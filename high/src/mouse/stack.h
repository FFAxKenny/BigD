/*
 * list
 *
 *  Created on: Mar 28, 2013
 *      Author: ejay
 */

#ifndef LIST_
#define LIST_

#include"../../util.h"

#define MAX 256

typedef struct Stack {
	void *content;
	struct Stack *next;
} Stack;

void push(Stack **stack, void *newElem);
void *pop(Stack **stack);

#endif /* LIST_ */
