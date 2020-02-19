#include "pch.h"
#include "ClassStack.h"

// 크기를 늘리거나 줄일 단위
const int UNIT = 2;

ClassStack::~ClassStack()
{
	SAFE_DELETE_ARR<DATA**>(Container);
	SAFE_DELETE_ARR<DATA**>(ForSwap);
}

void ClassStack::Push(int number, int size, const char* data)
{
	// 데이터를 추가한다.

	++Top;

	// 만약 Container가 배열로 할당되어 있지 않은 경우
	// 할당을 해준다.
	if (nullptr == Container)
	{
		Size = UNIT;
		Container = new DATA*[Size];
	}

	// 추가하기 전 배열이 꽉찬경우
	// 재할당하여 배열의 크기를 늘린다.
	if (Top == Size)
	{
		Size += UNIT;
		Swap(-UNIT);
	}
	
	// 새로운 데이터를 동적 할당하여 스택의 Top위치에 넣는다.
	DATA* NewData = new DATA(number, size, data);
	Container[Top] = NewData;
}

void ClassStack::Pop(DATA* OutData)
{
	// Top에 있는 데이터를 동적할당 해제하고
	// OutData 포인터로 역참조하여 Pop할 데이터를 받는다.

	// 만약 불필요하게 배열의 크기가 잡혀있는 경우
	// 재할당하여 배열의 크기를 줄인다.
	if ((Size - Top) > UNIT)
	{
		Size -= UNIT;
		Swap(0);
	}

	// OutData 포인터가 있는 경우
	// 데이터를 받는다.
	if(nullptr != OutData)
		*OutData = *Container[Top];

	// Pop할 데이터를 동적할당 해제한다.
	SAFE_DELETE<DATA*>(Container[Top]);
	--Top;
}

void ClassStack::Clear()
{
	// 스택이 빌때까지 Pop을 반복한다.
	while (-1 != Top)
	{
		Pop(nullptr);
	}
	// 컨테이너 배열을 동적할당 해제한다.
	SAFE_DELETE_ARR<DATA**>(Container);
}

void ClassStack::Swap(int ChangeSize)
{
	// ForSwap에 Container에 있는 모든 정보를 복사한다.
	ForSwap = new DATA*[Size];
	memcpy(ForSwap, Container, sizeof(DATA*) * (Size + ChangeSize));

	// Container를 알맞는 크기로 재할당하고 
	// ForSwap에 있는 정보를 다시 Continer에 복사한다.
	SAFE_DELETE_ARR<DATA**>(Container);
	Container = new DATA* [Size];
	memcpy(Container, ForSwap, sizeof(DATA*) * (Size + ChangeSize));

	// 다 사용한 ForSwap은 동적할당 해제시켜준다.
	SAFE_DELETE_ARR<DATA**>(ForSwap);
}
