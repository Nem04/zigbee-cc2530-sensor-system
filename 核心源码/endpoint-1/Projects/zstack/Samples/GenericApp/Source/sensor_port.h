#ifndef __SENSOR_PORT_H__
#define __SENSOR_PORT_H__


#define SENSOR_PORT_DO1   (P1_5)
#define SENSOR_PORT_DO2   (P1_6)


//函数声明
#define  Sensor_port_Init_DO1_IN() do{P1SEL &= ~(1<<5);\
    P1DIR &= ~(1<<5);\
    }while(0)    //初始化DO1控制IO口函数


#define  Sensor_port_Init_DO2_IN() do{P1SEL &= ~(1<<6);\
    P1DIR &= ~(1<<6);\
    }while(0)    //初始化DO1控制IO口函数



#define  Sensor_port_Init_DO1_OUT() do{P1SEL &= ~(1<<5);\
    P1DIR |= (1<<5);\
    }while(0)    //初始化DO1控制IO口函数


#define  Sensor_port_Init_DO2_OUT() do{P1SEL &= ~(1<<6);\
    P1DIR |= (1<<6);\
    }while(0)    //初始化DO1控制IO口函数



unsigned char   Sensor_port_Get_DO1(void);
unsigned char   Sensor_port_Get_DO2(void);


void Sensor_port_Set_DO1(unsigned char value);
void Sensor_port_Set_DO2(unsigned char value);


void Sensor_port_Init_AO(void);
void Sensor_port_Init_AO1(void);
void Sensor_port_Init_AO2(void);



unsigned char   Sensor_port_Get_AO0(void);
unsigned char   Sensor_port_Get_AO1(void);
unsigned char   Sensor_port_Get_AO2(void);


#endif
