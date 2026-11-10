#include <ioCC2530.h>
#include "OnBoard.h"
#include "dht11.h"
//#include "delay.h"


typedef unsigned char uchar;
typedef unsigned int  uint;




//温湿度定义
static uchar ucharFLAG,uchartemp;
static uchar ucharT_data_H,ucharT_data_L,ucharRH_data_H,ucharRH_data_L,ucharcheckdata;
static uchar ucharT_data_H_temp,ucharT_data_L_temp,ucharRH_data_H_temp,ucharRH_data_L_temp,ucharcheckdata_temp;
static uchar ucharcomdata;




static void Delay_us(unsigned int k) //1 us延时
{
    MicroWait(k);   
}


static  void Delay_ms(uint k)//n ms延时
{
  //unsigned char i;
  while(k--)
  {
    Delay_us(1000);
  }
}




//温湿度传感
static void COM(void)    // 温湿写入
{     
    uchar i;         
    for(i=0;i<8;i++)    
    {
        ucharFLAG=2; 
        while((!DHT11_DATA_PIN)&&ucharFLAG++);
        Delay_us(30);
        uchartemp=0;
        if(DHT11_DATA_PIN)uchartemp=1;
        ucharFLAG=2;
        while((DHT11_DATA_PIN)&&ucharFLAG++);   
        if(ucharFLAG==1)break;    
        ucharcomdata<<=1;
        ucharcomdata|=uchartemp; 
    }    
}

void Dht11_read(unsigned char * DHT11_wendu ,unsigned char * DHT11_shidu)   //温湿传感启动
{
  (void)ucharT_data_L;
  (void)ucharRH_data_L;
  (void)ucharcheckdata;
    DHT11_DATA_PIN_GPIO_MODE();
    Delay_us(10);;
    
    DHT11_DATA_PIN=0;
    Delay_ms(19);  //>18MS
    DHT11_DATA_PIN=1; 
    DHT11_DATA_PIN_IN(); //重新配置IO口方向
    Delay_us(40);  
    if(!DHT11_DATA_PIN) 
    {
        ucharFLAG=2; 
        while((!DHT11_DATA_PIN)&&ucharFLAG++);
        ucharFLAG=2;
        while((DHT11_DATA_PIN)&&ucharFLAG++); 
        COM();
        ucharRH_data_H_temp=ucharcomdata;
        COM();
        ucharRH_data_L_temp=ucharcomdata;
        COM();
        ucharT_data_H_temp=ucharcomdata;
        COM();
        ucharT_data_L_temp=ucharcomdata;
        COM();
        ucharcheckdata_temp=ucharcomdata;
        DHT11_DATA_PIN=1; 
        uchartemp=(ucharT_data_H_temp+ucharT_data_L_temp+ucharRH_data_H_temp+ucharRH_data_L_temp);
        if(uchartemp==ucharcheckdata_temp)
        {
            ucharRH_data_H=ucharRH_data_H_temp;
            ucharRH_data_L=ucharRH_data_L_temp;
            ucharT_data_H=ucharT_data_H_temp;
            ucharT_data_L=ucharT_data_L_temp;
            ucharcheckdata=ucharcheckdata_temp;
        }
  
        *DHT11_wendu = ucharT_data_H;      
        *DHT11_shidu = ucharRH_data_H; 

    } 
    else //没用成功读取，返回0
    {
        *DHT11_wendu = 0;      
        *DHT11_shidu = 0; 
    } 
    
    DHT11_DATA_PIN_OUT(); //IO口需要重新配置 
}


