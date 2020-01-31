#pragma once
#include "LinkedList.h"

class DoubleLinkedList
	:public LinkedList
{
public:
	DoubleLinkedList();
	virtual ~DoubleLinkedList();

public:
	virtual void Add(DATA& data);
	virtual void Delete(DATA& data);
	virtual void Clear();
	virtual void Print();
	virtual bool CheckEmpty();

private:
	DNODE m_head;
	DNODE m_tail;
};

