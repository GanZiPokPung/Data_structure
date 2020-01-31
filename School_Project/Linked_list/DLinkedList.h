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

//초기화
void ListInit(List *plist);
//데이터 저장
void FInsert(List *plist, LData data);
void SInsert(List *plist, LData data);
void LInsert(List *plist, LData data);

//첫 데이터 참조
int LFirst(List *plist, LData *pdata);
//두 번쨰 이후 데이터 참조
int LNext(List *plist, LData *pdata);

//참조한 데이터 삭제
LData LRemove(List *plist);
//저아된 데이터 수 반환
int LCount(List *plist);

void SetSortRule(List *plist, int(*comp)(LData d1, LData d2));