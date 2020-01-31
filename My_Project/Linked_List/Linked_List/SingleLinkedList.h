#pragma once
#include "LinkedList.h"

class SingleLinkedList
	: public LinkedList
{
public:
	SingleLinkedList();
	virtual ~SingleLinkedList();

public:
	virtual void Add(DATA& data);
	virtual void Delete(DATA& data);
	virtual void Clear();
	virtual void Print();
	virtual bool CheckEmpty();

private:
	SNODE m_head;
};

