/**
 *  name: ejayt
 *  date: 25 Feb 2013
 *  team: pg
 *  proj: umouse
 *  file: sim.c
 *
 */

#include"../../util.h"

#include"../mouse/mouse.h"


int main(int argc, char* argv[]) {
    Maze *maze;
    Mouse mouse;
    QueueAheadWall=0;
    QueueRightWall=0;
    QueueLeftWall=0;
    maze=(Maze*)malloc(sizeof(Maze));
    printf("Uploading maze\n");
    uploadMaze(maze,argv[1]); // pass the path to the maze file

    printf("upload successful\n");
    mouse=initializeMouse();

        initializeCellWalls();
 //      while(!finish(mouse)) {
        	queryMaze(maze, mouse);
 //       	update(&mouse);
        	floodMouseMap(&mouse);
        	//moveLowestDistCell(&mouse);
        	printf("QueueAheadWall == %d", QueueAheadWall);
        	printf("QueueLeftWall == %d", QueueLeftWall);
        	printf("QueueRightWall == %d", QueueRightWall);


        int i, j;
        for(i=0;i<16;i++) {
        	for(j=0;j<16;j++) {
        		printf("(%d,%d)== %d %d%d%d%d\n",i,j,cubes[i][j].distance,cubes[i][j].north,cubes[i][j].east,cubes[i][j].south,cubes[i][j].west);
        	}
        }

        	//floodMouseMap(mouse);
        	//moveLowestDistCell(mouse);
        printf("Current Location: (%d,%d)\n",mouse.row,mouse.col);
//        }
    return 0;
}

