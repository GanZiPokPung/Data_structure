#pragma once
class LinkedList
{
public:
	LinkedList() {}
	virtual ~LinkedList() {}

public:
	virtual void Add(DATA& data) = 0;
	virtual void Delete(DATA& data) = 0;
	virtual void Clear() = 0;
	virtual void Print() = 0;
	virtual bool CheckEmpty() = 0;
};

