#ifndef __SENSOR_MISC_H__
#define __SENSOR_MISC_H__

/************************************************************************/
#define SENSOR_PORT_Beep_Active (0)
#define SENSOR_PORT_Beep   (P1_2)



#define  InitSensor_Beep() do{P1SEL &= ~(1<<2);\
    P1DIR |= (1<<2);\
    }while(0)    



void SetSensor_Beep(unsigned char value);


/************************************************************************/


#define SENSOR_PORT_Renti   (P0_4)


#define  InitSensor_Renti() do{P0SEL &= ~(1<<4);\
    P0DIR &= ~(1<<4);\
    }while(0)    



unsigned char GetSensor_Renti(void);

/************************************************************************/

#define SENSOR_PORT_Jidianqi   (P1_7)


#define  InitSensor_Jidianqi() do{P1SEL &= ~(1<<7);\
    P1DIR |= (1<<7);\
    SENSOR_PORT_Jidianqi=0;\
    }while(0)    



void SetSensor_Jidianqi(unsigned char value );



#define SENSOR_PORT_Jidianqi_2   (P1_5)


#define  InitSensor_Jidianqi_2() do{P1SEL &= ~(1<<5);\
    P1DIR |= (1<<5);\
    SENSOR_PORT_Jidianqi_2=0;\
    }while(0)    



void SetSensor_Jidianqi_2(unsigned char value );






#endif