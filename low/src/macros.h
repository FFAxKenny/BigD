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


/* SENSOR VALUES */
#define WALL_AHEAD      420
#define NO_WALL         110
#define LEFT_WALL_MAX   580
#define LEFT_WALL_MIN   200
#define RIGHT_WALL_MAX  300
#define RIGHT_WALL_MIN  200


/* TIMER */
#define PERIOD          22000
#define PERIOD_SLOW     25000
#define PERIOD_FAST     15000
    
/* DRIVING MOVES CONSTANTS */
#define MOVE_FORWARD_COUNT  229
#define FACE_LEFT_COUNT     62
#define FACE_RIGHT_COUNT    31

/* DRIVING DEFINITIONS */
#define FORWARD 0
#define REVERSE 1
#define LEFT    2
#define RIGHT   3


#ifdef	__cplusplus
}
#endif

#endif	/* MACROS_H */

