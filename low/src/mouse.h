/**
 *  name: ejayt
 *  date: 1 Mar 2013
 *  team: pg
 *  proj: umouse
 *  file: mouse.h
 *
 */

#include"../../util.h"
#include"../env/maze.h"
#include"stack.h"


typedef struct mCell {
	int north;
	int east;
	int south;
	int west;
    int distance;
} mCell; //

typedef struct Mouse {
    int ori; // Orientation. Which way the mouse is facing. 0123=NESW
    int row; // Location. Where the mouse is in the maze
    int col;
    mCell **cells;
} Mouse;

void initializeMouse(Mouse **mouse);
int finish(Mouse *mouse);
int getCurrRow(Mouse *mouse);
int getCurrCol(Mouse *mouse);
void wallFollower(Maze *maze, Mouse *mouse);
void floodMouseMap(Mouse *mouse);
void initializeFloodMap(Mouse* mouse);
Stack* neighbors(Coordinates *coor, Mouse *mouse);
void moveToNeighbor(Mouse* mouse, Coordinates* current, Coordinates* lowest);
void moveLowestDistCell(Mouse* mouse);
void updateMouseMapSim(Mouse* mouse, Maze* maze);

