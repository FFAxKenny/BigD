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
#define PERIOD          18000
#define PERIOD_SLOW     21000
#define PERIOD_FAST     17000

/* SENSOR CONSTANT */
#define CORR_CONSTANT   4000
#define VELOCITY        200

/* DRIVING MOVES CONSTANTS */
#define MOVE_FORWARD_COUNT  215
#define FACE_LEFT_COUNT     60
#define FACE_RIGHT_COUNT    61
#define FACE_BACK_COUNT     60

/* DRIVING DEFINITIONS */
#define FORWARD 0
#define REVERSE 1
#define LEFT    2
#define RIGHT   3


#ifdef	__cplusplus
}
#endif

#endif	/* MACROS_H */

