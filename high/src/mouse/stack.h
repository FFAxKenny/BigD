/*
 * stack.h
 *
 *  Created on: Mar 28, 2013
 *      Author: ejay
 */

#ifndef STACK_
#define STACK_

//#include"../../util.h"
#include<stdio.h>

typedef struct Coordinates {
    int row;
    int col;
} Coordinates;

typedef struct Stack {
    Coordinates coordinates[100];
    int count;
} Stack;

extern Stack currentLvl;
extern Stack neigh;
extern Stack nextLvl;
extern Stack oldCells;

void initializeStack(Stack* stack);
void append(Stack* result, Stack* appendee);
void push(Stack* stack, Coordinates coor);
Coordinates pop(Stack* stack);
int push_unique(Stack* stack, Coordinates coor);
void add(Stack* result, Stack* one, Stack* two);
int check(Stack* stack, Coordinates c);

#endif /* STACK_ */

