#pragma once
#include "NameCard.h"

#define TRUE		1
#define FALSE		0

#define LIST_LEN	100
typedef NameCard* LData;

typedef struct __ArrayList
{
	LData arr[LIST_LEN];
	int numOfData;
	int curPosition;
}ArrayList;

typedef ArrayList List;

//초기화
void ListInit(List *plist);
//데이터 저장
void LInsert(List *plist, LData data);

//첫 데이터 참조
int LFirst(List *plist, LData *pdata);
//두 번쨰 이후 데이터 참조
int LNext(List *plist, LData *pdata);

//참조한 데이터 삭제
LData LRemove(List *plist);
//저아된 데이터 수 반환
int LCount(List *plist);