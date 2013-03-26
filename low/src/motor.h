/* 
 *  File:   motor.h
 *  Description: Motor struct for Left and Right Motor.
 *
 *  UH Manoa Micromouse | Team PG
 *
 */

#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct Motor {
      int speed;
      int step_count;
      int direction;
      int phase;
      int LeftorRight;
} Motor;

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

