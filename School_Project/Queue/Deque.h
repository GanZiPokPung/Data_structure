#pragma once

//덱은 앞으로도 뒤로도 넣을 수 있고, 앞으로도 뒤로도 뺼 수 있는 자료구조.
#define TRUE	1
#define FALSE   0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node *next;
	struct _node *prev;
}Node;

typedef struct _dlDeque
{
	Node* head; //그림을 통해서 F라 표현했던 멤버
	Node* tail;  //R
}DLDeque;

typedef DLDeque Deque;

void DequeInitialize(Deque * pdeq);
int DQIsEmpty(Deque * pdeq);

void DQAddFirst(Deque * pdeq, Data data);
void DQAddLast(Deque * pdeq, Data data);

Data DQRemoveFirst(Deque * pdeq);
Data DQRemoveLast(Deque * pdeq);

Data DQGetFirst(Deque * pdeq);
Data DQGetLast(Deque * pdeq);