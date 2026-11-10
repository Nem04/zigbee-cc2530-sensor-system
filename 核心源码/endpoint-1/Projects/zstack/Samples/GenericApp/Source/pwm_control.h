#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H



#define PWM_CH0 1 //通道1 P1_0
#define PWM_CH1 2 //通道1 P1_1

#define PWM_RED PWM_CH0 //通道1 P1_0
#define PWM_GREEN PWM_CH1//通道1 P1_1


void InitIO_PwmInit(void);


//Channel -- 通道号：PWM_CH0 1 //通道1 P1_0 通道1 P1_1
//period  --  pwm占空比   （ 0 - 255 )
void TurnPwm( unsigned char channel, unsigned char period );



#endif 