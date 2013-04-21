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
    unsigned walls:4; // Wall values: xxxx = NESW (0 false | 1 true)
    int distance;
} mCell; //

typedef struct Mouse {
    int ori; // Orientation. Which way the mouse is facing. 0123=NESW
    int row; // Location. Where the mouse is in the maze
    int col;
    mCell* (*cells)[16];
} Mouse;

void initializeMouse(Mouse **mouse);
int finish(Mouse *mouse);
int getCurrRow(Mouse *mouse);
int getCurrCol(Mouse *mouse);
void moveForward(Mouse *mouse);
void faceLeft(Mouse *mouse);
void faceRight(Mouse *mouse);
void faceBack(Mouse *mouse);
void wallFollower(Maze *maze, Mouse *mouse);
void floodFill(Maze *maze, Mouse *mouse);
void flood(Maze *maze, Mouse *mouse);
