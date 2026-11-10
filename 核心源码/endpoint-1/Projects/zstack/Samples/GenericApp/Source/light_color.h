#ifndef LIGHT_COLOR_H
#define LIGHT_COLOR_H

#define LIGHT_REVERSE			//开启反转   如果小灯是低电平触发则需开启

#define LIGHT_COLOR_RED          //开启红灯控制 P1_0
#define LIGHT_COLOR_BLUE		 //开启蓝灯控制 P1_5
#define LIGHT_COLOR_GREEN		 //开启绿灯控制 P1_1

void light_color_init(void);

void light_color_change(unsigned char arg_red , unsigned char arg_green ,unsigned char arg_blue);

void light_color_change_red(unsigned char arg_red);
void light_color_change_green(unsigned char arg_green);
void light_color_change_blue(unsigned char arg_blue);


#endif