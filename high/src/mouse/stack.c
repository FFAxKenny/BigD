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

int push_unique(Stack *stack, void *newElem) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	int i;
	for(i=0,newNode=stack->head; i<stack->count;i++,newNode=newNode->next) {
		if(memcmp(newNode->content,newElem,sizeof(int)*4) == 0) {
			return 1; //indicate failure
		}
	}
	push(stack,newElem); // re-use push
	return 0;
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



