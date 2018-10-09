#include <stdio.h>
#include <stdlib.h>
#include "DBLinkedList.h"

void ListInit(List *plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->tail = (Node*)malloc(sizeof(Node));

	plist->head->next = plist->tail;
	plist->tail->prev = plist->head;

	plist->head->prev = NULL;
	plist->tail->next = NULL;
	
	plist->numOfData = 0;
}

void LInsert(List *plist, Data data)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	if (plist->head->next == plist->tail)
	{
		//머리
		plist->head->next = newNode;
		newNode->prev = plist->head;

		//꼬리
		plist->tail->prev = newNode;
		newNode->next = plist->tail;
	}
	else
	{
		//새 노드 다음 노드 이어줌
		newNode->next = plist->head->next;
		newNode->next->prev = newNode;

		//머리
		plist->head->next = newNode;
		newNode->prev = plist->head;
	}

	(plist->numOfData)++;
}

int LFirst(List *plist, Data *pdata)
{
	if (plist->head->next == plist->tail)
		return FALSE;

	plist->cur = plist->head->next;
	*pdata = plist->cur->data;
	return TRUE;
}

int RFirst(List * plist, Data * pdata)
{
	if (plist->tail->prev == plist->head)
		return FALSE;

	plist->cur = plist->tail->prev;
	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List *plist, Data *pdata)
{
	if (plist->cur->next == plist->tail)
		return FALSE;

	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;
	return TRUE;
}

void RInsert(List * plist, Data data)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	if (plist->tail->prev == plist->head)
	{
		//꼬리
		plist->tail->prev = newNode;
		newNode->next = plist->tail;

		//머리
		plist->head->next = newNode;
		newNode->prev = plist->head;
	}
	else
	{
		//새 노드 다음 노드 이어줌
		newNode->prev = plist->tail->prev;
		newNode->prev->next = newNode;

		//꼬리
		plist->tail->prev = newNode;
		newNode->next = plist->tail;
	}

	(plist->numOfData)++;
}

int LPrevious(List *plist, Data*pdata)
{
	if (plist->cur->prev == plist->head)
		return FALSE;

	plist->cur = plist->cur->prev;
	*pdata = plist->cur->data;
	return TRUE;
}

Data LRemove(List * plist)
{
	//현재 위치가 머리나 꼬리일때 
	if (plist->cur == plist->tail || plist->cur == plist->head)
		return FALSE;

	Node *rpos = plist->cur;
	Data data = rpos->data;
	
	//지울 노드의 전과 후 노드를 서로 연결
	rpos->prev->next = rpos->next;
	rpos->next->prev = rpos->prev;

	//cur위치를 내림
	plist->cur = rpos->prev;

	free(rpos);
	(plist->numOfData)--;

	return data;
}

int LCount(List *plist)
{
	return plist->numOfData;
}