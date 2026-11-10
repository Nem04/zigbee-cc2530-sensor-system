#ifndef pulse_sensor_h
#define pulse_sensor_h


#define PULSE_SENSOR_LED  HAL_LED_1

/* 
初始化心率传感器
*/
void HeartRate_Init(void);

unsigned char GetCurrentHeartRate(void);



#endif