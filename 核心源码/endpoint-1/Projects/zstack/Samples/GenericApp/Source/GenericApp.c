

/*********************************************************************
 * INCLUDES
 */
#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "ZDProfile.h"

#include "GenericApp.h"
#include "DebugTrace.h"

#if !defined(WIN32)
#include "OnBoard.h"
#endif

/* HAL */

#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"
#include "Hal_adc.h"
#include "stdio.h"
#include "OSAL_Nv.h"
#include "OSAL_Clock.h"

#include "hal_lcd.h"

#include <string.h>

#include "OSAL_Memory.h"

#include "transfer.h"
#include "rc522.h"
#include "dht11.h"
#include "ds18b20.h"
#include "pulse_sensor.h"
#include "ws2812b.h"
#include "oled.h"
#include "led_light.h"
#include "oled_img.h"
#include "sensor_port.h"

#include "protocol.h"
#include "pwm_control.h"
#include "sensor_misc.h"
#include "chaoshengbo.h"
#include "yali.h"
#include "stepper_motor.h"
#include "mpu6050.h"

/**********************************************/
//脉冲计数
#define Open_Pulse_Count 0 //是否采用脉冲捕获
#define Open_Flow_Count 0  //是否开启流量监测

volatile uint32 Flow_ABS_Count = 0; //流量脉冲绝对值计数（即 ： 正反各一次 则为 0）

volatile uint32 Flow_CountALL = 0; //流量脉冲计数

volatile uint32 Pulse_CountALL = 0; //脉冲计数

typedef struct
{
  uint32 num;
  uint32 time;
} pulse_count_struct;

#define Pulse_speed_buff_len 5
pulse_count_struct pulse_count_save[Pulse_speed_buff_len];

/**********************************************/

const cId_t GenericApp_ClusterList[GENERICAPP_MAX_CLUSTERS] =
    {
        GENERICAPP_END_CLA,
};

const SimpleDescriptionFormat_t GenericApp_SimpleDesc =
    {
        GENERICAPP_ENDPOINT,             /*  int Endpoint; */
        GENERICAPP_PROFID,               /*  uint16 AppProfId[2]; */
        GENERICAPP_DEVICEID,             /*  uint16 AppDeviceId[2]; */
        GENERICAPP_DEVICE_VERSION,       /*  int   AppDevVer:4; */
        GENERICAPP_FLAGS,                /*  int   AppFlags:4; */
        GENERICAPP_MAX_CLUSTERS,         /*  byte  AppNumInClusters; */
        (cId_t *)GenericApp_ClusterList, /*  byte *pAppInClusterList; */
        GENERICAPP_MAX_CLUSTERS,         /*  byte  AppNumInClusters; */
        (cId_t *)GenericApp_ClusterList  /*  byte *pAppInClusterList; */
};

endPointDesc_t GenericApp_epDesc;

afAddrType_t SampleApp_P2P_DstAddr;

byte GenericApp_TaskID;
devStates_t GenericApp_NwkState;

byte GenericApp_TransID; /* This is the unique message ID (counter) */

afAddrType_t GenericApp_DstAddr;

//-------------------------------------------//
unsigned char flag_is_send_request = 0;

unsigned char GlobalVar_flag_lock_status = 1;
unsigned char GlobalVar_flag_lock_update_once = 0;

unsigned char GlobalVar_event_sign_in = 0;

unsigned char GlobalVar_flag_key_press_1 = 0;
unsigned char GlobalVar_flag_key_press_2 = 0;

unsigned char GlobalVar_flag_auto_adjust = 0;

unsigned char GlobalVar_flag_auto_adjust_tds = 0;
unsigned char GlobalVar_flag_auto_adjust_wendu = 0;
unsigned char GlobalVar_flag_auto_adjust_yanwu = 0;
unsigned char GlobalVar_flag_auto_adjust_renti = 0;
unsigned char GlobalVar_flag_auto_adjust_guangqiang = 0;
unsigned char GlobalVar_flag_auto_adjust_turang = 0;
unsigned char GlobalVar_flag_auto_adjust_shuiwei = 0;
unsigned char GlobalVar_flag_auto_adjust_yudi = 0;
unsigned char GlobalVar_flag_auto_adjust_dianliu = 0;
unsigned char GlobalVar_flag_auto_adjust_dianya = 0;
unsigned char GlobalVar_flag_auto_adjust_huoyan = 0;
unsigned char GlobalVar_flag_auto_adjust_zhendong = 0;
unsigned char GlobalVar_flag_auto_adjust_stepper = 0;
unsigned char GlobalVar_flag_auto_adjust_zhuodu = 0;

unsigned int GlobalVar_sensor_online_response =  0;
unsigned int GlobalVar_sensor_distance = 0;
unsigned char GlobalVar_sensor_DO1 = 0;
unsigned char GlobalVar_sensor_huoyan = 0;
unsigned char GlobalVar_sensor_DO2 = 0;
unsigned char GlobalVar_sensor_AO1 = 0;
unsigned char GlobalVar_sensor_zhuodu = 0;
unsigned char GlobalVar_sensor_AO2 = 0;
unsigned int GlobalVar_sensor_PM25 = 0;
unsigned int GlobalVar_sensor_TDS_wendu = 0;
unsigned int GlobalVar_sensor_TDS = 0;
unsigned char GlobalVar_sensor_dht11_wendu = 0;
unsigned char GlobalVar_sensor_dht11_shidu = 0;
unsigned char GlobalVar_sensor_ds18b20_wendu = 0;
unsigned char GlobalVar_sensor_heart = 0;
unsigned char GlobalVar_sensor_RenTi = 0;
unsigned char GlobalVar_sensor_guangqiang = 0;
unsigned char GlobalVar_sensor_shuiwei = 0;
unsigned char GlobalVar_sensor_yudi = 0;
unsigned char GlobalVar_sensor_turang = 0;
unsigned int GlobalVar_sensor_jiguangceju = 0;
unsigned int GlobalVar_sensor_dianya = 0;
unsigned int GlobalVar_sensor_dianliu = 0;
unsigned int GlobalVar_sensor_xinlv = 0;
unsigned int GlobalVar_sensor_xueyang = 0;
unsigned int GlobalVar_sensor_PulseSpeed = 0;
unsigned int GlobalVar_sensor_yali = 0;


int GlobalVar_sensor_MPU6050_gx = 0;
int GlobalVar_sensor_MPU6050_gy = 0;
int GlobalVar_sensor_MPU6050_gz = 0;

unsigned char GlobalVar_Threshold_alert_guangqiang_max = 65;
unsigned char GlobalVar_Threshold_alert_guangqiang_min = 30;
unsigned char GlobalVar_Threshold_alert_guangqiang = 28;
unsigned char GlobalVar_Threshold_alert_wendu = 28;
unsigned char GlobalVar_Threshold_alert_tds = 50;
unsigned char GlobalVar_Threshold_alert_yanwu = 30;
unsigned char GlobalVar_Threshold_alert_turang = 30;
unsigned char GlobalVar_Threshold_alert_shuiwei = 30;
unsigned char GlobalVar_Threshold_alert_yudi = 30;
unsigned char GlobalVar_Threshold_alert_dianya = 80;
unsigned char GlobalVar_Threshold_alert_zhuodu = 80;
unsigned char GlobalVar_Threshold_alert_dianliu = 8;
unsigned int  GlobalVar_Threshold_alert_zhendong = 2000;

struct protocol_info protocol_uart;
unsigned char protocol_uart_buff[50];

struct protocol_info protocol_rf;
unsigned char protocol_rf_buff[256];

//-------------------------------------------//

/*****************************************************************/
/*****************************************************************/

void GenericApp_HandleKeys(byte shift, byte keys);

void GenericApp_MessageMSGCB(afIncomingMSGPacket_t *pckt);

void har_init(void);

void network_init(byte task_id);

void transfer_data_init(void);

void Detect_Sensor(void);

void user_recive_data(unsigned char *buff, unsigned int len);

void zigbee_AF(unsigned char *buff, unsigned int len);

static void Uart_Recv_Callback(uint8 port, uint8 event);

void user_process_msg_AF(unsigned char *src, int len);

void user_process_msg_Uart(unsigned char *src, int len);

void har_uart_init(void);


int Abs(int a)
{
  if(a>0)
  {
    return a;
  }
  else
  {
    return (0-a);
  }
  
}


void har_uart_init(void)
{

  halUARTCfg_t uartConfig;

  uartConfig.configured = TRUE; // 2x30 don't care - see uart driver.
  uartConfig.baudRate = HAL_UART_BR_9600;
  uartConfig.flowControl = FALSE;
  uartConfig.flowControlThreshold = 64; // 2x30 don't care - see uart driver.
  uartConfig.rx.maxBufSize = 64;        // 2x30 don't care - see uart driver.
  uartConfig.tx.maxBufSize = 64;        // 2x30 don't care - see uart driver.
  uartConfig.idleTimeout = 6;
  uartConfig.intEnable = TRUE; // 2x30 don't care - see uart driver.
  uartConfig.callBackFunc = Uart_Recv_Callback;
  HalUARTOpen(0, &uartConfig);
}

void process_PM25(const unsigned char *buff, unsigned char len)
{
  int i = 0;
  for (; i < len; i++)
  {
    if (len - i < 8)
    {
      break;
    }

    if (buff[i] == 0xff && buff[i + 1] == 0x18)
    {
      GlobalVar_sensor_PM25 = buff[i + 3] * 10 + buff[i + 4] / 10;
    }
  }
}

void process_TDS(const unsigned char *buff, unsigned char len)
{
  if (len > 11)
  {
    if (buff[0] == 0xaa && buff[6] == 0xab)
    {
      GlobalVar_sensor_TDS_wendu = (buff[7] * 0xff + buff[8]) / 100;
      ;
      GlobalVar_sensor_TDS = (buff[1] * 0xff + buff[2]);
    }
  }
}

void process_jiguangceju(const unsigned char *buff, unsigned char len)
{
  if (len == 2)
  {
    GlobalVar_sensor_jiguangceju = (buff[0] * 0xff + buff[1]) / 10;
  }
}

//流量统计(人流量 车流量)
void InitSensor_flow(void)
{
  /*
  * 冲计数初始化 :采用中断方式查询
  * 端口  p1_5  p1:6
  */

  P1SEL &= ~(1 << 6); /* 设置P0_6为一般IO口功能 */
  P1DIR &= ~(1 << 6); /* 设置P0_6为输入功能 */
  P1INP &= ~(1 << 6); /* 设置为上拉 */
  P1IEN |= 1 << 6;    /* P1.6 设置为中断方式 1：中断使能 */

  P1SEL &= ~(1 << 5); /* 设置P0_5为一般IO口功能 */
  P1DIR &= ~(1 << 5); /* 设置P0_5为输入功能 */
  P1INP &= ~(1 << 5); /* 设置为上下拉模式 */
  P1IEN |= 1 << 5;    /* P1.5 设置为中断方式 1：中断使能 */

  P2INP &= ~(1 << 6); /*开启上拉模式*/

  PICTL |= 1 << 2; /*下降沿触发 */
  IEN2 |= 1 << 4;  /* 允许P1口中断; */

  P1IFG &= ~(1 << 6); /* 初始化中断标志位 */
  P1IFG &= ~(1 << 5); /* 初始化中断标志位 */
  EA = 1;             /* 打开总中断 */
}

//脉冲传感器速度初始化
void InitSensor_pause_speed(void)
{

  pulse_count_struct pulse_count_struct_temp;
  int i;

  /*
   * 冲计数初始化 :采用中断方式查询
   * 端口   p1:5
   */

  // P1SEL   &= ~(1 << 6);   /* 设置P0_6为一般IO口功能 */
  // P1DIR   &= ~(1 << 6);   /* 设置P0_6为输入功能 */
  // P1INP   &= ~(1 << 6);   /* 设置为上拉 */
  // P1IEN   |= 1 << 6;      /* P1.6 设置为中断方式 1：中断使能 */

  P1SEL &= ~(1 << 5); /* 设置P1_5为一般IO口功能 */
  P1DIR &= ~(1 << 5); /* 设置P1_5为输入功能 */
  P1INP &= ~(1 << 5); /* 设置为上下拉模式 */
  P1IEN |= 1 << 5;    /* P1.5 设置为中断方式 1：中断使能 */

  P2INP &= ~(1 << 6); /*开启上拉模式  注意：第6位代表整个P1为上拉，而不是第6位*/

  PICTL &= ~(1 << 2); /*上升沿触发 */
  // PICTL    |= ( 1 << 2);      /*下降沿触发 */

  IEN2 |= 1 << 4; /* 允许P1口中断; */

  // P1IFG   &= ~(1 << 6);   /* 初始化中断标志位 */
  P1IFG &= ~(1 << 5); /* 初始化中断标志位 */
  EA = 1;             /* 打开总中断 */

  for (i = 0; i < Pulse_speed_buff_len - 1; i++)
  {

    pulse_count_struct_temp.num = 0;
    pulse_count_struct_temp.time = osal_getClock();
    pulse_count_save[i] = pulse_count_struct_temp;
  }
}

//脉冲传感器初始化
void InitSensor_pulse(void)
{

  /*
   * 冲计数初始化 :采用中断方式查询
   * 端口   p1:5
   */

  // P1SEL   &= ~(1 << 6);   /* 设置P0_6为一般IO口功能 */
  // P1DIR   &= ~(1 << 6);   /* 设置P0_6为输入功能 */
  // P1INP   &= ~(1 << 6);   /* 设置为上拉 */
  // P1IEN   |= 1 << 6;      /* P1.6 设置为中断方式 1：中断使能 */

  P1SEL &= ~(1 << 5); /* 设置P1_5为一般IO口功能 */
  P1DIR &= ~(1 << 5); /* 设置P1_5为输入功能 */
  P1INP &= ~(1 << 5); /* 设置为上下拉模式 */
  P1IEN |= 1 << 5;    /* P1.5 设置为中断方式 1：中断使能 */

  P2INP &= ~(1 << 6); /*开启上拉模式  注意：第6位代表整个P1为上拉，而不是第6位*/

  PICTL &= ~(1 << 2); /*上升沿触发 */
  // PICTL    |= ( 1 << 2);      /*下降沿触发 */

  IEN2 |= 1 << 4; /* 允许P1口中断; */

  // P1IFG   &= ~(1 << 6);   /* 初始化中断标志位 */
  P1IFG &= ~(1 << 5); /* 初始化中断标志位 */
  EA = 1;             /* 打开总中断 */
}

/****************************
 * //中断处理函数  --- 脉冲中断捕获
 *****************************/

#if Open_Pulse_Count

HAL_ISR_FUNCTION(isr_count_pulse, P1INT_VECTOR)
{

  // interrupte_CountALL++;

  if (P1IFG & (1 << 5))
  {
    Onboard_wait(500); /* uS */
    // while (P1_5 == 0); //wait

    if (P1_5 == 1)
    {
      Pulse_CountALL++;
    }

    // P1IFG &= ~(1 << 5);
  }

  P1IF = 0;
  P1IFG = 0; //清中断标志
  P1IF = 0;  //清中断标
}

#endif

/****************************
 * //中断处理函数  --- 脉冲中断捕获
 *****************************/
#if Open_Flow_Count
HAL_ISR_FUNCTION(light_adj, P1INT_VECTOR)
{
  static uint8 flag_state_p16 = 0;
  static uint8 flag_state_p15 = 0;

  static uint32 flag_record_time_p16 = 0;
  static uint32 flag_record_time_p15 = 0;

  if (P1IFG & (1 << 6)) /* 中断计数 */
  {
    Onboard_wait(6000);   /* 100uS */
    if (P1IFG & (1 << 6)) /* 去抖 */
    {
      // while (P1_6 == 0); //wait

      flag_record_time_p16 = osal_getClock(); //获取当前时间

      if (flag_state_p15 && flag_record_time_p16 - flag_record_time_p15 <= 2)
      {
        Flow_ABS_Count++; /* 设置标志 */

        Flow_CountALL++; //人流量

        flag_state_p15 = 0;
        flag_state_p16 = 0;
      }
      else
      {
        flag_state_p16 = 1;
        flag_state_p15 = 0;
      }

      Onboard_wait(50000); /* 50000uS */
      Onboard_wait(50000); /* 50000uS */
      Onboard_wait(50000); /* 50000uS */
      Onboard_wait(50000); /* 50000uS */

      P1IFG &= ~(1 << 6);
      P1IFG &= ~(1 << 5);
    }
  }

  /*****************************/
  else if (P1IFG & (1 << 5)) /* 中断计数 */
  {
    Onboard_wait(6000);   /* 100uS */
    if (P1IFG & (1 << 5)) /* 去抖 */
    {
      // while (P1_5 == 0); //wait

      flag_record_time_p15 = osal_getClock(); //获取当前时间

      if (flag_state_p16 && flag_record_time_p15 - flag_record_time_p16 <= 2)
      {

        if (Flow_ABS_Count > 0)
          Flow_ABS_Count--; /* 设置标志 */

        Flow_CountALL++; //人流量

        flag_state_p15 = 0;
        flag_state_p16 = 0;
      }
      else
      {
        flag_state_p15 = 1;
        flag_state_p16 = 0;
      }

      Onboard_wait(50000); /* 50000uS */
      Onboard_wait(50000); /* 50000uS */
      Onboard_wait(50000); /* 50000uS */
      Onboard_wait(50000); /* 50000uS */

      P1IFG &= ~(1 << 5);
      P1IFG &= ~(1 << 6);
    }
  }
}

#endif

/***********************************************************
***********************************************************/

//获取流量状态并上报
void GetSensor_flow(char *flow_abs, char *flow_all)
{
  Set_id_value_int(flow_abs, Flow_ABS_Count);
  Set_id_value_int(flow_all, Flow_CountALL);
}

//获取脉冲上报
void GetSensor_pulse(char *name)
{
  int value = Pulse_CountALL;
  Set_id_value_int(name, value);
}

void GetSensor_pulse_speed(char *pulse_name)
{
  unsigned long num = Pulse_CountALL;
  unsigned long time_temp = osal_getClock();

  int i;
  int pulse_speed_every_minute;

  for (i = 0; i < Pulse_speed_buff_len - 1; i++)
  {
    pulse_count_save[i] = pulse_count_save[i + 1];
  }
  pulse_count_save[Pulse_speed_buff_len - 1].num = num;
  pulse_count_save[Pulse_speed_buff_len - 1].time = time_temp;

  time_temp = (pulse_count_save[Pulse_speed_buff_len - 1].time - pulse_count_save[0].time);
  if (time_temp == 0)
    time_temp = 1;

  num = (pulse_count_save[Pulse_speed_buff_len - 1].num - pulse_count_save[0].num);

  pulse_speed_every_minute = (num * 60) / time_temp;

  GlobalVar_sensor_PulseSpeed = pulse_speed_every_minute;

  Set_id_value_int(pulse_name, GlobalVar_sensor_PulseSpeed);
}

unsigned char GetSensor_rc522(char *name)
{
  char state;
  char value[10];
  char temp[20];
  unsigned int len;

  state = PcdRequest(PICC_REQIDL, value);
  if (!state)
  {
    state = PcdAnticoll(value);

    if (state == MI_OK)
    {
      len = sprintf(temp, "%02X%02X%02X%02X", value[0], value[1], value[2], value[3]);
      temp[len] = 0;

      //OLED_P6x8Str(0,4,temp);

      Set_id_value_str(name, temp);

      return 1;
    }
  }

  return 0;
}

void GetSensor_distance(char *name)
{
  // Set_id_value_int(name, GlobalVar_sensor_distance);

  unsigned int value;
  value = chaoshengbo_get_distance();

  GlobalVar_sensor_distance = value;
  Set_id_value_int(name, value);
}

void GetSensor_PM25(char *name)
{
  Set_id_value_int(name, GlobalVar_sensor_PM25);
}

void GetSensor_yali(char *name)
{
  // Set_id_value_int(name, GlobalVar_sensor_distance);
  static char flag_is_first_init = 3;
  unsigned int value;

  if (flag_is_first_init)
  {
    yali_Weight_calibration();
    flag_is_first_init--;
  }
  value = yali_Get_Weight();

  GlobalVar_sensor_yali = value;
  Set_id_value_int(name, value);
}

void GetSensor_TDS(char *name_tds, char *name_wendu)
{
  unsigned char const tds_triger[] = {0xA0, 00, 00, 00, 00, 0xA0};
  HalUARTWrite(0, tds_triger, sizeof(tds_triger));
  Set_id_value_int(name_tds, GlobalVar_sensor_TDS);
  Set_id_value_int(name_wendu, GlobalVar_sensor_TDS_wendu);
}

void GetSensor_jiguangceju(char *name)
{

  unsigned char const triger[] = {0xA0};

  HalUARTWrite(0, triger, sizeof(triger));

  Set_id_value_int(name, GlobalVar_sensor_jiguangceju);
}

// void GetSensor_Chaoshengbo(char *name)
// {
//   unsigned int value;
//   value = chaoshengbo_get_distance();

//   GlobalVar_sensor_RenTi = value;
//   Set_id_value_int(name, value);
// }

void GetSensor_RenTi(char *name)
{
  unsigned char value;
  value = GetSensor_Renti();

  GlobalVar_sensor_RenTi = value;
  Set_id_value_int(name, value);
}

void GetSensor_DO1(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_DO1();

  GlobalVar_sensor_DO1 = value;
  Set_id_value_int(name, value);
}

void GetSensor_huoyan_DO1(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_DO1();

  GlobalVar_sensor_huoyan = !value;
  Set_id_value_int(name, GlobalVar_sensor_huoyan);
}

void GetSensor_DO2(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_DO2();

  GlobalVar_sensor_DO2 = value;
  Set_id_value_int(name, value);
}


void GetSensor_zhuodu(char *name)
{
  unsigned int value;
  value = Sensor_port_Get_AO1();
  if(value >128)  value =128;
  value = 128-value;

  GlobalVar_sensor_zhuodu = value;
  Set_id_value_int(name, value);
}


void GetSensor_time(char *name)
{
  // Set_id_value_int(name, GlobalVar_sensor_distance);

  unsigned int value;
  value = osal_GetSystemClock() / 1000;;
 
  Set_id_value_int(name, value);
}



void GetSensor_A01(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_AO1();

  GlobalVar_sensor_AO1 = value;
  Set_id_value_int(name, value);
}

void GetSensor_A02(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_AO2();

  GlobalVar_sensor_AO2 = value;
  Set_id_value_int(name, value);
}

void GetSensor_Guangqiang_AO1(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_AO1();

  value = value > 100 ? 100 : value;
  value = 100 - value;

  GlobalVar_sensor_guangqiang = value;
  Set_id_value_int(name, value);
}


void GetSensor_yudi_AO1(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_AO1();

  value = value > 128 ? 128 : value ;
  value = value < 40 ? 40 : value;

  value = 128 - value;
 
  GlobalVar_sensor_yudi = value;
  Set_id_value_int(name, value);
}



void GetSensor_Shuiwei_AO1(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_AO1();

  value = value < 40 ? 40 : value;
  value = value > 65 ? 65 : value;
  value = value - 40;
  value = value * 4;

  GlobalVar_sensor_shuiwei = value;
  Set_id_value_int(name, value);
}

void GetSensor_Turang_AO2(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_AO2();

  value = value > 127 ? 127 : value;
  value = 127 - value;

  GlobalVar_sensor_turang = value;
  Set_id_value_int(name, value);
}

void GetSensor_dianya_AO1(char *name)
{
  unsigned int value;
  value = Sensor_port_Get_AO1();

  value = value * 5 * 33 / 128; //100mv

  GlobalVar_sensor_dianya = value;
  Set_id_value_int(name, value);
}

void GetSensor_dianliu_AO2(char *name)
{
  static char flag_first_init = 1;
  static int first_init_calibration = 0;
  unsigned int value;
  unsigned long count_num;

  if (flag_first_init)
  {
    first_init_calibration = HalAdcRead(HAL_ADC_CHN_AIN6, HAL_ADC_RESOLUTION_14);
    flag_first_init = 0;
  }

  value = HalAdcRead(HAL_ADC_CHN_AIN6, HAL_ADC_RESOLUTION_14);

  // if(first_init_calibration>value)
  //   {
  //       count_num = first_init_calibration - value ;
  //   }
  //   else{
  //       count_num = value - first_init_calibration;
  //   }

  if (4140 > value)
  {
    count_num = 4140 - value;
  }
  else
  {
    count_num = value - 4140;
  }

  value = count_num * 33 / 82; //get 10mA
  if (value < 5)
    value = 0;

  GlobalVar_sensor_dianliu = value;
  Set_id_value_int(name, value);
}

void GetSensor_Key1(char *name)
{

  if (GlobalVar_flag_key_press_1)
  {
    Set_id_value_str(name, "press");
    GlobalVar_flag_key_press_1 = 0;
  }
}

void GetSensor_Key2(char *name)
{
  if (GlobalVar_flag_key_press_2)
  {
    Set_id_value_str(name, "press");
    GlobalVar_flag_key_press_2 = 0;
  }
}

void GetSensor_dht11(char *name_wendu, char *name_shidu)
{
  unsigned char temp_wendu, temp_shidu;

  Dht11_read(&temp_wendu, &temp_shidu);

  GlobalVar_sensor_dht11_wendu = temp_wendu;
  GlobalVar_sensor_dht11_shidu = temp_shidu;

  Set_id_value_int(name_wendu, temp_wendu);
  Set_id_value_int(name_shidu, temp_shidu);
}

void GetSensor_ds18b20(char *name_wendu)
{
  unsigned char temp_wendu;

  temp_wendu = ReadDs18B20();

  GlobalVar_sensor_ds18b20_wendu = temp_wendu;

  Set_id_value_int(name_wendu, temp_wendu);
}

void GetSensor_heart(char *name_heart)
{
  unsigned char heart;

  heart = GetCurrentHeartRate();

  GlobalVar_sensor_heart = heart;

  Set_id_value_int(name_heart, heart);
}

void GetSensor_max30102(char *xinlv, char *xueyang)
{

  Set_id_value_int(xinlv, GlobalVar_sensor_xinlv);
  Set_id_value_int(xueyang, GlobalVar_sensor_xueyang);
}

void InitSensor_mpu6050()
{
  IIC_Init();           //IIC初始化
  MPU6050_Initialize(); //初始化mpu6050
}

void GetSensor_MPU6050(char *name_gx, char *name_gy, char *name_gz, char *name_ax, char *name_ay, char *name_az)
{
  unsigned char value;

  int ax, ay, az;
  int temperature;
  int gx, gy, gz;
  // float f_temperature;

  MPU6050_Initialize(); //初始化mpu6050

  //读取mpu6050的实时数据
  MPU6050_GetRawAccelGyro(&gx, &gy, &gz, &temperature, &ax, &ay, &az);
  // f_temperature = (float)temperature/340.0 + 36.53;

  GlobalVar_sensor_MPU6050_gx = gx;
  GlobalVar_sensor_MPU6050_gy = gy;
  GlobalVar_sensor_MPU6050_gz = gz;

  Set_id_value_int(name_ax, ax);
  Set_id_value_int(name_ay, ay);
  Set_id_value_int(name_az, az);
  Set_id_value_int(name_gx, gx);
  Set_id_value_int(name_gy, gy);
  Set_id_value_int(name_gz, gz);
}

void GetSensor_Beep(char *name)
{
  unsigned char value;
  value = Sensor_port_Get_DO1();

  GlobalVar_sensor_DO1 = value;
  Set_id_value_int(name, value);
}

void zigbee_AF(unsigned char *buff, unsigned int len)
{
  afStatus_t status;

  status = AF_DataRequest(&SampleApp_P2P_DstAddr, &GenericApp_epDesc,
                          GENERICAPP_END_CLA,
                          len,
                          buff,
                          &GenericApp_TransID,
                          AF_DISCV_ROUTE,
                          AF_DEFAULT_RADIUS);

  (void)status;
}

void GenericApp_Init(byte task_id)
{

  network_init(task_id);

  har_init();

  transfer_data_init();
}

UINT16 GenericApp_ProcessEvent(byte task_id, UINT16 events)
{
  afIncomingMSGPacket_t *MSGpkt;
  afDataConfirm_t *afDataConfirm;

  /* Data Confirmation message fields */
  byte sentEP;
  ZStatus_t sentStatus;
  byte sentTransID; /* This should match the value sent */
  (void)task_id;    /* Intentionally unreferenced parameter */

  if (events & SYS_EVENT_MSG)
  {
    MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive(GenericApp_TaskID);
    while (MSGpkt)
    {
      switch (MSGpkt->hdr.event)
      {

      case AF_DATA_CONFIRM_CMD:
        /*
         * This message is received as a confirmation of a data packet sent.
         * The status is of ZStatus_t type [defined in ZComDef.h]
         * The message fields are defined in AF.h
         */
        afDataConfirm = (afDataConfirm_t *)MSGpkt;
        sentEP = afDataConfirm->endpoint;
        sentStatus = afDataConfirm->hdr.status;
        sentTransID = afDataConfirm->transID;
        (void)sentEP;
        (void)sentTransID;

        /* Action taken when confirmation is received. */
        if (sentStatus != ZSuccess)
        {
          /* The data wasn't delivered -- Do something */
        }
        break;

      case KEY_CHANGE:

        //按键处理事件，用来处理按键
        GenericApp_HandleKeys(((keyChange_t *)MSGpkt)->state, ((keyChange_t *)MSGpkt)->keys);
        break;

      case AF_INCOMING_MSG_CMD:

        //接受其它无线节点发来的消息
        GenericApp_MessageMSGCB(MSGpkt);
        break;

      case ZDO_STATE_CHANGE:

        //网络状态改变事件，当组网成功后，开始定时器轮询采集传感器
        GenericApp_NwkState = (devStates_t)(MSGpkt->hdr.status);
        if ((GenericApp_NwkState == DEV_ROUTER) || (GenericApp_NwkState == DEV_END_DEVICE))
        {

          //该定时器用来轮询采集传感器
          osal_start_timerEx(GenericApp_TaskID,
                             GENERICAPP_DETECT_SENSOR_MSG_EVT,
                             GENERICAPP_DETECT_SENSOR_MSG_TIMEOUT + (osal_rand() & 0x00FF) );

          //该定时器用来周期性的处理其它无线节点发来的数据
          osal_start_timerEx(GenericApp_TaskID,
                             GENERICAPP_TRANSFER_RECV_DATA_EVT,
                             GENERICAPP_TRANSFER_RECV_DATA_TIMEOUT + (osal_rand() & 0x00FF));

          osal_start_timerEx(GenericApp_TaskID,
                             GENERICAPP_Stepper_motor_EVT,
                             1);
        }
        break;

      default:
        break;
      }

      /* Release the memory */
      osal_msg_deallocate((uint8 *)MSGpkt);

      /* Next */
      MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive(GenericApp_TaskID);
    }

    /* return unprocessed events */
    return (events ^ SYS_EVENT_MSG);
  }

  if (events & GENERICAPP_DETECT_SENSOR_MSG_EVT)
  {

    HalLedOnOff(HAL_LED_3, HAL_LED_MODE_ON);
    HalLedBlink(HAL_LED_3, 2, 50, 500);

    Detect_Sensor(); //传感器探测监测核心函数

    //再次开启定时器
    osal_start_timerEx(GenericApp_TaskID,
                       GENERICAPP_DETECT_SENSOR_MSG_EVT,
                       GENERICAPP_DETECT_SENSOR_MSG_TIMEOUT + (osal_rand() & 0x00FF));

    /* return unprocessed events */
    return (events ^ GENERICAPP_DETECT_SENSOR_MSG_EVT);
  }

  if (events & GENERICAPP_TRANSFER_RECV_DATA_EVT)
  {
    transfer_recv_sync();

    osal_start_timerEx(GenericApp_TaskID,
                       GENERICAPP_TRANSFER_RECV_DATA_EVT,
                       GENERICAPP_TRANSFER_RECV_DATA_TIMEOUT + (osal_rand() & 0x00FF));

    /* return unprocessed events */
    return (events ^ GENERICAPP_TRANSFER_RECV_DATA_EVT);
  }

  if (events & GENERICAPP_Stepper_motor_EVT)
  {
    stepper_motor_trigger_1ms();

    osal_start_timerEx(GenericApp_TaskID,
                       GENERICAPP_Stepper_motor_EVT,
                       1);

    /* return unprocessed events */
    return (events ^ GENERICAPP_Stepper_motor_EVT);
  }

  /* Discard unknown events */
  return (0);
}

void transfer_data_init(void)
{

  struct transfer_operation data_operation;
  data_operation.device_send_function = zigbee_AF;
  data_operation.user_recv_callback = user_recive_data;
  transfer_init(&data_operation);

  protocol_rf.buff_max_len = 256;
  protocol_rf.buff = protocol_rf_buff;
  protocol_rf.pack_callback = user_process_msg_AF;

  protocol_uart.buff_max_len = 50;
  protocol_uart.buff = protocol_uart_buff;
  protocol_uart.pack_callback = user_process_msg_Uart;
}

void network_init(byte task_id)
{

  GenericApp_TaskID = task_id;
  GenericApp_NwkState = DEV_INIT;
  GenericApp_TransID = 0;

  GenericApp_DstAddr.addrMode = (afAddrMode_t)AddrNotPresent;
  GenericApp_DstAddr.endPoint = 0;
  GenericApp_DstAddr.addr.shortAddr = 0;

  GenericApp_epDesc.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc.task_id = &GenericApp_TaskID;
  GenericApp_epDesc.simpleDesc = (SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
  GenericApp_epDesc.latencyReq = noLatencyReqs;

  afRegister(&GenericApp_epDesc);

  SampleApp_P2P_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
  SampleApp_P2P_DstAddr.endPoint = GENERICAPP_ENDPOINT;
  SampleApp_P2P_DstAddr.addr.shortAddr = 0x0000;

  //注册按键
  RegisterForKeys(GenericApp_TaskID);
}

//按键处理函数
void GenericApp_HandleKeys(byte shift, byte keys)
{
  (void)shift; /* Intentionally unreferenced parameter */

  if (keys & HAL_USER_KEY_1)
  {

    GlobalVar_flag_key_press_1 = 1;

    HalLedBlink(HAL_LED_1, 6, 50, 500);
  }

  /**************************************************************/
  if (keys & HAL_USER_KEY_2)
  {
    GlobalVar_flag_key_press_2 = 1;

    HalLedBlink(HAL_LED_2, 6, 50, 500);
  }
}

//接收到其它无线节点的数据后，将数据存到缓存区，有解析定时器定时解析。
void GenericApp_MessageMSGCB(afIncomingMSGPacket_t *pckt)
{

  HalLedOnOff(HAL_LED_3, HAL_LED_MODE_OFF);
  HalLedBlink(HAL_LED_3, 4, 50, 200);

  transfer_recv_to_cache(pckt->cmd.Data, pckt->cmd.DataLength);
}

//解析串口发来的数据指令
void user_process_msg_Uart(unsigned char *src, int len)
{
  char id[20];
  char value[20];

  int num_value;

  //HalUARTWrite(0,src,len);

  if (len < 5)
    return;

  while (Get_id_value(&protocol_uart, (char *)src, id, value))
  {

    // if (strcmp(id, "distance") == 0)
    // {
    //   num_value = osal_atoi(value);

    //   GlobalVar_sensor_distance = num_value;
    // }

    if (strcmp(id, "xinlv") == 0)
    {
      num_value = osal_atoi(value);

      GlobalVar_sensor_xinlv = num_value;
    }

    else if (strcmp(id, "xueyang") == 0)
    {
      num_value = osal_atoi(value);

      GlobalVar_sensor_xueyang = num_value;
    }
  }
}










void user_recive_data(unsigned char *buff, unsigned int len)
{

  GetPack(&protocol_rf, buff, len);
}

//处理串口收到的数据
static void Uart_Recv_Callback(uint8 port, uint8 event)
{

  static unsigned char recv_buff[50];
  unsigned char SerialApp_TxLen;
  if ((event & (HAL_UART_RX_FULL | HAL_UART_RX_ABOUT_FULL | HAL_UART_RX_TIMEOUT)))
  {
    //osal_memset(RxBuf, 0, Uart_Recv_property_max_len + 1);

    //static unsigned int  SerialApp_TxLen = 0;

    SerialApp_TxLen = HalUARTRead(0, recv_buff, 50);

    GetPack(&protocol_uart, recv_buff, SerialApp_TxLen);

    // process_PM25(recv_buff, SerialApp_TxLen);

    // process_TDS(recv_buff, SerialApp_TxLen);

    // process_jiguangceju(recv_buff, SerialApp_TxLen);
  }
}
   

void Adjust_Sensor(void)
{

 
  
  unsigned char flag_beep = 0;

 

  if (GlobalVar_flag_auto_adjust_yanwu)
  {
    if (GlobalVar_sensor_AO2 > GlobalVar_Threshold_alert_yanwu)
    {
      flag_beep = 1;
    }
  }

  if (GlobalVar_flag_auto_adjust_wendu)
  {
    // if (GlobalVar_sensor_ds18b20_wendu > GlobalVar_Threshold_alert_wendu)
    // if (GlobalVar_sensor_TDS_wendu > GlobalVar_Threshold_alert_wendu)
    if (GlobalVar_sensor_dht11_wendu > GlobalVar_Threshold_alert_wendu)
    {
      flag_beep = 1;
    }
  }

 

  if (GlobalVar_flag_auto_adjust_wendu || GlobalVar_flag_auto_adjust_yanwu  )
  {
    if (flag_beep)
    {
      SetSensor_Beep(1);
    }
    else
    {
      SetSensor_Beep(0);
    }
  }

 




}

//硬件初始化函数
void har_init()
{


  Sensor_port_Init_AO1();  //模拟电压采集初始化 ，对应P0——5引脚
  Sensor_port_Init_AO2();  //模拟电压采集初始化 ，对应P0——6引脚
  InitSensor_Beep();  //蜂鸣器初始化

}

//采集传感器信息的函数
void Detect_Sensor(void)
{
  //unsigned char status = 0;

  Start_send_pack(); //开始数据采集发送前，需要发送包头

  /**********************************************/
  GetSensor_dht11("wendu1", "shidu1");  //获取dht11的温湿度数据

  GetSensor_A02("yanwu1");   //获取AO传感器数值，对应引脚P0_6.    如采集MQ-X传感器

  Complete_send_pack(); //结束数据的采集，发送包尾 并 调用zigbee无线发送数据到协调器

  Adjust_Sensor(); //数据发送完毕，开始自动调节判断（如高温开风扇、天黑开灯）
}

//接收协调器发来的控制指令。
//如 开灯 、开蜂鸣器、设置高温阈值等
void user_process_msg_AF(unsigned char *src, int len)
{
  char id[30];
  char value[30];

  int num_value;

  // HalUARTWrite(0, src, len);

  if (len < 5)
    return;

  while (Get_id_value(&protocol_rf, (char *)src, id, value))
  {
    GlobalVar_sensor_online_response ++ ;

    if (strcmp(id, "beep1") == 0)
    {

      if (GlobalVar_flag_auto_adjust_wendu || GlobalVar_flag_auto_adjust_yanwu )
      {
        continue;
      }

      if (strcmp(value, "on") == 0)
      {
        SetSensor_Beep(1);
      }
      else
      {
        SetSensor_Beep(0);
      }
    }

   

    else if (strcmp(id, "auto_yanwu1") == 0)
    {
      if (strcmp(value, "on") == 0)
      {
        GlobalVar_flag_auto_adjust_yanwu = 1;
      }
      else
      {
        GlobalVar_flag_auto_adjust_yanwu = 0;
      }
    }

    else if (strcmp(id, "auto_wendu1") == 0)
    {
      if (strcmp(value, "on") == 0)
      {
        GlobalVar_flag_auto_adjust_wendu = 1;
      }
      else
      {
        GlobalVar_flag_auto_adjust_wendu = 0;
      }
    }

 
    else if (strcmp(id, "limit_yanwu1") == 0)
    {
      num_value = osal_atoi(value);

      if (num_value > 0xff)
        num_value = 0xff;

      GlobalVar_Threshold_alert_yanwu = num_value;
    }

    else if (strcmp(id, "limit_wendu1") == 0)
    {
      num_value = osal_atoi(value);

      if (num_value > 0xff)
        num_value = 0xff;

      GlobalVar_Threshold_alert_wendu = num_value;
    }

    




    
  }
}



/*********-----------------------------------------------------*********/
