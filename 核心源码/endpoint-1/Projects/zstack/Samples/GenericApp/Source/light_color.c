#include "pwm_control.h"
#include "light_color.h"
#include "iocc2530.h"
#include "OnBoard.h"

void light_color_init(void)
{

  CLKCONCMD &= ~0x40;             /* 设置系统时钟源为32MHZ晶振 */
  while ( CLKCONSTA & 0x40 )
    ;                       /* 等待晶振稳定为32M */
  CLKCONCMD &= ~0x07;       /* 设置系统主时钟频率为32MHZ */
  CLKCONCMD |= 0x38;        /* 时钟速度32 MHz 定时器标记输出设置[5:3]250kHz */

  PERCFG  |= 0x40;                /* 定时器1 的IO位置   1:备用位置2 */
  P2SEL &= ~0x10;               /* 定时器1优先 */
  P2DIR |= 0x80;                /* 第1优先级：定时器1通道2-3 */

  T1CC0H  = 0x0f;                 /* PWM duty cycle  周期 */
  T1CC0L  = 0xff;



#ifdef LIGHT_COLOR_RED

  P1DIR |= 0x01;                /* 端口1为输出 */
  P1SEL |= 0x01;                /* P1_0开启外设功能*/

//0x24 < -- > 0x1c  反转方式
  T1CCTL2 = 0x24;                 /* 模式选择 通道2比较模式 */
  T1CC2H  = 0x00;
  T1CC2L  = 0x01;

#endif

#ifdef LIGHT_COLOR_GREEN

  P1DIR |= (0x01 << 1);       /* 端口1为输出 */
  P1SEL |= (0x01 << 1);       /* P1_0开启外设功能*/


  T1CCTL1 = 0x24;                 /* 模式选择 通道1比较模式 */
  T1CC1H  = 0x00;
  T1CC1L  = 0x01;

#endif

  T1CTL = 0x02;                   /*不分频 */


#ifdef LIGHT_COLOR_BLUE

  // pwm 调光第三引脚
  P1SEL &= ~(1 << 5);   /* P1_5 定义普通IO */
  P1DIR |= (1 << 5);    /* P1_5 定义为输出 */
  P1_5 = 0;

#endif



}


void light_color_change(unsigned char arg_red , unsigned char arg_green , unsigned char arg_blue)
{
  unsigned int pwm_red, pwm_green;

#ifdef LIGHT_COLOR_RED

  pwm_red = arg_red * 16;


  if ( arg_red <= 5 )
  {
    T1CC2H  = 0x00;
    T1CC2L  = 0x01;
  }
  else if ( arg_red >= 254 )
  {
    T1CC2H  = 0x0f;
    T1CC2L  = 0xff;
  }
  else
  {
    T1CC2H  = pwm_red / 256;
    T1CC2L  = pwm_red % 256;

  }


#endif


#ifdef LIGHT_COLOR_GREEN

  pwm_green = 16 * arg_green;

  if ( arg_green <= 5 )
  {
    T1CC1H  = 0x00;
    T1CC1L  = 0x01;
  }
  else if ( arg_green >= 254 )
  {
    T1CC1H  = 0x0f;
    T1CC1L  = 0xff;
  }
  else
  {
    T1CC1H  = pwm_green / 256;
    T1CC1L  = pwm_green % 256;


  }


#endif



#ifdef LIGHT_COLOR_BLUE

  if (arg_blue > 125)
  {
    P1_5 = 1;
  }
  else
  {
    P1_5 = 0;
  }


#endif
}





void light_color_change_red(unsigned char arg_red)
{
  unsigned int pwm_red;
#ifdef LIGHT_COLOR_RED

  pwm_red = arg_red * 16;

  if ( arg_red <= 5 )
  {
    T1CC2H  = 0x00;
    T1CC2L  = 0x01;
  }
  else if ( arg_red >= 254 )
  {
    T1CC2H  = 0x0f;
    T1CC2L  = 0xff;
  }
  else
  {
    T1CC2H  = pwm_red / 256;
    T1CC2L  = pwm_red % 256;

  }



#endif
}


void light_color_change_green(unsigned char arg_green)
{
  unsigned int pwm_green;
#ifdef LIGHT_COLOR_GREEN

  pwm_green = 16 * arg_green;


  if ( arg_green <= 5 )
  {
    T1CC1H  = 0x00;
    T1CC1L  = 0x01;
  }
  else if ( arg_green >= 254 )
  {
    T1CC1H  = 0x0f;
    T1CC1L  = 0xff;
  }
  else
  {
    T1CC1H  = pwm_green / 256;
    T1CC1L  = pwm_green % 256;


  }


#endif


}
void light_color_change_blue(unsigned char arg_blue)
{
#ifdef LIGHT_COLOR_BLUE

  if (arg_blue > 125)
  {
    P1_5 = 1;
  }
  else
  {
    P1_5 = 0;
  }

#endif

}











