/*
 *  File:   main.c
 *  Description: Main source code for micromouse.
 *
 *  UH Manoa Micromouse | Team PG
 *
 */


#if defined(__dsPIC33F__)
#include <p33FJ128MC802.h>
#include "motor.h"
#include "init.h"
#include "SensorADC.h"
#include "macros.h"
#include "motor_controller.h"
#include <stdio.h>
#include <stdlib.h>
#endif


    

_FOSC(OSCIOFNC_ON & FCKSM_CSDCMD & POSCMD_NONE)     // Oscillator Configuration
_FOSCSEL(FNOSC_FRC)                                 // Select Internal FRC
_FWDT(FWDTEN_OFF)                                   // Turn off WatchDog Timer
_FGS(GCP_OFF)                                       // Turn off Code Protect


int main(void) {
    TheBirthOfBigD();               /* Initialize I/O, ADC, Timer, & Switch */

    TurnStage = 0;
    MoveStage = 0;
    QueueTurnStage = 0;
    //StopTracking = 0;

    while(1) {


        //MoveForward(300);
        if(QueueTurnStage == 1) {
            FaceRight();
        }
        
        

    }
    
    
    return (EXIT_SUCCESS);
}



