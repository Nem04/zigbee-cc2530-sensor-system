#include "yali.h"
#include <ioCC2530.h>


//if value is bigger  than it actually is , please increase this value;
//smaller , decrease this value.
#define GapValue 430


static unsigned long Weight_calibration = 0;
static long Weight_physical = 0;




static void Delay__hx711_us(unsigned int microSecs)
{
    while (microSecs--)
    { /* 32 NOPs == 1 usecs 因为延时还有计算的缘故，用了31个nop*/
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    }
}


// void Delay__hx711_us(void)
// {
// 	_nop_();
// 	_nop_();
// }





// unsigned long HX711_Read(void)	//ÔöÒæ128
// {
//     unsigned int limit = 60000;
// 	unsigned long count; 
// 	unsigned char i; 
//   	HX711_DOUT=1; 
// 	Delay__hx711_us(10);
//   	HX711_SCK=0; 
//   	count=0; 
//   	while(HX711_DOUT && limit--); 
//   	for(i=0;i<24;i++)
// 	{ 
// 	  	HX711_SCK=1; 
// 	  	count=count<<1; 
// 		Delay__hx711_us(1000);
// 		HX711_SCK=0; 
// 	  	if(HX711_DOUT)
// 			count++; 
// 		Delay__hx711_us(1000);
// 	} 
//  	HX711_SCK=1; 
//     count=count^0x800000;//µÚ25¸öÂö³åÏÂ½µÑØÀ´Ê±£¬×ª»»Êý¾Ý
// 	Delay__hx711_us(10);
// 	HX711_SCK=0;  
// 	return(count);
// }

void yali_init(void)
{
    HX711_DOUT_IN() ;
    HX711_DOUT_GPIO_MODE() ;

    HX711_SCK_OUT() ;
    HX711_SCK_GPIO_MODE() ;
}



unsigned long HX711_Read(void)	//增益128
{
	unsigned long count; 
	unsigned char i;
    unsigned int limit=50000;


    yali_init();

	HX711_DOUT=1;
	Delay__hx711_us(1);

	HX711_SCK=0;
	Delay__hx711_us(1);

  	count=0; 
  	while(HX711_DOUT && limit--); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
		Delay__hx711_us(1);
	  	count=count<<1; 
		HX711_SCK=0; 
		Delay__hx711_us(1);
	  	if(HX711_DOUT)
			count++; 
	} 
 	HX711_SCK=1; 
	count ^= 0x800000;
	Delay__hx711_us(1);
	HX711_SCK=0; 
	Delay__hx711_us(1);
	
	return(count);
}





void yali_Weight_calibration()
{
	Weight_calibration = HX711_Read();	
} 



int yali_Get_Weight()
{
    int result_value ;
	Weight_physical = HX711_Read();
	Weight_physical = Weight_physical - Weight_calibration;		
	if(Weight_physical > 0)			
	{	
		Weight_physical = (unsigned int)((float)Weight_physical/GapValue); 																		
	}
	else
	{
		Weight_physical = 0;		
	}

    result_value = (int)Weight_physical;
	return result_value;
}

