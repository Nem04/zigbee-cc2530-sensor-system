#ifndef _CHAOSHENGBO_H_
#define _CHAOSHENGBO_H_


#define Chaoshengbo_PIN_ECHO P1_5
#define Chaoshengbo_PIN_TRIG P1_6


#define Chaoshengbo_PIN_ECHO_IN() do{P1DIR &= ~(1<<5);}while(0)
#define Chaoshengbo_PIN_ECHO_IN_MODE() do{P1SEL &= ~(1<<5);}while(0)

#define Chaoshengbo_PIN_TRIG_OUT() do{P1DIR |= (1<<6);}while(0)
#define Chaoshengbo_PIN_TRIG_GPIO_MODE() do{P1SEL &= ~(1<<6);}while(0)


void chaoshengbo_init(void);

unsigned int  chaoshengbo_get_distance(void);

#endif