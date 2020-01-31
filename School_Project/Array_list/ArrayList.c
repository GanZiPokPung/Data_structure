#include<stdio.h>
#include"ArrayList.h"

//초기화
void ListInit(List * plist)
{
	plist->numOfData = 0;
	plist->curPosition = -1;
}

//값을 채움
void LInsert(List * plist, LData data)
{
	if (plist->numOfData > LIST_LEN)
	{
		puts("저장이 불가능합니다.");
		return;
	}

	//값을 채우고 데이타 갯수 증가
	plist->arr[plist->numOfData] = data;
	(plist->numOfData)++;
}

//맨 처음을 참조함
int LFirst(List * plist, LData * pdata)
{
	if (plist->numOfData == 0)
		return FALSE;

	//위치를 0으로 놓고 0에 있는 arr를 참조함
	(plist->curPosition) = 0;
	*pdata = plist->arr[0];
	return TRUE;
}

int LNext(List * plist, LData * pdata)
{
	//인덱스값이 데이타의 개수를 넘어서면 FALSE
	if (plist->curPosition >= (plist->numOfData) - 1)
		return FALSE;

	//아니라면 다음 인덱스값에 대한 arr값을 참조함
	(plist->curPosition)++;
	*pdata = plist->arr[plist->curPosition];
	return TRUE;
}

//참조한 데이터 삭제
LData LRemove(List * plist)
{
	//위치(지울 데이터 위치)
	int rpos = plist->curPosition;
	int num = plist->numOfData;
	int i;
	LData rdata = plist->arr[rpos];

	//지울 데이터를 배열의 끝으로 가져감
	for (i = rpos; i < num - 1; i++)
		plist->arr[i] = plist->arr[i + 1];

	//데이터 갯수와 포지션값을 감소시킴
	(plist->numOfData)--;
	(plist->curPosition)--;

	//삭제할 데이터의 값을 반환
	return rdata;
}

int LCount(List * plist)
{
	return plist->numOfData;
}
