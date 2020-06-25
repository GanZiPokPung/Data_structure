#include "pch.h"
#include "ClassStack.h"

// ũ�⸦ �ø��ų� ���� ����
const int UNIT = 2;

ClassStack::~ClassStack()
{
	SAFE_DELETE_ARR<DATA**>(Container);
	SAFE_DELETE_ARR<DATA**>(ForSwap);
}

void ClassStack::Push(int number, int size, const char* data)
{
	// �����͸� �߰��Ѵ�.

	++Top;

	// ���� Container�� �迭�� �Ҵ�Ǿ� ���� ���� ���
	// �Ҵ��� ���ش�.
	if (nullptr == Container)
	{
		Size = UNIT;
		Container = new DATA*[Size];
	}

	// �߰��ϱ� �� �迭�� �������
	// ���Ҵ��Ͽ� �迭�� ũ�⸦ �ø���.
	if (Top == Size)
	{
		Size += UNIT;
		Swap(-UNIT);
	}
	
	// ���ο� �����͸� ���� �Ҵ��Ͽ� ������ Top��ġ�� �ִ´�.
	DATA* NewData = new DATA(number, size, data);
	Container[Top] = NewData;
}

void ClassStack::Pop(DATA* OutData)
{
	// Top�� �ִ� �����͸� �����Ҵ� �����ϰ�
	// OutData �����ͷ� �������Ͽ� Pop�� �����͸� �޴´�.

	// ���� ���ʿ��ϰ� �迭�� ũ�Ⱑ �����ִ� ���
	// ���Ҵ��Ͽ� �迭�� ũ�⸦ ���δ�.
	if ((Size - Top) > UNIT)
	{
		Size -= UNIT;
		Swap(0);
	}

	// OutData �����Ͱ� �ִ� ���
	// �����͸� �޴´�.
	if(nullptr != OutData)
		*OutData = *Container[Top];

	// Pop�� �����͸� �����Ҵ� �����Ѵ�.
	SAFE_DELETE<DATA*>(Container[Top]);
	--Top;
}

void ClassStack::Clear()
{
	// ������ �������� Pop�� �ݺ��Ѵ�.
	while (-1 != Top)
	{
		Pop(nullptr);
	}
	// �����̳� �迭�� �����Ҵ� �����Ѵ�.
	SAFE_DELETE_ARR<DATA**>(Container);
}

void ClassStack::Swap(int ChangeSize)
{
	// ForSwap�� Container�� �ִ� ��� ������ �����Ѵ�.
	ForSwap = new DATA*[Size];
	memcpy(ForSwap, Container, sizeof(DATA*) * (Size + ChangeSize));

	// Container�� �˸´� ũ��� ���Ҵ��ϰ� 
	// ForSwap�� �ִ� ������ �ٽ� Continer�� �����Ѵ�.
	SAFE_DELETE_ARR<DATA**>(Container);
	Container = new DATA* [Size];
	memcpy(Container, ForSwap, sizeof(DATA*) * (Size + ChangeSize));

	// �� ����� ForSwap�� �����Ҵ� ���������ش�.
	SAFE_DELETE_ARR<DATA**>(ForSwap);
}
