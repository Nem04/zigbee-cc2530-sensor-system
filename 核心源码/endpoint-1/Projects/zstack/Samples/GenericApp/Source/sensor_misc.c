#include "sensor_misc.h"
#include <ioCC2530.h>


void SetSensor_Beep(unsigned char value)
{
  if (value)
  {
    SENSOR_PORT_Beep = !!SENSOR_PORT_Beep_Active;
  }
  else
  {
    SENSOR_PORT_Beep = !SENSOR_PORT_Beep_Active;
  }
}



unsigned char GetSensor_Renti(void)
{
  unsigned char     i   = 0;
  static unsigned char    record  = 0;
  unsigned char       state   = 0;
  if ( SENSOR_PORT_Renti == 1 )
  {
    state = 1;                      /*���˽��� */
  } else {
    for ( i = 0; i < 5; i++ )
    {
      if ( SENSOR_PORT_Renti == 1 )
      {
        state = 1;      /*���˽��� */
        break;
      }
      //MicroWait( 10000 );     /* Wait 10ms */
    }
  }

  if ( state == 1 )
  {
    record = ( (record << 1) | 0x01);
  } else {
    record = ( (record << 1) & (~0x01) );
  }

  if ( (record & 0x1f) == 0 )
  {
    return (0);
  } else {
    return (1);
  }
}







void SetSensor_Jidianqi(unsigned char value )
{
  if(value)
  {
    SENSOR_PORT_Jidianqi = 1;
  }
  else{
    SENSOR_PORT_Jidianqi = 0;
  }
}



void SetSensor_Jidianqi_2(unsigned char value )
{
  if(value)
  {
    SENSOR_PORT_Jidianqi_2 = 1;
  }
  else{
    SENSOR_PORT_Jidianqi_2 = 0;
  }
}

