#include "pch.h"
#include "Queue_LInkedList.h"


Queue_LInkedList::Queue_LInkedList()
{
	memset(&m_Front, 0, sizeof(NODE));
	memset(&m_Rear, 0, sizeof(NODE));
}


Queue_LInkedList::~Queue_LInkedList()
{
	ClearAll();
}

void Queue_LInkedList::Enqueue(const DATA & data)
{
	NODE* newNode = new NODE;
	newNode->data = data;
	newNode->link = nullptr;

	if (nullptr == m_Rear.link ||
		nullptr == m_Front.link)
	{
		m_Front.link = newNode;
		m_Rear.link = newNode;
	}
	else
	{
		m_Rear.link->link = newNode;
		m_Rear.link = newNode;
	}
}

bool Queue_LInkedList::Dequeue(DATA * OutData)
{
	if(true == IsEmpty())
		return false;
	if (nullptr != OutData)
		*OutData = m_Front.link->data;
	
	m_Front.link = m_Front.link->link;


	return true;
}

void Queue_LInkedList::ClearAll()
{
	if (true == IsEmpty())
		return;

	NODE* delNode = nullptr;

	while (false == IsEmpty())
	{
		delNode = m_Front.link;
		m_Front.link = m_Front.link->link;
		SAFE_DELETE<NODE>(delNode);
	}
}

void Queue_LInkedList::PrintAll()
{
	NODE* Node = m_Front.link;

	int num = 0;
	while (nullptr != Node)
	{
		printf("[%d] - %d\n", num, Node->data.number);
		Node = Node->link;
		++num;
	}
}

bool Queue_LInkedList::PeekFront(DATA * OutData)
{
	if (true == IsEmpty())
		return false;
	if (nullptr != OutData)
		*OutData = m_Front.link->data;
	return true;
}

bool Queue_LInkedList::PeekRear(DATA * OutData)
{
	if (true == IsEmpty())
		return false;
	if(nullptr != OutData)
		*OutData = m_Rear.link->data;
	return true;
}

bool Queue_LInkedList::IsEmpty()
{
	return (nullptr == m_Front.link ||
			nullptr == m_Rear.link);
}
