#pragma once
#include "Queue_Abstract.h"

class Queue_LinkedList
	: public Queue_Abstract
{
public:
	Queue_LinkedList();
	virtual ~Queue_LinkedList();
public:
	virtual void Enqueue(const DATA& data);
	virtual bool Dequeue(DATA* OutData);
	virtual void ClearAll();
	virtual void PrintAll();
	virtual bool PeekFront(DATA* OutData);
	virtual bool PeekRear(DATA* OutData);
	virtual bool IsEmpty();
private:
	NODE m_Front;
	NODE m_Rear;
};

