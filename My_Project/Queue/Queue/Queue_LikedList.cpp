#include "pch.h"
#include "Queue_LinkedList.h"

Queue_LinkedList::Queue_LinkedList()
{
	// Node를 초기화
	memset(&m_Front, 0, sizeof(NODE));
	memset(&m_Rear, 0, sizeof(NODE));
}

Queue_LinkedList::~Queue_LinkedList()
{
	ClearAll();
}

void Queue_LinkedList::Enqueue(const DATA & data)
{
	NODE* newNode = new NODE;
	newNode->data = data;
	newNode->link = nullptr;

	// 만약 큐가 비어있는 경우
	if (nullptr == m_Rear.link ||
		nullptr == m_Front.link)
	{
		// Front와 Rear가 모두 newNode를 가리킨다.
		m_Front.link = newNode;
		m_Rear.link = newNode;
	}
	else
	{
		// newNode는 Rear가 가리키는 노드 다음에 오고
		// Rear는 newNode를 가리키게된다.
		m_Rear.link->link = newNode;
		m_Rear.link = newNode;
	}
}

bool Queue_LinkedList::Dequeue(DATA * OutData)
{
	if(true == IsEmpty())
		return false;

	NODE* delNode = nullptr;
	if (nullptr != OutData)
		*OutData = m_Front.link->data;

	// 삭제할 Node는 Front가 가리키고 있다.
	delNode = m_Front.link;
	// Front가 그 다음 Node를 가리키도록 한다.
	m_Front.link = m_Front.link->link;

	// Node를 삭제한다.
	SAFE_DELETE<NODE>(delNode);

	return true;
}

void Queue_LinkedList::ClearAll()
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

void Queue_LinkedList::PrintAll()
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

bool Queue_LinkedList::PeekFront(DATA * OutData)
{
	if (true == IsEmpty())
		return false;
	if (nullptr != OutData)
		*OutData = m_Front.link->data;
	return true;
}

bool Queue_LinkedList::PeekRear(DATA * OutData)
{
	if (true == IsEmpty())
		return false;
	if(nullptr != OutData)
		*OutData = m_Rear.link->data;
	return true;
}

bool Queue_LinkedList::IsEmpty()
{
	return (nullptr == m_Front.link ||
			nullptr == m_Rear.link);
}
