/*
 * stack.c
 *
 *  Created on: Mar 28, 2013
 *      Author: ejay
 */

#include"stack.h"

void initializeStack(Stack **stack) {
	*stack = (Stack*)malloc(sizeof(Stack));
	(*stack)->count=0;
	(*stack)->head=NULL;
}

void push(Stack *stack, void *newElem) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->next = stack->head;
	newNode->content = newElem;
	stack->head = newNode;
	stack->count++;
}

void *pop(Stack *stack) {
	void *r=NULL;
	if(stack->head != NULL) {
		Node *temp = stack->head;
		r=stack->head->content;
		stack->head=stack->head->next;
		free(temp);
	}
	stack->count--;
	return r;
}



