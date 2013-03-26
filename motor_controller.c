/*
 *  File:   motor_controller.c
 *  Description: Forward, Face Left, Face Right, and Face Back Functions.
 *
 *  UH Manoa Micromouse | Team PG
 *
 */

#if defined(__dsPIC33F__)
#include <p33FJ128MC802.h>
#include "motor.h"
#include "init.h"
#include "motor_controller.h"
#include "SensorADC.h"
#include "macros.h"
#endif

    Motor LMotor;
    Motor RMotor;

    int stepCount;
    int sensorSelect;
    void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);
    
    void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void) {
                
        LMotor.LeftorRight = LEFT;
        RMotor.LeftorRight = RIGHT;

        StepLMotor(LMotor);
        StepRMotor(RMotor);

        if(LMotor.phase < 4) { LMotor.phase = LMotor.phase + 1;}
            else LMotor.phase = 1;
        if(RMotor.phase < 4) { RMotor.phase = RMotor.phase + 1;}
            else RMotor.phase = 1;
        

        _T1IF = 0;           //Clear Timer1 interrupt flag
    }
    
    
    void Move(Motor motor) {
            //ConvertADC();                             // Read Sensor Values
            //StepMotor(motor);                         // Pulse Motor
            // Increment motor phase
            //if(LMotor.phase < 3) { LMotor.phase = LMotor.phase + 1;}
            //else LMotor.phase = 1;
    }

void StepLMotor(Motor motor) {

    if(motor.direction == FORWARD) {
        switch(motor.phase) {
            case 1: RM1 = 1; RM2 = 0; RM3 = 1; RM4 = 0; break;
            case 2: RM1 = 0; RM2 = 1; RM3 = 1; RM4 = 0; break;
            case 3: RM1 = 0; RM2 = 1; RM3 = 0; RM4 = 1; break;
            case 4: RM1 = 1; RM2 = 0; RM3 = 0; RM4 = 1; break;
            }
        }
    

    if(motor.direction == REVERSE){
        switch(motor.phase) {
            case 1: RM1 = 1; RM2 = 0; RM3 = 1; RM4 = 0; break;
            case 4: RM1 = 0; RM2 = 1; RM3 = 1; RM4 = 0; break;
            case 3: RM1 = 0; RM2 = 1; RM3 = 0; RM4 = 1; break;
            case 2: RM1 = 1; RM2 = 0; RM3 = 0; RM4 = 1; break;
            }
    }
}

    void StepRMotor(Motor motor) {
        if(motor.direction == FORWARD) {
        switch(motor.phase) {
            case 1: LM1 = 1; LM2 = 0; LM3 = 1; LM4 = 0; break;
            case 2: LM1 = 0; LM2 = 1; LM3 = 1; LM4 = 0; break;
            case 3: LM1 = 0; LM2 = 1; LM3 = 0; LM4 = 1; break;
            case 4: LM1 = 1; LM2 = 0; LM3 = 0; LM4 = 1; break;
            }
        }

    if(motor.direction == REVERSE){
        switch(motor.phase) {
            case 1: LM1 = 1; LM2 = 0; LM3 = 1; LM4 = 0; break;
            case 4: LM1 = 0; LM2 = 1; LM3 = 1; LM4 = 0; break;
            case 3: LM1 = 0; LM2 = 1; LM3 = 0; LM4 = 1; break;
            case 2: LM1 = 1; LM2 = 0; LM3 = 0; LM4 = 1; break;
            }
        }
    }


    

