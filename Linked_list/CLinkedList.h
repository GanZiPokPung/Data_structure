#pragma once

#define TRUE  1
#define FALSE 0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node* next;
}Node;

typedef struct __CLL
{
	Node * tail;
	Node * cur;
	Node * before;
	int  numOfData;
}CList;

typedef CList List;

//�ʱ�ȭ
void ListInit(List *plist);
//������ ��带 �߰�
void LInsert(List *plist, Data data);
//�Ӹ��� ��带 �߰�
void LInsertFront(List *plist, Data data);

//ù ������ ����
int LFirst(List *plist, Data *pdata);
//�� ���� ���� ������ ����
int LNext(List *plist, Data *pdata);

//������ ������ ����
Data LRemove(List *plist);
//���Ƶ� ������ �� ��ȯ
int LCount(List *plist);
