#pragma once

#define TRUE		1
#define FALSE		0
#define STACK_LEN	100

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node *prev;
}Node;

typedef struct _clistStack
{
	Node * tail;
	Node * cur;
}CListStack;

typedef CListStack Stack;

void StackInit(Stack *pstack);				//������ �ʱ�ȭ
int	 SIsEmpty(Stack *pstack);				//������ ������� Ȯ��

void SPush(Stack *pstack, Data data);		//������ push
Data SPop(Stack *pstack);					//������ pop 
Data SPeek(Stack *pstack);					//������ peek