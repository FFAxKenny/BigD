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


    QueueAheadWall = 0;
    QueueRightWall = 1;
    QueueLeftWall = 1;
    wait();

    while(1) {


        if(QueueRightWall == 1 && QueueLeftWall == 1 && QueueAheadWall == 1)
        {
            FaceRight();
            FaceRight();
        }

        else if(QueueRightWall == 1 && QueueAheadWall == 1) {
                FaceLeft();
            }

        else if(QueueRightWall == 0) {
            FaceRight();
        }
        
            MoveForward(216);
        
            
        
    }
    
    
    return (EXIT_SUCCESS);
}



