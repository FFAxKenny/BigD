/*
 *
 * File:   Left_Motor.h
 * Author: Joshua Rivera
 *
 * UH Manoa Micromouse
 * Team PG
 *
 * Function declarations for Left Motor Control.
 *
 *
 */

#define LM1 (LATBbits.LATB8)
#define LM2 (LATBbits.LATB9)
#define LM3 (LATBbits.LATB10)
#define LM4 (LATBbits.LATB11)

#ifndef LEFT_MOTOR_H
#define	LEFT_MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

void L_Motor(int speed, int dir, int phase);

#ifdef	__cplusplus
}
#endif

#endif	/* LEFT_MOTOR_H */

