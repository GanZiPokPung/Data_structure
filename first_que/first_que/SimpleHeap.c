#include "SimpleHeap.h"

// 힙의 초기화
void HeapInit(Heap * ph)
{
	ph->numOfData = 0;
}

// 힙이 비었는지 확인
int HIsEmpty(Heap * ph)
{
	if (ph->numOfData == 0)
		return TRUE;
	else
		return FALSE;
}

// 부모 노드의 인덱스 값 반환
int GetParentIDX(int idx)
{
	return idx / 2;
}

// 왼쪽 자식 노드의 인덱스 값 반환
int GetLChildIDX(int idx)
{
	return idx * 2;
}

// 오른쪽 자식 노드의 인덱스 값 반환
int GetRChildIDX(int idx)
{
	return GetLChildIDX(idx) + 1;
}

// 두 개의 자식 노드 중 높은 우선순위의 자식 노드 인덱스 값 반환
int GetHipriChildIDX(Heap *ph, int idx)
{
	// 자식 노드가 존재하지 않는다면
	if (GetLChildIDX(idx) > ph->numOfData)
		return 0;

	// 자식 노드가 왼쪽 자식 노드 하나만 존재한다면
	else if (GetLChildIDX(idx) == ph->numOfData)
		return GetLChildIDX(idx);

	// 자식 노드가 둘 다 존재한다면
	else
	{
		// 오른쪽 자식 노드의 우선순위가 높다면,
		if (ph->heapArr[GetLChildIDX(idx)].pr
			> ph->heapArr[GetRChildIDX(idx)].pr)
			// 오른쪽 자식 노드의 인덱스값 반환
			return GetRChildIDX(idx);

		// 왼쪽 자식 노드의 우선순위가 높다면
		else
			// 왼쪽 자식 노드의 인덱스값 반환
			return GetLChildIDX(idx);
	}
}

// 힙에 데이터 저장
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

// 힙에서 데이터 삭제
HData HDelete(Heap * ph)
{
	// 반환을 위해서 삭제할 데이터 저장
	HData retData = (ph->heapArr[1]).data;
	// 힙의 마지막 노드 저장
	HeapElem lastElem = ph->heapArr[ph->numOfData];

	// 아래의 변수 parentIdx에는 마지막 노드가 저장될 위치정보가 담긴다.
	// 루트 노드가 위치해야 할 인덱스 값 저장
	int parentIdx = 1; 
	int childIdx;

	// 루트 노드의 우선순위가 높은 자식의 노드를 시작으로 반복문 시작
	while (childIdx = GetHipriChildIDX(ph, parentIdx))
	{
		// 마지막 노드와 우선순위 비교
		if (lastElem.pr <= ph->heapArr[childIdx].pr)
			// 마지막 노드의 우선순위가 높으면 반복문 탈출
			break;
		
		// 마지막 노드보다 우선순위 높으니, 비교대상 노드의 위치를 한 레벨 올림
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		// 마지막 노드가 저장될 위치정보를 한 레벨 내림
		parentIdx = childIdx;
	}  // 반복문 탈출하면 parentIDx에는 마지막 노드의 위치정보가 저장됨

	// 마지막 노드 최종 저장
	ph->heapArr[parentIdx] = lastElem;
	ph->numOfData -= 1;
	return retData;
}
