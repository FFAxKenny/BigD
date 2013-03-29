/*
 * list.c
 *
 *  Created on: Mar 28, 2013
 *      Author: ejay
 */

#include"stack.h"

void push(Stack **stack, void *newElem) {
	Stack *newStack = malloc(sizeof(Stack));
	newStack->next = *stack;
	newStack->content = newElem;
	*stack = newStack;
}

void *pop(Stack **stack) {
	void *r=NULL;
	if(*stack != NULL) {
		Stack *temp = *stack;
		r=(*stack)->content;
		*stack=(*stack)->next;
		free(temp);
	}
	return r;
}



