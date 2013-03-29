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
    int LeftReading;
    int RightReading;
    int sensorSelect;
    // Timer1 Interrupt controls Left Motor
    void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);
    // Timer2 Interrupt controls Right Motor
    void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void);

    void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void);

    void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void) {
        if(PORTBbits.RB15 == 1){
            T1CONbits.TON = 0;
            T2CONbits.TON = 0;
        }

    }



    void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void) {

        
        LMotor.LeftorRight = LEFT;              // Declare Left Motor
        
        if(LMotor.phase < 4) LMotor.phase++;    // Increment motor phase
        else LMotor.phase = 1;
        
        StepLMotor(LMotor);                     // Step Motor
        LMotor.step_count++;                    // Increment Motor Step Count
         _T1IF = 0;                             // Clear Timer1 interrupt flag
    }

    void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void) {

        
        RMotor.LeftorRight = RIGHT;             // Declare Right Motor
        
        // Calculate Correction
        ConvertADC(3); RightReading = CalcCorr();

        // Center, do not change timer
        PR1 = PERIOD;
        PR2 = PERIOD;

        // If too close to right wall, speed up timer
        if(RightReading > 1800) {
            PR1 = PERIOD_SLOW;
            PR2 = PERIOD;
        }

        // If too far from right wall, slow down timer
        else if(RightReading < 650) {
            PR1 = PERIOD;
            PR2 = PERIOD_SLOW; }
        

        if(RMotor.phase < 4) RMotor.phase++;    // Increment motor phase
        else RMotor.phase = 1;

        StepRMotor(RMotor);                     // Step Motor
        RMotor.step_count++;                    // Increment Motor Step Count
        _T2IF = 0;                              // Clear Timer1 interrupt flag
    }
    int i;
    void MoveForward(int distance) {

        // Reset step_count and spin LMotor Forward and RMotor Forward
        LMotor.direction = FORWARD;
        RMotor.direction = FORWARD;
        LMotor.step_count = 0;
        RMotor.step_count = 0;

        // Perform appropriate amount of steps to move forward one cell
        while(RMotor.step_count<distance);

        // Turn off timers and create Delay
        //T1CONbits.TON = 0;
        //T2CONbits.TON = 0;
        /*
         * for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
 */
        // Reconfigre Timers
        //ConfigureTimers();
    }

    void FaceRight(void){
        // Reset step_count and spin LMotor Forward and RMotor Reverse
        LMotor.step_count = 0;
        RMotor.step_count = 0;
        LMotor.direction = FORWARD;
        RMotor.direction = REVERSE;

        // Perform appropriate amount of steps to face right
        while(RMotor.step_count < FACE_RIGHT_COUNT);

        // Turn off timers and create Delay
        /*T1CONbits.TON = 0;
        T2CONbits.TON = 0;
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};
        for(i=0; i<6000; i++) {};

        // Reconfigre Timers
        ConfigureTimers();
         * */
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


    

