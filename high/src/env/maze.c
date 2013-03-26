/**
 * name: ejayt
 * date: 25 Feb 2013
 * team: pg
 * proj: umouse
 * file: maze.c 
 *
 */

#include "maze.h"

void determineWalls(Maze *maze) {
    int i,j;
    int rowDisplayCoord,colDisplayCoord;
    for(i=0;i<16;i++) {
        for(j=0;j<16;j++) {
            rowDisplayCoord=maze->actualMap[i][j].dispCoord[0];
            colDisplayCoord=maze->actualMap[i][j].dispCoord[1];
            if(maze->displayMap[rowDisplayCoord-1][colDisplayCoord]==45) {
                maze->actualMap[i][j].north = 1;
            } else maze->actualMap[i][j].north = 0;
            if(maze->displayMap[rowDisplayCoord+1][colDisplayCoord]==45) {
                maze->actualMap[i][j].south = 1;
            } else maze->actualMap[i][j].south = 0;
            if(maze->displayMap[rowDisplayCoord][colDisplayCoord-1]==124) {
                maze->actualMap[i][j].west = 1;
            } else maze->actualMap[i][j].west = 0;
            if(maze->displayMap[rowDisplayCoord][colDisplayCoord+1]==124) {
                maze->actualMap[i][j].east = 1;
            } else maze->actualMap[i][j].east = 0;
        }
    }
}

/**
 * Function: uploadMaze()
 * Description: Uploads a .maz.txt file and inteprets its text representation into
 *              a Maze object. Which can then be used for maze simulation. 
 */
void uploadMaze(Maze *maze, char* mazeFilePath) {
    char line[35];
    FILE *mazeFile;
    
    mazeFile = fopen(mazeFilePath,"r");
    if(!mazeFile) {
        printf("Couldn't find maze file\n");
        exit(0);
    }
    else { 
        int row;
        int col;
        int cell_row;
        int cell_col;
        for(row=0;fgets(line,35,mazeFile)!=NULL;row++) {
            for(col=0;line[col]!=0;col++) {
                // printf("%d : ",line[col]);
                // printf("(%d,%d)\n",row,col);
                maze->displayMap[row][col] = line[col];
            }
        }
        
        cell_row=0;
        cell_col=0;
        for(row=0;row<33;row++) {
            for(col=0;col<33;col++) {
                if(col%2==1&&row%2==1) {
                     maze->actualMap[cell_row][cell_col].dispCoord[0]=row;
                     maze->actualMap[cell_row][cell_col].dispCoord[1]=col;
                     cell_col++;
                }
            }
           if(row%2==1&&col==0) {
               cell_row++;
           }
        }

       determineWalls(maze); 

    }
}
