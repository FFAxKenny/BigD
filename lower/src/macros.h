/* 
 *  File:   macros.h
 *  Description: Holds macros for functions.
 *
 *  UH Manoa Micromouse | Team PG
 * 
 */

#ifndef MACROS_H
#define	MACROS_H

#ifdef	__cplusplus
extern "C" {
#endif

/* TIMER */
#define PERIOD 50000 //20000

/* SENSOR CONSTANT */
#define CORR_CONSTANT 200000    //200000
#define VELOCITY 200

/* DRIVING MOVES CONSTANTS */
#define FORWARD_COUNT     200
#define FACE_LEFT_COUNT   200
#define FACE_RIGHT_COUNT  200
#define FACE_BACK_COUNT   200

/* DRIVING DEFINITIONS */
#define FORWARD 0
#define REVERSE 1
#define LEFT    2
#define RIGHT   3


#ifdef	__cplusplus
}
#endif

#endif	/* MACROS_H */

