#ifndef __DHT11_H__
#define __DHT11_H__


#define DHT11_DATA_PIN P0_7

#define DHT11_DATA_PIN_IN() do{P0DIR &= ~(1<<7);}while(0)
#define DHT11_DATA_PIN_OUT() do{P0DIR |= (1<<7);}while(0)
#define DHT11_DATA_PIN_GPIO_MODE() do{P0SEL &= ~(1<<7);}while(0)



void Dht11_read(unsigned char * DHT11_wendu ,unsigned char * DHT11_shidu);

#endif