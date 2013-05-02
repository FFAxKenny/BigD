/* Written by Rahul Anand
   http://eternalthinker.blogspot.com/2010/09/how-to-use-graphicsh-in-ubuntu.html */

#include<stdio.h>
#include<graphics.h>

#include"../mouse/mouse.h"

#define CW 25

typedef struct DisplayCoordinates {
    int x[16][16];
    int y[16][16];
} DisplayCoordinates;


void drawMaze();
void drawMouse();
void eraseMouse();
void drawCell(Cell cell,int x, int y, int red);
// void drawMouseAnim();
void solvingAlgorithm();


int mouseIsInCell(int row, int col);
void drawDistance();

DisplayCoordinates coord;
Mouse mouse;
Maze* maze;


int main(int argc, char* argv[]) {
 int gd=VGA,gm=VGAMAX;
 initgraph(&gd,&gm,NULL);

 maze=(Maze*)malloc(sizeof(Maze));
 initializeMouse(&mouse);
 uploadMaze(maze,argv[1]);

 setbkcolor(BLACK);
    drawMaze();

    int count = 0;
 while(!finish(mouse)) {

    setcolor(12);

    drawMouse();

    delay(100);
    eraseMouse();
    solvingAlgorithm();
    drawDistance();
    printf("move count: %d\n", count++);
 }
 getch();
 closegraph();
 
 return 0;
}

void solvingAlgorithm() {
    //wallFollower(maze,mouse);
	update(&mouse);
	floodMouseMap(&mouse);
	moveLowestDistCell(&mouse);
}


void drawMaze() {
int i,row,j,col;

	for(i=50,col=0; col<16; col++,i+=CW) {
		for(j=50,row=0; row<16; row++,j+=CW) {
		   drawCell(maze->actualMap[row][col],i,j,0);
           coord.x[row][col]=i;
           coord.y[row][col]=j;
        }
    }
}

int mouseIsInCell(int row, int col) {
   return (mouse.row==row || mouse.col==col);
}

/*
void Display::drawMouseAnim() {
    int i=coor->x[mouse->row][mouse->col];
    int j=coor->y[mouse->row][mouse->col];
    int orientation=mouse->ori;
    if(orientation==0) {
        for(j=j;j>coor->y[mouse->row-1][mouse->col];j--) {
            drawMouse(i,j);
            delay(10);
            eraseMouse(i,j);
        }
    }
    else if(orientation==1) {
        for(i=i;i<coor->x[mouse->row][mouse->col+1]+CW;i++) {
            drawMouse(i,j);
            delay(10);
            eraseMouse(i,j);
        }
    }
    else if(orientation==2) {
        for(j=j;j<coor->y[mouse->row+1][mouse->col]+CW;j++) {
            drawMouse(i,j);
            delay(10);
            eraseMouse(i,j);
        }
    }
    else if(orientation==3) {
        for(i=i;i>coor->x[mouse->row][mouse->col-1];i--) {
            drawMouse(i,j);
            delay(10);
            eraseMouse(i,j);
        }
    }
}
*/

void drawMouse() {
    int i=coord.x[mouse.row][mouse.col];
    int j=coord.y[mouse.row][mouse.col];
 
    setcolor(YELLOW);
    setlinestyle(0,0,2);
	rectangle(i+6,j+6, i+CW-6, j+CW-6);
    drawCell(maze->actualMap[mouse.row][mouse.col],i,j,1);
}

void eraseMouse() {
    int i=coord.x[mouse.row][mouse.col];
    int j=coord.y[mouse.row][mouse.col];
    
    int areaAroundMouse[]={i+2,j+2,i+2,j+CW-2,i+CW-2,j+2,i+CW-2,j+CW-2,i+CW-2,j+2,i+2,j+CW-2};
    setcolor(DARKGRAY);
    fillpoly(6, areaAroundMouse);
}

void drawCell(Cell cell, int x, int y, int red) {
    if(red) { 
        setcolor(RED);
    }
    else setcolor(LIGHTGRAY);
    setlinestyle(0,0,3);
	if(cell.north) { 
	   line(x,y,x+CW,y);
	}
	if(cell.east) { 
	   line(x+CW,y,x+CW,y+CW);
	}
	if(cell.south) { 
	   line(x,y+CW,x+CW,y+CW);
	}
	if(cell.west) { 
	   line(x,y,x,y+CW);
	}

}

void drawDistance() {
	int x, y;
	int i, j;
	char d[3];
	for(i=0;i<16;i++) {
		for(j=0;j<16;j++) {
			x = coord.x[i][j];
			y = coord.y[i][j];
			sprintf(d, "%d", cubes[i][j].distance);
			outtextxy(x+CW/4,y+CW/4,d);
		}
	}
}
