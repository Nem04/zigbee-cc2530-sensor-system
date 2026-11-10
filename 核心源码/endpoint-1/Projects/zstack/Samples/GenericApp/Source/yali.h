#ifndef _YALI_H_
#define _YALI_H_



#define HX711_DOUT P1_5
#define HX711_SCK  P1_6




#define HX711_DOUT_IN() do{P1DIR &= ~(1<<5);}while(0)
#define HX711_DOUT_GPIO_MODE() do{P1SEL &= ~(1<<5);}while(0)

#define HX711_SCK_OUT() do{P1DIR |= (1<<6);}while(0)
#define HX711_SCK_GPIO_MODE() do{P1SEL &= ~(1<<6);}while(0)


void yali_init(void);

void yali_Weight_calibration(void); //calibration the weight

int yali_Get_Weight(void);




#endif 