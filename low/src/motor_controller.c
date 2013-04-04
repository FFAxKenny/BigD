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

int TurnStage, MoveStage, QueueTurnStage, StopTracking;

/* Motor Declaration */
    Motor LMotor;
    Motor RMotor;

    int i;

    /* Variables */
    volatile int Sensor1 = 0;
    volatile int Sensor2 = 0;
    volatile int Sensor3 = 0;
    volatile int Sensor4 = 0;
    
    /* Fucntion Declarations to Create Global Variables
    extern int TurnStage;           // If 1 = Performing Turn Function
    extern int MoveStage;           // If 1 = Spin Motors, 0 = Stop motors
    extern int QueueTurnStage;      // If 1 = Next Move Should Be A Turn
    void TurnStage_GlobalDeclaration(int num) { num+=TurnStage; }
    void MoveStage_GlobalDeclaration(int num) { num+=MoveStage; }
    void QueueTurnStage_GlobalDeclaration(int num) { num+=QueueTurnStage; }
    */

    

    void wait(void) {
        T1CONbits.TON = 0;
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        for(i=0; i<6000; i++);
        T1CONbits.TON = 1;

    }

    void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void) {


        Sensor1 = ReadADC(0);
        Sensor2 = ReadADC(1);
        Sensor3 = ReadADC(4);
        Sensor4 = ReadADC(5);

        /* PERFORM MAPPING STORAGE HERE */

        if(Sensor2+Sensor3 > WALL_AHEAD) QueueTurnStage = 1;


        if(MoveStage == 1) {

            if(TurnStage == 1) {
                if(LMotor.phase < 4) LMotor.phase++;    // Increment motor phase
                    else LMotor.phase = 1;
                if(RMotor.phase < 4) RMotor.phase++;
                    else RMotor.phase = 1;
                StepLMotor(LMotor);                     // Step Motors
                StepRMotor(RMotor);
                LMotor.step_count++;                // Increment Motor Step Count
                RMotor.step_count++;                // Increment Motor Step Count
             } // End TurnStage

            
            else {

                /* If there is right wall to track off... */
                if(Sensor4 > NO_WALL) {

                    
                    if(Sensor4 > RIGHT_WALL_MAX) {
                        if(RMotor.phase < 4) RMotor.phase++; else RMotor.phase = 1;
                        StepRMotor(RMotor);
                        RMotor.step_count++;
                    }

                    /* If Left Position, Step ONLY Left Motor*/
                    else if(Sensor4 > NO_WALL && Sensor4 < RIGHT_WALL_MIN) {
                        if(LMotor.phase < 4) LMotor.phase++; else LMotor.phase = 1;
                        StepLMotor(LMotor);
                        LMotor.step_count++;
                    }

                    else {
                        if(LMotor.phase < 4) LMotor.phase++; else LMotor.phase = 1;
                        if(RMotor.phase < 4) RMotor.phase++; else RMotor.phase = 1;
                        StepLMotor(LMotor);
                        StepRMotor(RMotor);
                        LMotor.step_count++;
                        RMotor.step_count++;
                    }
            }
                else {
                        if(LMotor.phase < 4) LMotor.phase++; else LMotor.phase = 1;
                        if(RMotor.phase < 4) RMotor.phase++; else RMotor.phase = 1;
                        StepLMotor(LMotor);
                        StepRMotor(RMotor);
                        LMotor.step_count++;
                        RMotor.step_count++;

                }

            }

        } // End MoveStage
         _T1IF = 0;                             // Clear Timer1 Interrupt Flag
    }























    void MoveForward(int distance) {

        MoveStage = 1;
        TurnStage = 0;
        
        // Reset Motor Step Count
        LMotor.step_count = 0;
        RMotor.step_count = 0;

        // Set Motor Direction
        LMotor.direction = FORWARD;
        RMotor.direction = FORWARD;

        // Step Motors until Distance obtained
        //while(RMotor.step_count<distance && LMotor.step_count<distance);
     
    }

    void FaceRight(void){

        MoveStage = 1;
        TurnStage = 1;

        // Reset Motor Step Count
        LMotor.step_count = 0;
        RMotor.step_count = 0;

        // Set Motor Direction
        LMotor.direction = FORWARD;
        RMotor.direction = REVERSE;

        // Perform appropriate amount of steps to face right
        while( RMotor.step_count < FACE_RIGHT_COUNT && LMotor.step_count < FACE_RIGHT_COUNT);

        //TurnStage = 0;
        QueueTurnStage = 0;
        

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


    


