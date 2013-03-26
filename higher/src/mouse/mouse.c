/**
 * name: ejayt
 * date: 25 Feb 2013
 * team: pg
 * proj: umouse
 * file: mouse.c
 *
 */

#include"mouse.h"

void initializeMouse(Mouse **mouse) {
    *mouse = (Mouse*)malloc(sizeof(Mouse));
    (*mouse)->ori=0;
    (*mouse)->row=15;
    (*mouse)->col=0;
    // flood(mouse->mCell);
}

void wallFollower(Maze *maze, Mouse *mouse) {
    int cNorth;
    int cEast;
    int cSouth;
    int cWest;
    int wallFront;
    int wallRight;
    int wallLeft;
    // See what walls are in the cell
    cNorth=maze->actualMap[mouse->row][mouse->col].north;
    cEast=maze->actualMap[mouse->row][mouse->col].east;
    cSouth=maze->actualMap[mouse->row][mouse->col].south;
    cWest=maze->actualMap[mouse->row][mouse->col].west;

    if(mouse->ori==0) {
        wallFront=cNorth;
        wallRight=cEast;
        wallLeft=cWest;
    }
    else if(mouse->ori==1) {
        wallFront=cEast;
        wallRight=cSouth;
        wallLeft=cNorth;
    }
    else if(mouse->ori==2) {
        wallFront=cSouth;
        wallRight=cWest;
        wallLeft=cEast;
    }
    else {
        wallFront=cWest;
        wallRight=cNorth;
        wallLeft=cSouth;
    }

    // Decide where to turn
    if(!wallRight) {
        faceRight(mouse);
 //       printf("Mouse turned right\n");
    } 
    else if(!wallFront) {
        // Do Nothing
//        printf("Mouse did nothing\n");
    }
    else if(!wallLeft) {
        faceLeft(mouse);
 //       printf("Mouse turned left\n");
    }
    else {
        faceBack(mouse);
  //      printf("Moused turned around\n");
    }
    moveForward(mouse);
   //     printf("Mouse moved %d\n",mouse->ori);
}


int finish(Mouse *mouse) {
    return (mouse->row==8 && mouse->col==8); 
}

void moveForward(Mouse *mouse) {
    // the mouse is facing north
    if(mouse->ori==0) mouse->row=mouse->row-1; //north 
    else if(mouse->ori==1) mouse->col=mouse->col+1; // east 
    else if(mouse->ori==2) mouse->row=mouse->row+1; // south
    else if(mouse->ori==3) mouse->col=mouse->col-1; // west
}

void faceLeft(Mouse *mouse) {
    if(mouse->ori==0) mouse->ori=3;
    else if(mouse->ori==1) mouse->ori=0;
    else if(mouse->ori==2) mouse->ori=1;
    else if(mouse->ori==3) mouse->ori=2;
}

void faceRight(Mouse *mouse) {
    if(mouse->ori==0) mouse->ori=1;
    else if(mouse->ori==1) mouse->ori=2;
    else if(mouse->ori==2) mouse->ori=3;
    else if(mouse->ori==3) mouse->ori=0;
}

void faceBack(Mouse *mouse) {
    faceLeft(mouse);
    faceLeft(mouse);
}

int getCurrCol(Mouse * mouse) {
    return mouse->col;
}

int getCurrRow(Mouse * mouse) {
    return mouse->row;
}
