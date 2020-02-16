#pragma once
#include "Queue_Abstract.h"

const int UNIT = 2;

class Queue_Array
	: public Queue_Abstract
{
public:
	Queue_Array();
	virtual ~Queue_Array();

public:
	virtual void Enqueue(const DATA& data);
	virtual bool Dequeue(DATA* OutData);
	virtual void ClearAll();
	virtual void PrintAll();
	virtual bool PeekFront(DATA* OutData);
	virtual bool PeekRear(DATA* OutData);
	virtual bool IsEmpty();

private:
	void ChangeSize(int size);

private:
	DATA* m_Array = nullptr;
	DATA* m_ForSwap = nullptr;
	int m_Size = 0;

	int m_Front = 0;
	int m_Rear = 0;
};

