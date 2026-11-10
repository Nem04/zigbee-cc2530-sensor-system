

#include "stepper_motor.h"
#include <ioCC2530.h>



///////////////////步进电机定义/////////////////////////////
//**********************正向旋转相序表*****************************
// static unsigned char FFW[8]={0x80,0xc0,0x40,0x60,0x20,0x30,0x10,0x90};
// //**********************反向旋转相序表*****************************
// static unsigned char REV[8]={0x90,0x10,0x30,0x20,0x60,0x40,0xc0,0x80};



// static unsigned char turn_right[4]={0x01,0x02,0x04,0x08};
// static unsigned char turn_left[4]={0x08,0x04,0x02,0x01};

static unsigned char turn_right[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};
static unsigned char turn_left[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};


static unsigned char  motor_count=0;


static unsigned char  motorFlag=0; //0:stop  1:right  2:left
static unsigned char  motorSpeed=5;  //1~5;  //1:slow   5:fast

static unsigned char flag_is_init = 0;



void stepper_motor_init()
{
    STEPPER_MOTOER_init();
    flag_is_init = 1;
}


void stepper_motor_set_mode(unsigned char mode_code)
{
    if(mode_code == STEPPER_MOTOER_MODE_LEFT )
    {
        motorFlag = STEPPER_MOTOER_MODE_LEFT;
    }
    else if (mode_code == STEPPER_MOTOER_MODE_RIGHT )
    {
        motorFlag = STEPPER_MOTOER_MODE_RIGHT;
    }
    else
    {
        motorFlag = STEPPER_MOTOER_MODE_STOP;
    }
    
}

void stepper_motor_set_speed(unsigned char speed)
{
 if(speed>STEPPER_MOTOER_SPEED_LV5)
 {
     motorSpeed = STEPPER_MOTOER_SPEED_LV5 ;
 }
 else
 {
     motorSpeed = speed ;
 }
 
}


void motor_parse_code(unsigned char code)
{
    // STEPPER_MOTOER_PIN_A = code & 0x01 ;
    // STEPPER_MOTOER_PIN_B = code & 0x02 ;
    // STEPPER_MOTOER_PIN_C = code & 0x04 ;
    // STEPPER_MOTOER_PIN_D = code & 0x08 ;


    STEPPER_MOTOER_PIN_A = !(code & 0x01) ;
    STEPPER_MOTOER_PIN_B = !(code & 0x02) ;
    STEPPER_MOTOER_PIN_C = !(code & 0x04) ;
    STEPPER_MOTOER_PIN_D = !(code & 0x08) ;
}


void motorCtrl()
{
    static unsigned char  motorIndex=0;
    
    if(motorFlag==STEPPER_MOTOER_MODE_RIGHT) //1:turn right 
    {
        motor_parse_code(turn_right[motorIndex]);
        
    }
    else if(motorFlag==STEPPER_MOTOER_MODE_LEFT) //2:turn left
    {
        motor_parse_code(turn_left[motorIndex]);
    }
    else  //stop:
    {
        motor_parse_code(0x00);
    }

    motorIndex++;
    if(motorIndex>=sizeof(turn_right))
    {
        motorIndex=0;
    }
}



void stepper_motor_trigger_1ms()
{

    if(flag_is_init=0) return ;

     motor_count++;

    if(motorSpeed==1)
    {
        motor_count++;
        if(motor_count>15)
        {
            motorCtrl();
            motor_count=0;
        }    
    }
    else if(motorSpeed==2)
    {
        motor_count++;
        if(motor_count>10)
        {
            motorCtrl();
            motor_count=0;
        }    
    }
    else if(motorSpeed==3)
    {
        motor_count++;
        if(motor_count>5)
        {
            motorCtrl();
            motor_count=0;
        }
    }
    else if(motorSpeed==4)
    {
        motor_count++;
        if(motor_count>1)
        {
            motorCtrl();
            motor_count=0;
        }
    }
    else
    {
        motorCtrl();
    }

}




