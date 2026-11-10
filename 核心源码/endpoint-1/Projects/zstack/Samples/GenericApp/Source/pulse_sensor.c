
#include "OSAL.h"
#include "hal_adc.h"
#include "hal_led.h"
#include "pulse_sensor.h"
#include "hal_uart.h"



/*
说明:
此pulsesensor的计算代码移植自 arduino pulse的官方代码，
每2s采样一次，我们使用12bit adc采样， pluse的波形为脉冲波
当检测到上升是点亮led1， 下降时灭掉led1。

我们使用time3来作为adc的定时采样。
*/


#define  MAX_VALUE      (1270)   //我们使用12bit adc采样， 设置成最大量程的 1/3
#define  MAX_RATE_ID     8        // 心率平均值总数，必须>=5, 设置大一点， 否则心率就跳动太大

static int max_value = MAX_VALUE;


//----------------------------------------------------------------------------------
static int rate[MAX_RATE_ID];                    // used to hold last ten IBI values  //存储心跳相领峰值的ms时间值
static unsigned long sampleCounter = 0;          // used to determine pulse timing  //当前采样的时间点 ms
static unsigned long lastBeatTime = 0;           // used to find the inter beat interval //心跳的峰值点
static int Px =MAX_VALUE;                      // used to find peak in pulse wave
static int T = MAX_VALUE;                     // used to find trough in pulse wave
static int thresh = MAX_VALUE;                // used to find instant moment of heart beat  //心跳上升和下降的阀值
static int amp = 100;                   // used to hold amplitude of pulse waveform  //心跳的幅度
static bool firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
static bool secondBeat = true;       // used to seed rate array so we startup with reasonable BPM


// these variables are volatile because they are used during the interrupt service routine!
static int BPM;                   // used to hold the pulse rate　　//心率，每秒几次
static int Signal;                // holds the incoming raw data  //当前采样的值
static int IBI = 600;             // holds the time between beats, the Inter-Beat Interval //相领峰值的ms
static bool Pulse = false;     // true when pulse wave is high, false when it's low
static bool QS = false;        // becomes true when Arduoino finds a beat.  //找到一次心跳



static void PulseSenosrCal()
{
    HalAdcSetReference( HAL_ADC_REF_AVDD ); //3.3为参考电压
    Signal = HalAdcRead( HAL_ADC_CHN_AIN4, HAL_ADC_RESOLUTION_12); //12 bit采样

    sampleCounter += 50;                         // keep track of the time in mS with this variable
    int N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise

/////////////////////////////////////////
#if 0
    static char buff[20];
    int len = sprintf(buff,"%d\n",Signal);
    HalUARTWrite( 0, buff, len);  /* 输出接收到的数据 */
#endif
//////////////////////////////////////////


    //  find the peak and trough of the pulse wave
    //最低点，即波谷
    if(Signal < thresh && N > (IBI/5)*3){       // avoid dichrotic noise by waiting 3/5 of last IBI
        if (Signal < T){                        // T is the trough
            T = Signal;                         // keep track of lowest point in pulse wave 
        }
    }

    //最高点，即波峰
    if(Signal > thresh && Signal > Px){          // thresh condition helps avoid noise
        Px = Signal;                             // P is the peak
    }                                        // keep track of highest point in pulse wave

    //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
    // signal surges up in value every time there is a pulse
    if (N > 250){                                   // avoid high frequency noise
        if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){        
            Pulse = true;                               // set the Pulse flag when we think there is a pulse

            //上升沿，点亮LED
            HalLedSet( PULSE_SENSOR_LED, HAL_LED_MODE_OFF );      // turn on LED1
            IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
            lastBeatTime = sampleCounter;               // keep track of time for next pulse

            //第一次找到峰值点
            if(firstBeat){                         // if it's the first time we found a beat, if firstBeat == TRUE
                firstBeat = false;                 // clear firstBeat flag
                return;                            // IBI value is unreliable so discard it
            }

            //第二次找到峰值点
            if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
                secondBeat = false;                 // clear secondBeat flag
                for(int i=0; i<MAX_RATE_ID; i++){         // seed the running total to get a realisitic BPM at startup
                    rate[i] = IBI;                      
                }
            }

            // keep a running total of the last 10 IBI values
            //通过最近的MAX_RATE_ID次采样，计算平均心跳
            int runningTotal = 0;                   // clear the runningTotal variable    

            for(int i=0; i<MAX_RATE_ID-1; i++){                // shift data in the rate array
                rate[i] = rate[i+1];              // and drop the oldest IBI value 
                runningTotal += rate[i];          // add up the 9 oldest IBI values
            }

            rate[MAX_RATE_ID-1] = IBI;                          // add the latest IBI to the rate array
            runningTotal += rate[MAX_RATE_ID-1];                // add the latest IBI to runningTotal
            runningTotal /= MAX_RATE_ID;                     // average the last 10 IBI values 
            BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
            QS = true;                              // set Quantified Self flag 

            if(BPM>40 && BPM<127)
            {            
            }
            else
            {
                BPM = 0;
                QS = false;  
            }
        // QS FLAG IS NOT CLEARED INSIDE THIS ISR
        }                       
    }

    if (Signal < thresh && Pulse == true){     // when the values are going down, the beat is over

        //检测到下降沿，关LED
        HalLedSet( PULSE_SENSOR_LED, HAL_LED_MODE_ON );  // turn off LED1
        Pulse = false;                         // reset the Pulse flag so we can do it again
        amp = Px - T;                           // get amplitude of the pulse wave
        thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
        Px = thresh;                            // reset these for next time
        T = thresh;
    }

    if (N > 2500){                             // if 2.5 seconds go by without a beat
        thresh = max_value;                          // set thresh default
        Px = max_value;                               // set P default
        T = max_value;                               // set T default

        lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date        
        firstBeat = true;                      // set these to avoid noise
        secondBeat = true;                     // when we get the heartbeat back
    }
}

//time3 初始化
static void InitTimer3()
{
	T3CTL |= BV(3);	//开启溢出中断
	T3CTL |= BV(5) | BV(6) | BV(7) ;//128分频, 已经是最大分频了
	T3CTL &= ~BV(0); T3CTL |= BV(1);//0x00~0xff，Modulo, repeatedly count from 0x00 to T3CC0
    /*
    这里实现每隔1ms秒翻转一次，128分频，128/32M *Number=0.002s,所以Number=500次
    由于timer3为8位，对应T3CC0为*/
    T3CC0 = 249;//中断中计数，中断两次开始调用
    
    T3CCTL0 |= BV(6);//IM
    T3CCTL0 |= BV(2);//MODE
        
	T3CTL |= BV(4); //启动timer3
	T3IE =1; //开启T3中断控制
}

#if 1
// THIS IS THE TIMER 3 INTERRUPT SERVICE ROUTINE. 
//定时器 T3 中断处理函数 ,1ms中断一次
#pragma vector = T3_VECTOR    
__interrupt void Timer3_ISR(void)
{
  //清楚中断标识
  IRCON &= ~BV(3);
  static uint16 count=0;

  if(count>=50)//2ms调用一次，因此，adc采样频率为500hz
  {
    PulseSenosrCal();
	count=0;
  }

  count++;
}



#endif

// 传感器初始化
void HeartRate_Init(void)
{

    InitTimer3();
}


unsigned char  GetCurrentHeartRate(void)
{
    if(QS)
    {
        QS = FALSE;
        return BPM;
    }
    return 0;
}


