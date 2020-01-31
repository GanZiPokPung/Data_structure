#pragma once

#define TRUE		1
#define FALSE		0
#define STACK_LEN	100

typedef int Data;

typedef struct _arrayStack
{
	Data stackArr[STACK_LEN];
	int topIndex;
}ArrayStack;

typedef ArrayStack Stack;

void StackInit(Stack *pstack);				//스택의 초기화
int	 SIsEmpty(Stack *pstack);				//스택이 비었는지 확인

void SPush(Stack *pstack, Data data);		//스택의 push
Data SPop(Stack *pstack);					//스택의 pop 
Data SPeek(Stack *pstack);					//스택의 peek