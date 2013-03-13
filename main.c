/* 
 * File:   main.c
 * Author: Doswah
 *
 * Created on March 13, 2013, 2:01 AM
 */

#if defined(__dsPIC33F__)
#include <p33FJ128MC802.h>
#include "DrivingMoves.h"
#include "MouseInit.h"
#include "Left_Motor.h"
#include "SensorADC.h"
#include <stdio.h>
#include <stdlib.h>
#endif

_FOSC(OSCIOFNC_ON & FCKSM_CSDCMD & POSCMD_NONE)    //Oscillator Configuration
_FOSCSEL(FNOSC_FRC)                                //Oscillator Selection
_FWDT(FWDTEN_OFF)                                  //Turn off WatchDog Timer
_FGS(GCP_OFF)                                      //Turn off code protect


#define FORWARD     5000
#define FACE_LEFT   5000
#define FACE_RIGHT  5000
#define FACE_BACK   5000
#define TURN_SPEED  1500

int main(void) {
    InitTimer_IO();                 // Initialize Timer & I/O
    InitBuzzer(PORTBbits.RB15);     // Wait for Start button to Start

    while(1) {
        Forward();                  // Test Forward Function
    }

    return (EXIT_SUCCESS);
}



