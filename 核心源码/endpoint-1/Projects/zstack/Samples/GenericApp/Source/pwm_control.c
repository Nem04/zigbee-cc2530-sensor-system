#include "iocc2530.h"
#include "OnBoard.h"
#include "pwm_control.h"







void InitIO_PwmInit(void)
{
  /*************************************************
  *  mode = 2:
  *
  *  ch 1 ---> p1_1
  *  ch 2 ---> p1_0
  *
  *
  *************************************************/
  CLKCONCMD &= ~0x40;             /* 设置系统时钟源为32MHZ晶振 */
  while ( CLKCONSTA & 0x40 )
    ;                       /* 等待晶振稳定为32M */
  CLKCONCMD &= ~0x07;       /* 设置系统主时钟频率为32MHZ */
  CLKCONCMD |= 0x38;        /* 时钟速度32 MHz 定时器标记输出设置[5:3]250kHz */

  PERCFG  |= 0x40;                /* 定时器1 的IO位置   1:备用位置2 */
  P2SEL &= ~0x10;               /* 定时器1优先 */
  P2DIR |= 0xC0;                /* 第1优先级：定时器1通道2-3 */


  P1DIR |= 0x03;                /* 端口1为输出 */
  P1SEL |= 0x03;                /* timer1 通道2映射口P1_0 p1_1*/

  T1CC0H  = 0x00;                 /* PWM duty cycle  周期 */
  T1CC0L  = 0xff;

  T1CCTL1 = 0x1c;                 /* 模式选择 通道1比较模式 */
  T1CC1H  = 0x00;
  T1CC1L  = 0x00;

  T1CCTL2 = 0x1c;                 /* 模式选择 通道2比较模式 */
  T1CC2H  = 0x00;
  T1CC2L  = 0x00;

  T1CTL = 0x02;                   /*不分频 */
}


void TurnPwm( unsigned char channel, unsigned char period )
{

  unsigned char pwm;


  

  pwm = 0xff - period +1;
  //pwm = 16 * pwm;


  if ( channel == 1)
  {

    T1CC2H  = 0;
    T1CC2L  = pwm;
  }else  {

    T1CC1H  = 0;
    T1CC1L  = pwm;
  }
}




