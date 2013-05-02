/**
 *  name: ejayt
 *  date: 1 Mar 2013
 *  team: pg
 *  proj: umouse
 *  file: mouse.h
 *
 */

#include "stack.h"
#include "../env/maze.h"

/* Motor Declaration */


typedef struct mCell {
	unsigned north:1;
	unsigned east:1;
	unsigned south:1;
	unsigned west:1;
    int distance;
} mCell; //

typedef struct Mouse {
    int ori; // Orientation. Which way the mouse is facing. 0123=NESW
    int row; // Location. Where the mouse is in the maze
    int col;
} Mouse;

extern int QueueAheadWall, QueueRightWall, QueueLeftWall;
extern mCell cubes[16][16];

void initializeMouse(Mouse* mouse);
int finish(Mouse mouse);
int getCurrRow(Mouse mouse);
int getCurrCol(Mouse mouse);
//void wallFollower(Maze maze, Mouse mouse);
void floodMouseMap(Mouse* mouse);
void initializeCellWalls();
void initializeFloodMap();
void neighbors(Stack* neighbor, Coordinates coor);
void moveToNeighbor(Mouse* mouse, Coordinates current, Coordinates lowest);
void moveLowestDistCell(Mouse* mouse);
void forward(Mouse* mouse,int distance);
void left(Mouse* mouse);
void right(Mouse* mouse);
void back(Mouse* mouse);
void update(Mouse* mouse);
//void updateMouseMapSim(Mouse mouse, Maze maze);
void queryMaze(Maze* maze, Mouse mouse);

