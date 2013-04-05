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
#define WALL_AHEAD      400
#define NO_LEFT_WALL    230
#define NO_RIGHT_WALL   170 //200
    
#define LEFT_WALL_MAX   580
#define LEFT_WALL_MIN   350 //300

#define RIGHT_WALL_MAX  350
#define RIGHT_WALL_MIN  250


/* TIMER */
#define PERIOD          19000
    
/* DRIVING MOVES CONSTANTS */
#define MOVE_FORWARD_COUNT  214
#define FACE_LEFT_COUNT     60
#define FACE_RIGHT_COUNT    59

/* DRIVING DEFINITIONS */
#define FORWARD 0
#define REVERSE 1
#define LEFT    2
#define RIGHT   3


#ifdef	__cplusplus
}
#endif

#endif	/* MACROS_H */

