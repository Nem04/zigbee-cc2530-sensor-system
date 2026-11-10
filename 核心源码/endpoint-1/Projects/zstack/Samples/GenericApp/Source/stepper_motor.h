#ifndef  _STEPPER_MOTTOR_H_
#define  _STEPPER_MOTTOR_H_




#define STEPPER_MOTOER_PIN_A    P0_0
#define STEPPER_MOTOER_PIN_B    P0_1
#define STEPPER_MOTOER_PIN_C    P1_0
#define STEPPER_MOTOER_PIN_D    P1_1


#define STEPPER_MOTOER_init()   do{P0DIR |= ((1<<0)|(1<<1));\
    P0SEL &=~((1<<0)|(1<<1));\
    P1DIR |= ((1<<0)|(1<<1));\
    P1SEL &=~((1<<0)|(1<<1));\
    }while(0)


#define STEPPER_MOTOER_MODE_LEFT   1
#define STEPPER_MOTOER_MODE_RIGHT  2
#define STEPPER_MOTOER_MODE_STOP   3


#define STEPPER_MOTOER_SPEED_LV1   1
#define STEPPER_MOTOER_SPEED_LV2   2
#define STEPPER_MOTOER_SPEED_LV3   3
#define STEPPER_MOTOER_SPEED_LV4   4
#define STEPPER_MOTOER_SPEED_LV5   5




void stepper_motor_init();

void stepper_motor_trigger_1ms();

void stepper_motor_set_mode(unsigned char mode_code);

void stepper_motor_set_speed(unsigned char speed);


#endif

