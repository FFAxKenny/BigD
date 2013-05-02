/**
 * name: ejayt
 * date: 25 Feb 2013
 * team: pg
 * proj: umouse
 * file: mouse.c
 *
 */

#include "mouse.h"

int QueueAheadWall, QueueRightWall, QueueLeftWall;
mCell cubes[16][16];

void initializeMouse(Mouse* mouse) {
	mouse->ori = 0;
	mouse->row = 15;
	mouse->col = 0;
	int i,j;
	for (i = 0; i < 16; i++) {
            for(j = 0; j <16; j++) {
                cubes[i][j].distance = 0;
                cubes[i][j].north = 0;
                cubes[i][j].east = 0;
                cubes[i][j].south = 0;
                cubes[i][j].west = 0;
            }
	}
}


void floodMouseMap(Mouse* mouse) {
	// 1. Set variable lvl to 0
	int i, j;
	int lvl = 0;

	// 2. Initialize the distance values for the distance-flood
	// map to 255 indicating that it is not assigned
	initializeFloodMap();
	initializeCellWalls();


	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			printf("(%d,%d) == %d\n",i,j,cubes[i][j].distance);
		}
	}

	// 3. Place destination cubes in stack called currentLvl
	// Destination cubes are (7,7),(7,8),(8,7),(8,8)
	initializeStack(&currentLvl);
	for (i = 7; i < 9; i++) {
		for (j = 7; j < 9; j++) {
			Coordinates dest;
			dest.row = i;
			dest.col = j;
			push(&currentLvl, dest);
		}
	}
	printf("currentLvl.count: %d\n", currentLvl.count);

	// 4. Initialize a second array called nextLvl

	begin:
	// 5. While currentLvl is not empty
	while (currentLvl.count != 0) {
		// 6. Remove a cell from currentLvl
		Coordinates coor;
		coor = pop(&currentLvl);
		// 7. If Distance Value (cell) = 255 then let Distance Value = lvl
		if (cubes[coor.row][coor.col].distance == 255) {
			cubes[coor.row][coor.col].distance = lvl;
			push_unique(&oldCells, coor);
			// 7a. Place all open neighbors of cell into nextLvl
			initializeStack(&neigh);
			neighbors(&neigh, coor);
			append(&nextLvl, &neigh);
		}
		// 8. The currentLvl is now empty
	}
	if (nextLvl.count != 0) {
		lvl++;
		append(&currentLvl, &nextLvl);
		initializeStack(&nextLvl);
		goto begin;
	}
}

void moveLowestDistCell(Mouse* mouse) {
	// 1. Decide which neighbor has the lowest distance value
	Coordinates current;
	current.col = mouse->col;
	current.row = mouse->row;
	initializeStack(&neigh);
	neighbors(&neigh,current);

	Coordinates lowest;
	int c=0;
	while(neigh.count!=0) {
		Coordinates temp;
	//	printf("n.count: %d;\n",n.count);
		temp = pop(&neigh);
//		printf("temp.row: %d; temp.col: %d;\n",temp.row,temp.col);
		if(c==0 || (cubes[lowest.row][lowest.col].distance >
				cubes[temp.row][temp.col].distance )) {
			lowest = temp;
		}
		c++;
	}

	// 2. Move to that neighbor
	moveToNeighbor(mouse,current,lowest);
}


void moveToNeighbor(Mouse* mouse, Coordinates current, Coordinates lowest) {
	// Given that these two coordinates are neighbors!
	// 0123 = NESW
	int direction;

	int westOrEast = current.col - lowest.col;  // west if +1 east if -1
	int northOrSouth = current.row - lowest.row; //north if +1 south if -1


	if(westOrEast != 0) {
		if(westOrEast==1) {
			direction = 3;
		}
		else if(westOrEast==-1) {
			direction = 1;
		}
	}
	else if(northOrSouth != 0) {
		if(northOrSouth==1) {
			direction = 0;
		}
		else if(northOrSouth==-1) {
			direction = 2;
		}
	}

	if(mouse->ori==0) {
		if(direction == 0) {

		}
		else if(direction == 1) {
			right(mouse);
		}
		else if(direction == 2) {
			back(mouse);
		}
		else if(direction == 3) {
			left(mouse);
		}
	}
	if(mouse->ori==1) {
		if(direction == 0) {
			left(mouse);
		}
		else if(direction == 1) {

		}
		else if(direction == 2) {
			right(mouse);
		}
		else if(direction == 3) {
			back(mouse);
		}
	}
	if(mouse->ori==2) {
		if(direction == 0) {
			back(mouse);
		}
		else if(direction == 1) {
			left(mouse);
		}
		else if(direction == 2) {

		}
		else if(direction == 3) {
			right(mouse);
		}
	}
	if(mouse->ori==3) {
		if(direction == 0) {
			right(mouse);
		}
		else if(direction == 1) {
			back(mouse);
		}
		else if(direction == 2) {
			left(mouse);
		}
		else if(direction == 3) {

		}
	}
	forward(mouse,216);
}


void neighbors(Stack *neighbor, Coordinates coor) {
	int row = coor.row, col = coor.col;
	// It is only considered a neighbor if there is no wall seperating the two cubes
	if (!cubes[coor.row][coor.col].north) {
		Coordinates north;
		north.row = row - 1;
		north.col = col;
		if(!check(&oldCells,north)) push_unique(neighbor, north);
	}
	if (!cubes[coor.row][coor.col].east) {
		Coordinates east;
		east.row = row;
		east.col = col + 1;
		if(!check(&oldCells,east)) push_unique(neighbor, east);
	}
	if (!cubes[coor.row][coor.col].south) {
		Coordinates south;
		south.row = row + 1;
		south.col = col;
		if(!check(&oldCells,south)) push_unique(neighbor, south);
	}
	if (!cubes[coor.row][coor.col].west) {
		Coordinates west;
		west.row = row;
		west.col = col - 1;
		if(!check(&oldCells,west)) push_unique(neighbor, west);
	}
}

void initializeCellWalls() {
    int i, j;
    for(i=0;i<16;i++) {
        for(j=0;j<16;j++) {
            if(i==0) {
				cubes[i][j].north=1;
			}
			if(i==15) {
				cubes[i][j].south=1;
			}
			if(j==0) {
				cubes[i][j].west=1;
			}
			if(j==15) {
				cubes[i][j].east=1;
			}
        }
    }
}

void initializeFloodMap() {
	int i, j;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			cubes[i][j].distance = 255;
		}
	}
}


/*
void wallFollower(Maze *maze, Mouse *mouse) {
	int cNorth; int cEast;
	int cSouth;
	int cWest;
	int wallFront;
	int wallRight;
	int wallLeft;
	// See what walls are in the cell
	cNorth = maze.actualMap[mouse.row][mouse.col].north;
	cEast = maze.actualMap[mouse.row][mouse.col].east;
	cSouth = maze.actualMap[mouse.row][mouse.col].south;
	cWest = maze.actualMap[mouse.row][mouse.col].west;

	if (mouse.ori == 0) {
		wallFront = cNorth;
		wallRight = cEast;
		wallLeft = cWest;
	} else if (mouse.ori == 1) {
		wallFront = cEast;
		wallRight = cSouth;
		wallLeft = cNorth;
	} else if (mouse.ori == 2) {
		wallFront = cSouth;
		wallRight = cWest;
		wallLeft = cEast;
	} else {
		wallFront = cWest;
		wallRight = cNorth;
		wallLeft = cSouth;
	}

	// Decide where to turn
	if (!wallRight) {
		right(mouse);
		//       printf("Mouse turned right\n");
	} else if (!wallFront) {
		// Do Nothing
//        printf("Mouse did nothing\n");
	} else if (!wallLeft) {
		left(mouse);
		//       printf("Mouse turned left\n");
	} else {
		back(mouse);
		//      printf("Moused turned around\n");
	}
	MoveForward(mouse);
	//     printf("Mouse moved %d\n",mouse.ori);
}
 */

int finish(Mouse mouse) {
	return ((mouse.row == 8 && mouse.col == 8)
			|| (mouse.row == 7 && mouse.col == 7)
			|| (mouse.row == 7 && mouse.col == 8)
			|| (mouse.row == 8 && mouse.col == 7));
}

int getCurrCol(Mouse mouse) {
	return mouse.col;
}

int getCurrRow(Mouse mouse) {
	return mouse.row;
}

void forward(Mouse* mouse,int distance) {
    	/* Adjust orientation variable and mouse coordinates */
	  // the mouse is facing north
	if(mouse->ori == 0)
		mouse->row = mouse->row - 1; // north
	else if(mouse->ori == 1)
		mouse->col = mouse->col + 1; // east
	else if(mouse->ori == 2)
		mouse->row = mouse->row + 1;  // south
	else if(mouse->ori == 3)
		mouse->col = mouse->col - 1; // west
}

void left(Mouse* mouse) {
	// Adjust the ori for the mouse
	if (mouse->ori == 0)
		mouse->ori = 3;
	else if (mouse->ori == 1)
		mouse->ori = 0;
	else if (mouse->ori == 2)
		mouse->ori = 1;
	else if(mouse->ori == 3)
		mouse->ori = 2;
}

void right(Mouse* mouse) {
           	// Adjust ori for the mouse
    if (mouse->ori == 0)
		mouse->ori = 1;
	else if (mouse->ori == 1)
		mouse->ori = 2;
	else if (mouse->ori == 2)
		mouse->ori = 3;
	else if(mouse->ori == 3)
		mouse->ori = 0;
}
void back(Mouse* mouse) {
    right(mouse);
    right(mouse);
}

void update(Mouse* mouse) {
  	if(QueueAheadWall) {
        if(mouse->ori==0) {
		    cubes[mouse->row][mouse->col].north = 1;
		    if(mouse->row!=0) cubes[mouse->row-1][mouse->col].south = 1;
        }
        else if(mouse->ori==1) {
            cubes[mouse->row][mouse->col].east = 1;
            if(mouse->col!=15) cubes[mouse->row][mouse->col+1].west = 1;
        }
        else if(mouse->ori==2) {
            cubes[mouse->row][mouse->col].south = 1;
            if(mouse->row!=15)cubes[mouse->row+1][mouse->col].north = 1;
        }
        else if(mouse->ori==3) {
            cubes[mouse->row][mouse->col].west = 1;
            if(mouse->col!=0) cubes[mouse->row][mouse->col-1].east = 1;
        }
	}
	if(QueueRightWall) {
       if(mouse->ori==0) {
		    cubes[mouse->row][mouse->col].east = 1;
		    if(mouse->col!=15) cubes[mouse->row][mouse->col+1].west = 1;
        }
        else if(mouse->ori==1) {
            cubes[mouse->row][mouse->col].south = 1;
            if(mouse->row!=15) cubes[mouse->row+1][mouse->col].north = 1;
        }
        else if(mouse->ori==2) {
            cubes[mouse->row][mouse->col].west = 1;
            if(mouse->col!=0) cubes[mouse->row][mouse->col-1].east = 1;
        }
        else if(mouse->ori==3) {
            cubes[mouse->row][mouse->col].north = 1;
            if(mouse->row!=0) cubes[mouse->row-1][mouse->col].south = 1;
        }
	
	}
	if(QueueLeftWall) {
        if(mouse->ori==0) {
		    cubes[mouse->row][mouse->col].west = 1;
		    if(mouse->col!=0)cubes[mouse->row][mouse->col-1].east = 1;
        }
        else if(mouse->ori==1) {
            cubes[mouse->row][mouse->col].north = 1;
            if(mouse->row!=0)cubes[mouse->row-1][mouse->col].south = 1;
        }
        else if(mouse->ori==2) {
            cubes[mouse->row][mouse->col].east = 1;
            if(mouse->col!=15)cubes[mouse->row][mouse->col+1].west = 1;
        }
        else if(mouse->ori==3) {
            cubes[mouse->row][mouse->col].south = 1;
            if(mouse->row!=15)cubes[mouse->row+1][mouse->col].north = 1;
        }
	}
}

void queryMaze(Maze* maze, Mouse mouse) {
	if(mouse.ori == 0) {
		if(maze->actualMap[mouse.row][mouse.col].north) QueueAheadWall = 1;
		if(maze->actualMap[mouse.row][mouse.col].east) QueueRightWall = 1;
		if(maze->actualMap[mouse.row][mouse.col].west) QueueLeftWall = 1;
	}
	else if(mouse.ori == 1) {
		if(maze->actualMap[mouse.row][mouse.col].north) QueueLeftWall = 1;
		if(maze->actualMap[mouse.row][mouse.col].east) QueueAheadWall = 1;
		if(maze->actualMap[mouse.row][mouse.col].south) QueueRightWall = 1;
	}
	else if(mouse.ori == 2) {
		if(maze->actualMap[mouse.row][mouse.col].south) QueueAheadWall = 1;
		if(maze->actualMap[mouse.row][mouse.col].east) QueueLeftWall = 1;
		if(maze->actualMap[mouse.row][mouse.col].west) QueueRightWall = 1;
	}
	else if(mouse.ori == 3) {
		if(maze->actualMap[mouse.row][mouse.col].north) QueueRightWall = 1;
		if(maze->actualMap[mouse.row][mouse.col].south) QueueLeftWall = 1;
		if(maze->actualMap[mouse.row][mouse.col].west) QueueAheadWall = 1;
	}
	printf("queryMaze\n");
	printf("QueueAheadWall == %d", QueueAheadWall);
	printf("QueueLeftWall == %d", QueueLeftWall);
	printf("QueueRightWall == %d\n",QueueRightWall);
}
