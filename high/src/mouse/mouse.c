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

void floodMouseMap(Maze *maze, Mouse *mouse) {
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
	printf("currentLvl->count = %d\n", currentLvl->count);

	// 4. Initialize a second array called nextLvl
	Stack *nextLvl = initializeStack();

	begin:
	// 5. While currentLvl is not empty
	while (currentLvl->count != 0) {
		// 6. Remove a cell from currentLvl
		Coordinates *coor = (Coordinates*) malloc(sizeof(Coordinates));
		memset(coor, 0, sizeof(coor));
		coor = (Coordinates*)pop(currentLvl);
		printf("coor->row: %d\n",coor->row);
		printf("coor->col: %d\n",coor->col);
		// 7. If Distance Value (cell) = 255 then let Distance Value = lvl
		if (mouse->cells[coor->row][coor->col].distance == 255) {
			mouse->cells[coor->row][coor->col].distance = lvl;
			// 7a. Place all open neighbors of cell into nextLvl
			printf("lvl: %d\n",lvl);
			Stack * n = neighbors(coor, mouse);
			printf("neighbors->count: %d\n",n->count);
			append(nextLvl, n);
			free(n);
			printf("currentLvl->count(while) = %d\n", currentLvl->count);
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
	printf("Stay pau");
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

void moveForward(Mouse *mouse) {
	// the mouse is facing north
	if (mouse->ori == 0)
		mouse->row = mouse->row - 1; //north
	else if (mouse->ori == 1)
		mouse->col = mouse->col + 1; // east
	else if (mouse->ori == 2)
		mouse->row = mouse->row + 1; // south
	else if (mouse->ori == 3)
		mouse->col = mouse->col - 1; // west
}

void faceLeft(Mouse *mouse) {
	if (mouse->ori == 0)
		mouse->ori = 3;
	else if (mouse->ori == 1)
		mouse->ori = 0;
	else if (mouse->ori == 2)
		mouse->ori = 1;
	else if (mouse->ori == 3)
		mouse->ori = 2;
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
