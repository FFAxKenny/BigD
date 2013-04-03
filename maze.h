/* 
 * File:   maze.h
 * Author: Doswah
 *
 * Created on March 29, 2013, 1:35 AM
 */

#ifndef MAZE_H
#define	MAZE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define DISP_HEIGHT 33
#define DISP_WIDTH  33
#define MAZE_HEIGHT 16
#define MAZE_WIDTH  16

typedef struct Cell {
    int dispCoord[2];
    int graphCoord[2];
    int north; // north wall
    int east;  // east
    int south; // south
    int west;  // west
} Cell;

typedef struct Maze { // a depiction of the maze
    Cell Map[MAZE_HEIGHT][MAZE_WIDTH];
} Maze;

//void uploadMaze(Maze *maze,char* mazeFilePath);
//void determineWalls(Maze *maze);


#ifdef	__cplusplus
}
#endif

#endif	/* MAZE_H */

