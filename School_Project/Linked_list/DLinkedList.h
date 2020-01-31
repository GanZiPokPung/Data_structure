#pragma once

#define TRUE  1
#define FALSE 0

typedef int LData;

typedef struct _node
{
	LData data;
	struct _node* next;
}Node;

typedef struct __linkedList
{
	Node * head;
	Node * cur;
	Node * before;
	int  numOfData;
	int(*comp)(LData d1, LData d2);
}LinkedList;

typedef LinkedList List;

//�ʱ�ȭ
void ListInit(List *plist);
//������ ����
void FInsert(List *plist, LData data);
void SInsert(List *plist, LData data);
void LInsert(List *plist, LData data);

//ù ������ ����
int LFirst(List *plist, LData *pdata);
//�� ���� ���� ������ ����
int LNext(List *plist, LData *pdata);

//������ ������ ����
LData LRemove(List *plist);
//���Ƶ� ������ �� ��ȯ
int LCount(List *plist);

void SetSortRule(List *plist, int(*comp)(LData d1, LData d2));