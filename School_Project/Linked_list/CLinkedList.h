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

//초기화
void ListInit(List *plist);
//꼬리에 노드를 추가
void LInsert(List *plist, Data data);
//머리에 노드를 추가
void LInsertFront(List *plist, Data data);

//첫 데이터 참조
int LFirst(List *plist, Data *pdata);
//두 번쨰 이후 데이터 참조
int LNext(List *plist, Data *pdata);

//참조한 데이터 삭제
Data LRemove(List *plist);
//저아된 데이터 수 반환
int LCount(List *plist);
