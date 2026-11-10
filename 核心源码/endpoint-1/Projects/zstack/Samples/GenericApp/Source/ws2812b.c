#include "ws2812b.h"
#include <ioCC2530.h>


static unsigned char rgb[3];


static void wait_us( unsigned int timeout ) {
    while (timeout--) {
        asm("NOP");
        asm("NOP");
        asm("NOP");
    }
}


void ws2812b_rgb(unsigned char red , unsigned char green , unsigned char blue) {

    unsigned char i = 0;

    if(red>0xff) red=0xff;
    if(green>0xff) green=0xff;
    if(blue>0xff) blue=0xff;


    rgb[0] = red;
    rgb[1] = green;
    rgb[2] = blue;


    EA = 0;

    for (i = 0; i < 8; i++) {
        if (0x80 == (green & 0x80) ) {
            ws18b20_bit_1();
        } else {
            ws18b20_bit_0();
        }
        green <<= 1;
    }

    for (i = 0; i < 8; i++) {
        if (0x80 == (red & 0x80) ) {
            ws18b20_bit_1();
        } else {
            ws18b20_bit_0();
        }
        red <<= 1;
    }

    for (i = 0; i < 8; i++) {
        if (0x80 == (blue & 0x80) ) {
            ws18b20_bit_1();
        } else {
            ws18b20_bit_0();
        }
        blue <<= 1;
    }


    EA = 1;

    // ws18b20_bit_0();
    wait_us(55);
    // ws18b20_bit_1();
    // ws18b20_bit_0();
}


void ws2812b_red(unsigned char red ) {
    ws2812b_rgb(red, rgb[1], rgb[2]);
}

void ws2812b_green(unsigned char green) {
    ws2812b_rgb(rgb[0], green, rgb[2]);
}

void ws2812b_blue(unsigned char blue) {
    ws2812b_rgb(rgb[0], rgb[1], blue);
}




