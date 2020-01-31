#include "SimpleHeap.h"

// ���� �ʱ�ȭ
void HeapInit(Heap * ph)
{
	ph->numOfData = 0;
}

// ���� ������� Ȯ��
int HIsEmpty(Heap * ph)
{
	if (ph->numOfData == 0)
		return TRUE;
	else
		return FALSE;
}

// �θ� ����� �ε��� �� ��ȯ
int GetParentIDX(int idx)
{
	return idx / 2;
}

// ���� �ڽ� ����� �ε��� �� ��ȯ
int GetLChildIDX(int idx)
{
	return idx * 2;
}

// ������ �ڽ� ����� �ε��� �� ��ȯ
int GetRChildIDX(int idx)
{
	return GetLChildIDX(idx) + 1;
}

// �� ���� �ڽ� ��� �� ���� �켱������ �ڽ� ��� �ε��� �� ��ȯ
int GetHipriChildIDX(Heap *ph, int idx)
{
	// �ڽ� ��尡 �������� �ʴ´ٸ�
	if (GetLChildIDX(idx) > ph->numOfData)
		return 0;

	// �ڽ� ��尡 ���� �ڽ� ��� �ϳ��� �����Ѵٸ�
	else if (GetLChildIDX(idx) == ph->numOfData)
		return GetLChildIDX(idx);

	// �ڽ� ��尡 �� �� �����Ѵٸ�
	else
	{
		// ������ �ڽ� ����� �켱������ ���ٸ�,
		if (ph->heapArr[GetLChildIDX(idx)].pr
			> ph->heapArr[GetRChildIDX(idx)].pr)
			// ������ �ڽ� ����� �ε����� ��ȯ
			return GetRChildIDX(idx);

		// ���� �ڽ� ����� �켱������ ���ٸ�
		else
			// ���� �ڽ� ����� �ε����� ��ȯ
			return GetLChildIDX(idx);
	}
}

// ���� ������ ����
void HInsert(Heap * ph, HData data, Priority pr)
{
	int idx = ph->numOfData + 1;
	HeapElem nelem = { pr, data };

	while (idx != 1)
	{
		if (pr < (ph->heapArr[GetParentIDX(idx)].pr))
		{
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
			idx = GetParentIDX(idx);
		}
		else
			break;
	}

	ph->heapArr[idx] = nelem;
	ph->numOfData += 1;
}

// ������ ������ ����
HData HDelete(Heap * ph)
{
	// ��ȯ�� ���ؼ� ������ ������ ����
	HData retData = (ph->heapArr[1]).data;
	// ���� ������ ��� ����
	HeapElem lastElem = ph->heapArr[ph->numOfData];

	// �Ʒ��� ���� parentIdx���� ������ ��尡 ����� ��ġ������ ����.
	// ��Ʈ ��尡 ��ġ�ؾ� �� �ε��� �� ����
	int parentIdx = 1; 
	int childIdx;

	// ��Ʈ ����� �켱������ ���� �ڽ��� ��带 �������� �ݺ��� ����
	while (childIdx = GetHipriChildIDX(ph, parentIdx))
	{
		// ������ ���� �켱���� ��
		if (lastElem.pr <= ph->heapArr[childIdx].pr)
			// ������ ����� �켱������ ������ �ݺ��� Ż��
			break;
		
		// ������ ��庸�� �켱���� ������, �񱳴�� ����� ��ġ�� �� ���� �ø�
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		// ������ ��尡 ����� ��ġ������ �� ���� ����
		parentIdx = childIdx;
	}  // �ݺ��� Ż���ϸ� parentIDx���� ������ ����� ��ġ������ �����

	// ������ ��� ���� ����
	ph->heapArr[parentIdx] = lastElem;
	ph->numOfData -= 1;
	return retData;
}
