#pragma once

class LinkedListStack
{
public:
	LinkedListStack();
	~LinkedListStack();

public:
	bool Push(NODE element);
	NODE Pop();
	NODE Peek();

	bool IsEmpty();

	void DeleteAll();

public:
	void PrintStack();

private:
	void CreateLinkedStack();
	void DeleteLinkedStack();

private:
	LLSTACK* m_stack = nullptr;
};

