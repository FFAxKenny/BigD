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
_FGS(GCP_OFF)                                       // Turn off code protect


int main(void) {
    TheBirthOfBigD();               /* Initialize I/O and ADC */
    ConfigureTimers();              /* Initialize Timer1, Timer2 & Timer3 */

    while(1) {
        MoveForward(210);

    }


    return (EXIT_SUCCESS);
}



