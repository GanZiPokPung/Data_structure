#include <stdio.h>
#include <stdlib.h>
#include "CListBaseStack.h"

void StackInit(Stack * pstack)
{
	pstack->tail = NULL;
}

int SIsEmpty(Stack * pstack)
{
	if (pstack->tail == NULL)
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack * pstack, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	
	newNode->data = data;

	if (pstack->tail == NULL)
	{
		newNode->prev = pstack->tail;
		pstack->tail = newNode;
	}
	else
	{
		newNode->prev = pstack->cur;
		pstack->tail->prev = newNode;
	}
	
	pstack->cur = newNode;
}

Data SPop(Stack * pstack)
{
	Data rData;
	Node* rNode;

	if (pstack->tail == NULL)
	{
		printf("Memory Error!\n");
		exit(-1);
	}
	
	rData = pstack->cur->data;
    rNode = pstack->cur;

	if (pstack->cur == pstack->tail)
	{
		pstack->tail = NULL;
	}
	else
	{
		pstack->cur = pstack->cur->prev;
		pstack->tail->prev = pstack->cur;
	}
	free(rNode);

	return rData;
}

Data SPeek(Stack * pstack)
{
	if (pstack->tail == NULL)
	{
		printf("Memory Error!\n");
		exit(-1);
	}

	return pstack->cur->data;
}
