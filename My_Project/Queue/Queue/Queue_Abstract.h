#pragma once
class Queue_Abstract
{
public:
	Queue_Abstract();
	virtual ~Queue_Abstract();
public:
	virtual void Enqueue(const DATA& data) = 0;
	virtual bool Dequeue(DATA* OutData) = 0;
	virtual void ClearAll() = 0;
	virtual void PrintAll() = 0;
	virtual bool PeekFront(DATA* OutData) = 0;
	virtual bool PeekRear(DATA* OutData) = 0;
	virtual bool IsEmpty() = 0;
};

