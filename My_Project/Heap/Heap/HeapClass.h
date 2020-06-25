#pragma once

const int MAX_HEAP_NODE = 200;
typedef int NODE;

class HeapClass
{
public:
	HeapClass();
	~HeapClass();

public:
	int IsEmpty();
	int IsFull();
	NODE Find();

public:
	void Initialize();
	void Insert(NODE n);
	NODE Delete();
	void Print();

private:
	int Key(NODE n);
	NODE Parent(NODE n);
	NODE Left(NODE n);
	NODE Right(NODE n);

private:
	NODE m_Heap[MAX_HEAP_NODE];
	int m_heapSize = 0;
};

