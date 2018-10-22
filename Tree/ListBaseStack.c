#include <stdio.h>
#include <stdlib.h>
#include "ListBaseStack.h"

void StackInit(Stack * pstack)
{
	pstack->head = NULL;
}

int SIsEmpty(Stack * pstack)
{
	if (pstack->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack * pstack, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	
	newNode->next = pstack->head;
	newNode->data = data;

	pstack->head  = newNode;
}

Data SPop(Stack * pstack)
{
	Data rData;
	Node* rNode;

	if (pstack->head == NULL)
	{
		printf("Memory Error!\n");
		exit(-1);
	}
	
	rData = pstack->head->data;
    rNode = pstack->head;
	
	pstack->head = pstack->head->next;
	free(rNode);

	return rData;

}

Data SPeek(Stack * pstack)
{
	if (pstack->head == NULL)
	{
		printf("Memory Error!\n");
		exit(-1);
	}

	return pstack->head->data;
}
