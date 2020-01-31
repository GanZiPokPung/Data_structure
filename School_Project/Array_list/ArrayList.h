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

//�ʱ�ȭ
void ListInit(List *plist);
//������ ����
void LInsert(List *plist, LData data);

//ù ������ ����
int LFirst(List *plist, LData *pdata);
//�� ���� ���� ������ ����
int LNext(List *plist, LData *pdata);

//������ ������ ����
LData LRemove(List *plist);
//���Ƶ� ������ �� ��ȯ
int LCount(List *plist);