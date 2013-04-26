/*
 * stack.c
 *
 *  Created on: Mar 28, 2013
 *      Author: ejay
 */

#include"stack.h"

Stack* initializeStack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	memset(stack,0,sizeof(Stack));
	stack->count=0;
	stack->head=NULL;
	return stack;
}

void push(Stack *stack, void *newElem) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	memset(newNode,0,sizeof(newNode));
	newNode->next = stack->head;
	newNode->content = newElem;
	stack->head = newNode;
	stack->count++;
}

int push_unique(Stack *stack, void *newElem) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	memset(newNode,0,sizeof(newNode));
	int i;
	for(i=0,newNode=stack->head; i<stack->count;i++,newNode=newNode->next) {
		if(memcmp(newNode->content,newElem,sizeof(int)*4) == 0) {
			return 1; //indicate failure
		}
	}
	push(stack,newElem); // re-use push
	return 0;
}

Stack* add(Stack* one, Stack* two) {
	Stack* result = initializeStack();
	void *content=NULL;
	while(one->count!=0) {
		content=pop(one);
		push(result,content);
	}
	while(two->count!=0) {
		content=pop(two);
		push(result,content);
	}
	return result;
}

void append(Stack* result, Stack* appendee) {
	void* content=NULL;
	while(appendee->count!=0) {
		content=pop(appendee);
		push(result,content);
	}
}

void* pop(Stack *stack) {
	Node* temp = (Node*)malloc(sizeof(Node));
	memset(temp,0,sizeof(temp));
	void *r=NULL;
	if(stack->head != NULL) {
		temp = stack->head;
		r=stack->head->content;
		stack->head=stack->head->next;
		free(temp);
	}
	stack->count--;
	return r;
}



