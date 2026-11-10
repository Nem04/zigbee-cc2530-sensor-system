#ifndef __WS2812B_H__
#define __WS2812B_H__

//定义控制灯的端口
#define WS2812B_Port P1_3 //定义WS2812B_Port

#define ws18b20_bit_1()      {WS2812B_Port = 1;asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");WS2812B_Port = 0;}
#define ws18b20_bit_0()      {WS2812B_Port = 1 ;asm("NOP");asm("NOP");asm("NOP");WS2812B_Port = 0 ;asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");}



#define ws2812b_init()   do{P1SEL &= ~(1<<3);P1DIR |= (1<<3);}while(0)

//#define ws2812b_init()   do{P2SEL &= ~(1<<0);P2DIR |= (1<<0);P2_0=0;}while(0)

/*-------------------------------
(P2SEL specail rigister description)
D2			D1			D0
P2_4		P2_3		P2_0
---------------------------------*/


void ws2812b_rgb(unsigned char red , unsigned char green , unsigned char blue);

void ws2812b_red(unsigned char red );

void ws2812b_green(unsigned char green);

void ws2812b_blue(unsigned char blue);


#endif


