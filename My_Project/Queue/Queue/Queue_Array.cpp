#include "pch.h"
#include "Queue_Array.h"


Queue_Array::Queue_Array()
{
	m_Size = UNIT;
	m_Array = new DATA[m_Size];
	memset(m_Array, 0, sizeof(DATA) * m_Size);
}

Queue_Array::~Queue_Array()
{
	ClearAll();
	SAFE_DELETE_ARRAY<DATA>(m_Array);
	SAFE_DELETE_ARRAY<DATA>(m_ForSwap);
}

void Queue_Array::Enqueue(const DATA & data)
{
	// 추가 후 사이즈가 배열 사이즈를 넘는다면
	if ((m_Rear + 1) - m_Front > m_Size)
	{
		// 배열 확장
		ChangeSize(+UNIT);
	}

	m_Array[m_Rear] = data;
	++m_Rear;
}

bool Queue_Array::Dequeue(DATA* OutData)
{	
	// 비어 있거나 데이터 return;
	if (true == IsEmpty())
		return false; 

	bool changeCheck = false;
	// 삭제 후 사이즈가 일정 크기만큼 작아진다면
	if (m_Rear - (m_Front + 1) <= m_Size - UNIT)
	{
		// 배열 축소
		changeCheck = true;
	}

	if(nullptr != OutData)
	{
		*OutData = m_Array[m_Front];
	}
	++m_Front;

	if(true == changeCheck &&
		false == IsEmpty())
		ChangeSize(-UNIT);
	
	return true;
}

void Queue_Array::ClearAll()
{
	m_Front = 0;
	m_Rear = 0;
}

void Queue_Array::PrintAll()
{
	if (true == IsEmpty())
	{
		cout << "Empty!" << endl;
		return;
	}

	int index = m_Front;
	int num = 0;

	while (m_Rear > index)
	{
		printf("[%d] - %d\n", num, m_Array[index].number);
		++index;
		++num;
	}
}

bool Queue_Array::PeekFront(DATA * OutData)
{
	if (true == IsEmpty())
		return false;
	if (nullptr != OutData)
		*OutData = m_Array[m_Front];
	return true;
}

bool Queue_Array::PeekRear(DATA * OutData)
{
	if (true == IsEmpty())
		return false;
	if (nullptr != OutData)
		*OutData = m_Array[m_Rear - 1];
	return true;
}

bool Queue_Array::IsEmpty()
{
	return (m_Front == m_Rear);
}

void Queue_Array::ChangeSize(int size)
{
	m_ForSwap = new DATA[m_Size];
	memset(m_ForSwap, 0, sizeof(DATA) * m_Size);
	memcpy(m_ForSwap, m_Array, sizeof(DATA) * m_Size);

	SAFE_DELETE_ARRAY(m_Array);
	m_Array = new DATA[m_Size + size];
	memset(m_Array, 0, sizeof(DATA) * (m_Size + size));

	if (0 > size)
	{
		int index = 0;
		for (int i = m_Front; i < m_Rear; ++i)
		{
			m_Array[index] = m_ForSwap[i];
			++index;
		}
		m_Rear -= m_Front;
		m_Front = 0;
	}
	else
	{
		memcpy(m_Array, m_ForSwap, sizeof(DATA) * m_Size);
	}

	SAFE_DELETE_ARRAY(m_ForSwap);
	m_Size += size;

	cout << "Current Size : " << m_Size << endl;
}
