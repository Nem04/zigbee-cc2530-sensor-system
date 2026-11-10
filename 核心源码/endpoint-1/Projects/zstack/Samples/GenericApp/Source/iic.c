 

#include <ioCC2530.h>
#include "IIC.h"

#define  uchar unsigned  char 
#define  uint  unsigned  int
void IIC_Init(void)//IIC初始化
{
    // P0DIR |= 0xA0;      //P0.5、P0.7定义为输出

    MPU6050_SCK_GPIO_MODE();
    MPU6050_SDA_GPIO_MODE();
    MPU6050_SDA_OUT();
    MPU6050_SCK_OUT();


    MPU6050_SDA_PIN = 1;
    delay_1ms();
    MPU6050_SCK_PIN = 1;
    delay_1ms();
}

void Signal_Start(void)//IIC起始信号
{
    // P0DIR |= 0xA0;      //P0.5、P0.7定义为输出

    MPU6050_SCK_GPIO_MODE();
    MPU6050_SDA_GPIO_MODE();
    MPU6050_SDA_OUT();
    MPU6050_SCK_OUT();


    MPU6050_SDA_PIN = 1;
    delay_1ms();
    MPU6050_SCK_PIN = 1;
    delay_1ms();
    MPU6050_SDA_PIN = 0;
    delay_1ms(); 
}
void Signal_Stop(void)//IIC停止信号
{
    // P0DIR |= 0xA0;      //P0.5、P0.7定义为输出

    MPU6050_SCK_GPIO_MODE();
    MPU6050_SDA_GPIO_MODE();
    MPU6050_SDA_OUT();
    MPU6050_SCK_OUT();

    MPU6050_SDA_PIN = 0;
    delay_1ms();
    MPU6050_SCK_PIN = 1;
    delay_1ms();
    MPU6050_SDA_PIN = 1;
    delay_1ms(); 
}
void Respons(void)//答应信号
{
    uint i = 0;

    // P0DIR |= 0x20;      //P0.5定义为输出
    // P0DIR &= ~0x80;      //P0.7定义为输入

    MPU6050_SCK_OUT();
    MPU6050_SDA_IN();


    MPU6050_SCK_PIN = 1;
    delay_1ms();
    MPU6050_SCK_PIN = 0;
    delay_1ms();
    
    if(i>=300)
    {
      delay_1ms();
    }
}
void Write_Byte(uchar wdata)
{
    uchar i,mdata;

    // P0DIR |= 0xA0;      //P0.5、P0.7定义为输出


    // MPU6050_SCK_GPIO_MODE();
    // MPU6050_SDA_GPIO_MODE();
    MPU6050_SDA_OUT();
    MPU6050_SCK_OUT();


    mdata = wdata;
    for(i=0;i<8;i++)
    {        
        MPU6050_SCK_PIN = 0;
        delay_1ms();
        if(mdata & 0x80)
        {
          MPU6050_SDA_PIN = 1;
        }
        else
        {
          MPU6050_SDA_PIN = 0;
        }
        delay_1ms();
        MPU6050_SCK_PIN = 1;
        delay_1ms();  
        mdata <<= 1;
    }
    MPU6050_SCK_PIN = 0;
    delay_1ms();
    MPU6050_SCK_PIN = 1;
    delay_1ms();
}
uchar Read_Byte()
{
    uchar i,rdata = 0;

    // P0DIR |= 0x20;      //P0.5定义为输出
    // P0DIR &= ~0x80;      //P0.7定义为输入


    MPU6050_SCK_OUT();
    MPU6050_SDA_IN();

    MPU6050_SCK_PIN = 0;
    delay_1ms();
    MPU6050_SCK_PIN = 1;
    for(i=0;i<8;i++)
    {
        MPU6050_SCK_PIN = 1;
        delay_1ms();
        rdata = (rdata<<1)|MPU6050_SDA_PIN;
        MPU6050_SCK_PIN = 0;
        delay_1ms();
    }
    return rdata;
}
void Write_Add(uchar add,uchar wdata,uchar comd)
{
    Signal_Start(); //产生一个起始信号
    Write_Byte(comd);
    Respons();      //等待答应
    Write_Byte(add);
    Respons();      //等待答应
    Write_Byte(wdata);
    Respons();      //等待答应
    Signal_Stop();  //产生一个终止信号
}
uchar Read_Add(uchar add,uchar comd)
{
    uchar tdata;
    Signal_Start();     //产生一个起始信号
    Write_Byte(comd);
    Respons();          //等待答应
    Write_Byte(add);
    Respons();          //等待答应
    Signal_Start();     //再产生一个起始信号
    Write_Byte(comd|0x01);
    Respons();          //等待答应
    tdata = Read_Byte();
    Signal_Stop();      //产生一个终止信号
    return tdata;       
}
void delay_1ms(void)    //误差 0us  延时1ms
{
    uchar a,b,c;    
    for(c=4;c>0;c--)
    {
        //for(b=142;b>0;b--)
        {
            for(a=2;a>0;a--)
            {
            }
        }
    }
}
