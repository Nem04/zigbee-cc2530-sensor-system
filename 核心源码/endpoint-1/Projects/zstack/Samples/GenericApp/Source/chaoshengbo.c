#include "chaoshengbo.h"
#include <ioCC2530.h>

static void chaoshengbo_Delay_1us(unsigned int microSecs)
{
    while (microSecs--)
    { /* 32 NOPs == 1 usecs 因为延时还有计算的缘故，用了31个nop*/
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    }
}

void chaoshengbo_init(void)
{
    Chaoshengbo_PIN_ECHO_IN();
    Chaoshengbo_PIN_ECHO_IN_MODE();

    Chaoshengbo_PIN_TRIG_OUT();
    Chaoshengbo_PIN_TRIG_GPIO_MODE();
}

unsigned int chaoshengbo_get_distance(void)
{
    unsigned int tick_value;
    unsigned int distance;
    unsigned int limit_vlaue=0;
    chaoshengbo_init();
    EA = 0;

    Chaoshengbo_PIN_TRIG = 1;

    chaoshengbo_Delay_1us(10); //需要延时10us以上的高电平
    Chaoshengbo_PIN_TRIG = 0;

    while (!Chaoshengbo_PIN_ECHO && limit_vlaue<50000)
    {
        limit_vlaue++;
    }
      

    T1CNTL = 0;
    T1CNTH = 0;
    T1CTL = 0x09; //通道0,中断有效,32分频;自动重装模式(0x0000->0xffff);

    while (Chaoshengbo_PIN_ECHO && T1CNTH < 180)
        ;

    T1CTL = 0x00; //关闭计数器
    tick_value = 256 * T1CNTH + T1CNTL;

    tick_value = tick_value / 10;

    EA = 1;

    distance = (unsigned int)(tick_value * 17) / 100;

    return distance;
}
