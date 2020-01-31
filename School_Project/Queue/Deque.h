#pragma once

//���� �����ε� �ڷε� ���� �� �ְ�, �����ε� �ڷε� �E �� �ִ� �ڷᱸ��.
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
	Node* head; //�׸��� ���ؼ� F�� ǥ���ߴ� ���
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