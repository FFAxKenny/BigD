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

class Display {
        public:
	       Display(char *mazeFilePath);
	       ~Display();
           void drawMaze();
           void drawMouse();
           void eraseMouse();
	       void drawCell(Cell cell,int x, int y, bool red);
           void drawMouseAnim();
           void floodFill();
           void solvingAlgorithm();

           bool mouseIsInCell(int row, int col);

           Mouse* getMouse();
           Maze* getMaze();
        private:
           DisplayCoordinates* coor;
           Mouse *mouse;
           Maze *maze;
};

int main(int argc, char* argv[]) {
 int gd=VGA,gm=VGAMAX;
 initgraph(&gd,&gm,NULL);
 Display *display = new Display(argv[1]);

 setbkcolor(BLACK);
    display->drawMaze();

 while(!finish(display->getMouse())) {

    setcolor(12);            //outline heart

    display->drawMouse();
    delay(100);
    display->eraseMouse();
    display->solvingAlgorithm();
   
 }
 getch();
 display->~Display();
 closegraph();
 
 return 0;
}

void Display::floodFill() {
// flood the maze with values

}

void Display::solvingAlgorithm() {
    wallFollower(maze,mouse);
}

Display::Display(char* mazeFilePath) {
    maze=(Maze*)malloc(sizeof(Maze));
    //initializeMouse(mouse);
    mouse=(Mouse*)malloc(sizeof(Mouse));
    coor=(DisplayCoordinates*)malloc(sizeof(DisplayCoordinates));
    mouse->row=15; 
    mouse->col=0; 
    mouse->ori=0;
	
	uploadMaze(maze,mazeFilePath);
}

Display::~Display() {
	delete maze;
	delete mouse;
}

Mouse* Display::getMouse() {
    return mouse;
}

Maze* Display::getMaze() {
    return maze;
}

void Display::drawMaze() {
int i,row,j,col;

//    initializeMouse(mouse);
    //mouse->row=15;mouse->col=0;
	for(i=50,col=0; col<16; col++,i+=CW) {
		for(j=50,row=0; row<16; row++,j+=CW) {
		   drawCell(maze->actualMap[row][col],i,j,false);
           coor->x[row][col]=i;
           coor->y[row][col]=j;
        }
    }
}

bool Display::mouseIsInCell(int row, int col) {
   return (mouse->row==row || mouse->col==col);
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

void Display::drawMouse() {  
    int i=coor->x[mouse->row][mouse->col];
    int j=coor->y[mouse->row][mouse->col];
 
    setcolor(YELLOW);
    setlinestyle(0,0,2);
	rectangle(i+6,j+6, i+CW-6, j+CW-6);
    drawCell(maze->actualMap[mouse->row][mouse->col],i,j,true);
}

void Display::eraseMouse() {
    int i=coor->x[mouse->row][mouse->col];
    int j=coor->y[mouse->row][mouse->col];
    
    int areaAroundMouse[]={i+2,j+2,i+2,j+CW-2,i+CW-2,j+2,i+CW-2,j+CW-2,i+CW-2,j+2,i+2,j+CW-2};
    setcolor(DARKGRAY);
    fillpoly(6, areaAroundMouse);
}

void Display::drawCell(Cell cell, int x, int y, bool red) {
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
	//rectangle(x+4,y+4, x-4, y-4);
    //int n=12;
    //char c[2];
    //sprintf(c, "%d", n);
	// outtextxy(x+CW/4,y+CW/4,c);
}
