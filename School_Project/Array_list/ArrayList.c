#include<stdio.h>
#include"ArrayList.h"

//�ʱ�ȭ
void ListInit(List * plist)
{
	plist->numOfData = 0;
	plist->curPosition = -1;
}

//���� ä��
void LInsert(List * plist, LData data)
{
	if (plist->numOfData > LIST_LEN)
	{
		puts("������ �Ұ����մϴ�.");
		return;
	}

	//���� ä��� ����Ÿ ���� ����
	plist->arr[plist->numOfData] = data;
	(plist->numOfData)++;
}

//�� ó���� ������
int LFirst(List * plist, LData * pdata)
{
	if (plist->numOfData == 0)
		return FALSE;

	//��ġ�� 0���� ���� 0�� �ִ� arr�� ������
	(plist->curPosition) = 0;
	*pdata = plist->arr[0];
	return TRUE;
}

int LNext(List * plist, LData * pdata)
{
	//�ε������� ����Ÿ�� ������ �Ѿ�� FALSE
	if (plist->curPosition >= (plist->numOfData) - 1)
		return FALSE;

	//�ƴ϶�� ���� �ε������� ���� arr���� ������
	(plist->curPosition)++;
	*pdata = plist->arr[plist->curPosition];
	return TRUE;
}

//������ ������ ����
LData LRemove(List * plist)
{
	//��ġ(���� ������ ��ġ)
	int rpos = plist->curPosition;
	int num = plist->numOfData;
	int i;
	LData rdata = plist->arr[rpos];

	//���� �����͸� �迭�� ������ ������
	for (i = rpos; i < num - 1; i++)
		plist->arr[i] = plist->arr[i + 1];

	//������ ������ �����ǰ��� ���ҽ�Ŵ
	(plist->numOfData)--;
	(plist->curPosition)--;

	//������ �������� ���� ��ȯ
	return rdata;
}

int LCount(List * plist)
{
	return plist->numOfData;
}
