#include "sensor_port.h"
#include <ioCC2530.h>
#include "hal_adc.h"

void Sensor_port_Init_AO0(void)
{
    HalAdcSetReference( HAL_ADC_REF_AVDD ); //3.3为参考电压
}


void Sensor_port_Init_AO1(void)
{
    HalAdcSetReference( HAL_ADC_REF_AVDD ); //3.3为参考电压
}
void Sensor_port_Init_AO2(void)
{
    HalAdcSetReference( HAL_ADC_REF_AVDD ); //3.3为参考电压
}




unsigned char   Sensor_port_Get_DO1(void)
{
  if (SENSOR_PORT_DO1 == 1)
    return 1;
  else
    return 0 ;
}


unsigned char   Sensor_port_Get_DO2(void)
{
  if (SENSOR_PORT_DO2 == 1)
    return 1;
  else
    return 0 ;

}


void Sensor_port_Set_DO1(unsigned char value)
{
    SENSOR_PORT_DO1 = !! value ;
}


void Sensor_port_Set_DO2(unsigned char value)
{
    SENSOR_PORT_DO1 = !! value ;
}


unsigned char   Sensor_port_Get_AO0(void)
{
    unsigned char value ;
    value = HalAdcRead( HAL_ADC_CHN_AIN0, HAL_ADC_RESOLUTION_8); 
    return value;
}




unsigned char   Sensor_port_Get_AO1(void)
{
    unsigned char value ;
    value = HalAdcRead( HAL_ADC_CHN_AIN5, HAL_ADC_RESOLUTION_8); 
    return value;
}




unsigned char   Sensor_port_Get_AO2(void)
{
  unsigned char value ;
  value = HalAdcRead( HAL_ADC_CHN_AIN6, HAL_ADC_RESOLUTION_8); 
  return value;
}







