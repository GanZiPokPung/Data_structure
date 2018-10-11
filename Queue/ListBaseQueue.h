#pragma once

#define TRUE	1
#define FALSE   0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node *next;
}Node;

typedef struct _lQueue
{
	Node* front; //그림을 통해서 F라 표현했던 멤버
	Node* rear;  //R
}LQueue;

typedef LQueue Queue;

void QueueInitialize(Queue* pq);
int QIsEmpty(Queue* pq);

void Enqueue(Queue* pq, Data data);
Data Dequeue(Queue* pq);
Data QPeek(Queue* pq);