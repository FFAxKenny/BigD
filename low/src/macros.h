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
#define WALL_AHEAD      320
#define NO_WALL         210
#define LEFT_WALL_MAX   580
#define LEFT_WALL_MIN   300
#define RIGHT_WALL_MAX  425
#define RIGHT_WALL_MIN  250


/* TIMER */
#define PERIOD          30000
    
/* DRIVING MOVES CONSTANTS */
#define MOVE_FORWARD_COUNT  229
#define FACE_LEFT_COUNT     300
#define FACE_RIGHT_COUNT    62

/* DRIVING DEFINITIONS */
#define FORWARD 0
#define REVERSE 1
#define LEFT    2
#define RIGHT   3


#ifdef	__cplusplus
}
#endif

#endif	/* MACROS_H */

