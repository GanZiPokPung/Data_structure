#include "pch.h"
#include "ClassStack.h"

const int UNIT = 2;

ClassStack::~ClassStack()
{
	SAFE_DELETE_ARR<DATA**>(Container);
	SAFE_DELETE_ARR<DATA**>(ForSwap);
}

void ClassStack::Push(int number, int size, const char* data)
{
	++Top;

	if (nullptr == Container)
	{
		Size = UNIT;
		Container = new DATA*[Size];
	}

	if (Top == Size)
	{
		Size += UNIT;
		Swap(-UNIT);
	}
	
	DATA* NewData = new DATA(number, size, data);
	Container[Top] = NewData;
}

void ClassStack::Pop(DATA* OutData)
{
	if ((Size - Top) > UNIT)
	{
		Size -= UNIT;
		Swap(0);
	}

	if(nullptr != OutData)
		*OutData = *Container[Top];

	SAFE_DELETE<DATA*>(Container[Top]);
	--Top;
}

void ClassStack::Clear()
{
	while (-1 != Top)
	{
		Pop(nullptr);
	}
	SAFE_DELETE_ARR<DATA**>(Container);
}

void ClassStack::Swap(int ChangeSize)
{
	ForSwap = new DATA*[Size];
	memcpy(ForSwap, Container, sizeof(DATA*) * (Size + ChangeSize));

	SAFE_DELETE_ARR<DATA**>(Container);
	Container = new DATA* [Size];
	memcpy(Container, ForSwap, sizeof(DATA*) * (Size + ChangeSize));

	SAFE_DELETE_ARR<DATA**>(ForSwap);
}
