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
    Mouse *mouse;
    maze=(Maze*)malloc(sizeof(Maze));
    printf("Uploading maze\n");
    uploadMaze(maze,argv[1]); // pass the path to the maze file

    int i, j;
    for(i=0;i<16;i++) {
        for(j=0;j<16;j++) {
            printf("(%d,%d)==%d%d%d%d\n",i,j,maze->actualMap[i][j].north,maze->actualMap[i][j].east,maze->actualMap[i][j].south,maze->actualMap[i][j].west);
        }
    }

    printf("upload successful\n");
    initializeMouse(&mouse);
    printf("Current Location: (%d,%d)\n",mouse->row,mouse->col); 
    while(!finish(mouse)) {
        wallFollower(maze,mouse); 
        printf("Current Location: (%d,%d)\n",mouse->row,mouse->col);
    }
    return 0;
}

