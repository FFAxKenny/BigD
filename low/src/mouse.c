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
	*mouse = (Mouse*) malloc(sizeof(Mouse));
	(*mouse)->ori = 0;
	(*mouse)->row = 15;
	(*mouse)->col = 0;
	(*mouse)->cells = (mCell**) malloc(sizeof(mCell*) * 16);
	memset((*mouse)->cells,0,sizeof((*mouse)->cells));
	int i;
	for (i = 0; i < 16; i++) {
		(*mouse)->cells[i] = (mCell*) malloc(sizeof(mCell) * 16);
		memset((*mouse)->cells[i],0,sizeof((*mouse)->cells[i]));
	}
}

void floodMouseMap(Mouse *mouse) {
	// 1. Set variable lvl to 0
	int i, j;
	int lvl = 0;

	// 2. Initialize the distance values for the distance-flood
	// map to 255 indicating that it is not assigned

	initializeFloodMap(mouse);
	// 3. Place destination cells in stack called currentLvl
	// Destination cells are (7,7),(7,8),(8,7),(8,8)
	Stack *currentLvl = initializeStack();
	for (i = 7; i < 9; i++) {
		for (j = 7; j < 9; j++) {
			Coordinates * dest = (Coordinates*)malloc(sizeof(Coordinates));
			dest->row = i;
			dest->col = j;
			push(currentLvl, dest);
		}
	}

	// 4. Initialize a second array called nextLvl
	Stack *nextLvl = initializeStack();

	begin:
	// 5. While currentLvl is not empty
	while (currentLvl->count != 0) {
		// 6. Remove a cell from currentLvl
		Coordinates *coor = (Coordinates*) malloc(sizeof(Coordinates));
		memset(coor, 0, sizeof(coor));
		coor = (Coordinates*)pop(currentLvl);
		// 7. If Distance Value (cell) = 255 then let Distance Value = lvl
		if (mouse->cells[coor->row][coor->col].distance == 255) {
			mouse->cells[coor->row][coor->col].distance = lvl;
			// 7a. Place all open neighbors of cell into nextLvl
			Stack * n = neighbors(coor, mouse);
			append(nextLvl, n);
			free(n);
		}
		// 8. The currentLvl is now empty
	}
	if (nextLvl->count != 0) {
		lvl++;
		append(currentLvl, nextLvl);
		free(nextLvl);
		nextLvl=initializeStack();
		goto begin;
	}
}

void updateMouseMapSim(Mouse* mouse, Maze* maze) {
	if(maze->actualMap[mouse->row][mouse->col].north) {
		mouse->cells[mouse->row][mouse->col].north = 1;
	}
	if(maze->actualMap[mouse->row][mouse->col].east) {
		mouse->cells[mouse->row][mouse->col].east = 1;
	}
	if(maze->actualMap[mouse->row][mouse->col].south) {
		mouse->cells[mouse->row][mouse->col].south = 1;
	}
	if(maze->actualMap[mouse->row][mouse->col].west) {
		mouse->cells[mouse->row][mouse->col].west = 1;
	}
}

void moveLowestDistCell(Mouse* mouse) {
	// 1. Decide which neighbor has the lowest distance value
	Coordinates* current = (Coordinates*)malloc(sizeof(Coordinates));
	memset(current,0,sizeof(current));
	current->col = mouse->col;
	current->row = mouse->row;
	Stack* n;
	n = neighbors(current,mouse);

	Coordinates * lowest = (Coordinates*)malloc(sizeof(Coordinates));
	int c=0;
	while(n->count!=0) {
		Coordinates* temp = (Coordinates*)malloc(sizeof(Coordinates));
	//	printf("n->count: %d;\n",n->count);
		temp = (Coordinates*)pop(n);
//		printf("temp->row: %d; temp->col: %d;\n",temp->row,temp->col);
		if(c==0 || (mouse->cells[lowest->row][lowest->col].distance >
				mouse->cells[temp->row][temp->col].distance )) {
			lowest = temp;
		}
		c++;
	}
		printf("new cell:\n");
		printf("lowest->row: %d; lowest->col: %d;\n",lowest->row,lowest->col);
		printf("mouse->cells[lowest->row][lowest->col].distance: %d\n", mouse->cells[lowest->row][lowest->col].distance);
		printf("mouse->cells[current->row][current->col].distance: %d\n", mouse->cells[current->row][current->col].distance);

	// 2. Move to that neighbor
	moveToNeighbor(mouse,current,lowest);
	free(current);
}

void moveToNeighbor(Mouse* mouse, Coordinates* current, Coordinates* lowest) {
	// Given that these two coordinates are neighbors!
	// 0123 = NESW
	int direction;
	printf("current->row: %d; current->col: %d;\n",current->row,current->col);

	int westOrEast = current->col - lowest->col;  // west if +1 east if -1
	int northOrSouth = current->row - lowest->row; //north if +1 south if -1
	printf("westOrEast: %d\n", westOrEast);
	printf("northOrSouth: %d\n", northOrSouth);

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
			faceRight(mouse);
		}
		else if(direction == 2) {
			faceBack(mouse);
		}
		else if(direction == 3) {
			faceLeft(mouse);
		}
	}
	if(mouse->ori==1) {
		if(direction == 0) {
			faceLeft(mouse);
		}
		else if(direction == 1) {

		}
		else if(direction == 2) {
			faceRight(mouse);
		}
		else if(direction == 3) {
			faceBack(mouse);
		}
	}
	if(mouse->ori==2) {
		if(direction == 0) {
			faceBack(mouse);
		}
		else if(direction == 1) {
			faceLeft(mouse);
		}
		else if(direction == 2) {

		}
		else if(direction == 3) {
			faceRight(mouse);
		}
	}
	if(mouse->ori==3) {
		if(direction == 0) {
			faceRight(mouse);
		}
		else if(direction == 1) {
			faceBack(mouse);
		}
		else if(direction == 2) {
			faceLeft(mouse);
		}
		else if(direction == 3) {

		}
	}
}

Stack* neighbors(Coordinates *coor, Mouse *mouse) {
	int row = coor->row, col = coor->col;
	Stack *neighbors = initializeStack();
	// It is only considered a neighbor if there is no wall seperating the two cells
	if (!mouse->cells[coor->row][coor->col].north) {
		Coordinates *north = (Coordinates*) malloc(sizeof(Coordinates));
		north->row = row - 1;
		north->col = col;
		push_unique(neighbors, north);
	}
	if (!mouse->cells[coor->row][coor->col].east) {
		Coordinates *east = (Coordinates*) malloc(sizeof(Coordinates));
		east->row = row;
		east->col = col + 1;
		push_unique(neighbors, east);
	}
	if (!mouse->cells[coor->row][coor->col].south) {
		Coordinates *south = (Coordinates*) malloc(sizeof(Coordinates));
		south->row = row + 1;
		south->col = col;
		push_unique(neighbors, south);
	}
	if (!mouse->cells[coor->row][coor->col].west) {
		Coordinates *west = (Coordinates*) malloc(sizeof(Coordinates));
		west->row = row;
		west->col = col - 1;
		push_unique(neighbors, west);
	}
	return neighbors;
}

void initializeFloodMap(Mouse* mouse) {
	int i, j;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			mouse->cells[i][j].distance = 255;
			if(i==0) {
				mouse->cells[i][j].north=1;
			}
			if(i==15) {
				mouse->cells[i][j].south=1;
			}
			if(j==0) {
				mouse->cells[i][j].west=1;
			}
			if(j==15) {
				mouse->cells[i][j].east=1;
			}
		}
	}
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
	cNorth = maze->actualMap[mouse->row][mouse->col].north;
	cEast = maze->actualMap[mouse->row][mouse->col].east;
	cSouth = maze->actualMap[mouse->row][mouse->col].south;
	cWest = maze->actualMap[mouse->row][mouse->col].west;

	if (mouse->ori == 0) {
		wallFront = cNorth;
		wallRight = cEast;
		wallLeft = cWest;
	} else if (mouse->ori == 1) {
		wallFront = cEast;
		wallRight = cSouth;
		wallLeft = cNorth;
	} else if (mouse->ori == 2) {
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
		faceRight(mouse);
		//       printf("Mouse turned right\n");
	} else if (!wallFront) {
		// Do Nothing
//        printf("Mouse did nothing\n");
	} else if (!wallLeft) {
		faceLeft(mouse);
		//       printf("Mouse turned left\n");
	} else {
		faceBack(mouse);
		//      printf("Moused turned around\n");
	}
	moveForward(mouse);
	//     printf("Mouse moved %d\n",mouse->ori);
}

int finish(Mouse *mouse) {
	return ((mouse->row == 8 && mouse->col == 8)
			|| (mouse->row == 7 && mouse->col == 7)
			|| (mouse->row == 7 && mouse->col == 8)
			|| (mouse->row == 8 && mouse->col == 7));
}

void faceRight(Mouse *mouse) {
	if (mouse->ori == 0)
		mouse->ori = 1;
	else if (mouse->ori == 1)
		mouse->ori = 2;
	else if (mouse->ori == 2)
		mouse->ori = 3;
	else if (mouse->ori == 3)
		mouse->ori = 0;
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
