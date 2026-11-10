#ifndef __DS18B20_H__
#define __DS18B20_H__

#define Ds18b20IO P0_7       //温度传感器引脚

#define Ds18b20OutputInitial() do{P0DIR |= (1<<7);}while(0)
#define Ds18b20InputInitial() do{P0DIR &= ~(1<<7);}while(0)
#define Ds18b20_PIN_GPIO_MODE() do{P0SEL &= ~(1<<7);}while(0)

extern unsigned char ReadDs18B20(void);
extern float floatReadDs18B20(void);
#endif