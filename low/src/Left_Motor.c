/*
 *  Name: Left_Motor.c
 *
 *  StepMotor(speed, dir, phase)
 *
 *  SPEED:  250 = TOP SPEED
 *          2000 = SLOW SPEEDs
 *
 *  DIR:    0 = FORWARD
 *          1 = REVERSE
 *
 */

#if defined(__dsPIC33F__)
#include <p33FJ128MC802.h>
#include "Left_Motor.h"
#endif

void L_Motor(int speed, int dir, int phase) {
    volatile int cycle;
    if(dir == 0){                  // 0 FORWARD
        switch(phase) {
            case 1:
                for(cycle=0; cycle<speed; cycle++) {
                    LM1 = 1; LM2 = 0; LM3 = 1; LM4 = 0; } break;
            case 2:
                for(cycle=0; cycle<speed; cycle++) {
                    LM1 = 0; LM2 = 1; LM3 = 1; LM4 = 0; } break;
            case 3:
                for(cycle=0; cycle<speed; cycle++) {
                    LM1 = 0; LM2 = 1; LM3 = 0; LM4 = 1; } break;
            case 4:
                for(cycle=0; cycle<speed; cycle++) {
                    LM1 = 1; LM2 = 0; LM3 = 0; LM4 = 1; } break;
        }
    }

    if(dir == 1){                  // 1 REVERSE
        switch(phase) {
            case 4:
                for(cycle=0; cycle<speed; cycle++) {
                    LM1 = 1; LM2 = 0; LM3 = 1; LM4 = 0; } break;
            case 3:
                for(cycle=0; cycle<speed; cycle++) {
                    LM1 = 0; LM2 = 1; LM3 = 1; LM4 = 0; } break;
            case 2:
                for(cycle=0; cycle<speed; cycle++) {
                    LM1 = 0; LM2 = 1; LM3 = 0; LM4 = 1; } break;
            case 1:
                for(cycle=0; cycle<speed; cycle++) {
                    LM1 = 1; LM2 = 0; LM3 = 0; LM4 = 1; } break;
        }
    }

}