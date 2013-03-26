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
    TheBirthOfBigD();               /* Initialize I/O, Start Switch, and ADC */
    ConfigureTimers();              /* Initialize Timer1 and Timer2 */

    /* README
     *
     * Motor control is controled by independent timers (Timer1: Left Motor)
     *  and (Timer2: Right Motor). CalcCorr() function used to calculate motor
     *  correction uses raw ADC1BUF0 value.
     *
     * Current correction is done with ONE sensor value (the right most sensor
     *  if you are looking at the mouse from behind. I COULD NOT FIGURE OUT HOW
     *  TO SAMPLE MORE THAN ONE SENSOR VALUE... GOOD LUCK WITH THAT :)
     *
     * while loop in main can call functions MoveFoward(distance) and
     *  FaceRight(). "distance" parameter in MoveFoward reflects the number
     *  of steps to travel one cell. The 215 paramteter is close to one cell
     *  travel. FaceRight() can be tweaked with FACE_RIGHT_COUNT in macros.h
     *
     *  FaceRight(), FaceLeft(), and FaceBack() not implemented yet.
     */

    //while(1){
        MoveForward(210);
        MoveForward(210);
        MoveForward(210);
        MoveForward(210);
        MoveForward(210);
        MoveForward(210);
    //}

    return (EXIT_SUCCESS);
}



