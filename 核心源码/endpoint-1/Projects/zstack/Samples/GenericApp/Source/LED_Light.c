#include "LED_Light.h"
#include <ioCC2530.h>




void LED1_light_control(unsigned char mode)
{

        if(mode==LED_OFF)
        {
            LED_PORT_1_GPIO = !LED_PORT_1_ON_ACTIVE;
        }
        else
        {

            LED_PORT_1_GPIO = LED_PORT_1_ON_ACTIVE;
        }
}



void LED2_light_control(unsigned char mode)
{

        if(mode==LED_OFF)
        {
            LED_PORT_2_GPIO = !LED_PORT_2_ON_ACTIVE;
        }
        else
        {
            LED_PORT_2_GPIO = LED_PORT_2_ON_ACTIVE;
        }
}




