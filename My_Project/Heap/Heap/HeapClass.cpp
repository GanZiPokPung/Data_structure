#include "pch.h"
#include "HeapClass.h"

HeapClass::HeapClass()
{
}

HeapClass::~HeapClass()
{
}

void HeapClass::Initialize()
{
	memset(m_Heap, 0, sizeof(NODE) * MAX_HEAP_NODE);
}

int HeapClass::IsEmpty()
{
	return (0 == m_heapSize);
}

int HeapClass::IsFull()
{
	return (MAX_HEAP_NODE - 1 == m_heapSize);
}

NODE HeapClass::Find()
{
	return m_Heap[1];
}

void HeapClass::Insert(NODE n)
{
	int i;
	if (IsFull())
		return;
	i = ++(m_heapSize);
	while (1 != i && Key(n) > Key(Parent(i)))
	{
		m_Heap[i] = Parent(i);
		i /= 2;
	}
	m_Heap[i] = n;
}

NODE HeapClass::Delete()
{
	NODE root, last;
	int parent = 1, child = 2;

	if (IsEmpty())
	{
		cout << "힙 트리 공백에러" << endl;
		exit(-1);
	}

	root = m_Heap[1];
	last = m_Heap[m_heapSize--];

	while (child <= m_heapSize)
	{
		if (child < m_heapSize && Key(Left(parent)) < Key(Right(parent)))
			++child;
		if (Key(last) >= Key(m_Heap[child]))
			break;
		m_Heap[parent] = m_Heap[child];
		parent = child;
		child *= 2;
	}
	m_Heap[parent] = last;
	return root;
}

void HeapClass::Print()
{
	int  level = 1;	
	for (int i = 1; i <= m_heapSize; ++i)
	{
		if (level == i)
		{
			cout << endl;
			level *= 2;
		}
		cout << Key(m_Heap[i]) << ' ' ;
	}
	cout << "\n-----------";
}

int HeapClass::Key(NODE n)
{
	return n;
}

NODE HeapClass::Parent(NODE n)
{
	return m_Heap[n / 2];
}

NODE HeapClass::Left(NODE n)
{
	return m_Heap[n * 2];
}

NODE HeapClass::Right(NODE n)
{
	return m_Heap[n * 2 + 1];
}
