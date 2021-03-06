#pragma once

#define TRUE	1
#define FALSE   0

#define QUE_LEN 100
typedef int Data;

typedef struct _cQueue
{
	int front; //그림을 통해서 F라 표현했던 멤버
	int rear;  //R
	Data queArr[QUE_LEN];
}CQueue;

typedef CQueue Queue;

void QueueInitialize(Queue* pq);
int QIsEmpty(Queue* pq);

void Enqueue(Queue* pq, Data data);
Data Dequeue(Queue* pq);
Data QPeek(Queue* pq);