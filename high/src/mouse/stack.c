/*
 * stack.c
 *
 *  Created on: Mar 28, 2013
 *      Author: ejay
*/

#include"stack.h"

Stack currentLvl;
Stack neigh;
Stack nextLvl;
Stack oldCells;

void initializeStack(Stack* stack) {
	stack->count=0;
        int i;
        for(i=0;i<100;i++) {
            stack->coordinates[i].row = 255;
            stack->coordinates[i].col = 255;
        }
}

void push(Stack* stack, Coordinates newElem) {
    stack->coordinates[stack->count]=newElem;
    stack->count++;
}

int check(Stack* stack, Coordinates c) {
	int i;
	for(i=0;i<stack->count;i++) {
		if((stack->coordinates[i].col ==  c.col) &&
				(stack->coordinates[i].row ==  c.row)) return 1;
	}
	return 0;
}

int push_unique(Stack* stack, Coordinates newElem) {
    int i;
    for(i=0;i<stack->count;i++) {
        if(stack->coordinates[i].row == newElem.row &&
           stack->coordinates[i].col == newElem.col) {
            return 1;
        }
    }
    push(stack,newElem);
    return 0;
}

void add(Stack* result, Stack* one, Stack* two) {
	initializeStack(result);
	Coordinates content;
	while(one->count!=0) {
		content=pop(one);
		push(result,content);
	}
	while(two->count!=0) {
		content=pop(two);
		push(result,content);
	}
}

void append(Stack* result, Stack* appendee) {
	Coordinates content;
	while(appendee->count!=0) {
		content=pop(appendee);
		push(result,content);
	}
}


Coordinates pop(Stack* stack) {
    Coordinates r;
    r = stack->coordinates[stack->count-1];
    stack->coordinates[stack->count-1].col = 255;
    stack->coordinates[stack->count-1].row = 255;
    stack->count--;
	return r;
}
