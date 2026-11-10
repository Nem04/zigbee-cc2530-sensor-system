#ifndef LED_Light_H
#define LED_Light_H

#define LED_ON 1
#define LED_OFF 0
#define LED_PORT_1 1
#define LED_PORT_2 2 



#define LED_PORT_1_ON_ACTIVE 0 //低电平触发
#define LED_PORT_2_ON_ACTIVE 0 //低电平触发

//定义控制灯的端口
#define LED_PORT_1_GPIO P1_0 //定义LED_PORT为P10口控制
#define LED_PORT_2_GPIO P1_1 //定义LED_PORT为P10口控制



//函数声明
#define  LED1_light_Init() do{P1SEL &= ~((1<<0));\
    P1DIR |= ((1<<0));\
    LED_PORT_1_GPIO = !LED_PORT_1_ON_ACTIVE;\
    }while(0)    //初始化LED控制IO口函数


#define  LED2_light_Init() do{P1SEL &= ~((1<<1));\
    P1DIR |= ((1<<1));\
    LED_PORT_2_GPIO = !LED_PORT_2_ON_ACTIVE;\
    }while(0)    //初始化LED控制IO口函数

void LED1_light_control(unsigned char mode);
void LED2_light_control(unsigned char mode);

#endif