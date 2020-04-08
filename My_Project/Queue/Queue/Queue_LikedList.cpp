#include "pch.h"
#include "Queue_LinkedList.h"

Queue_LinkedList::Queue_LinkedList()
{
	// Node�� �ʱ�ȭ
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

	// ���� ť�� ����ִ� ���
	if (nullptr == m_Rear.link ||
		nullptr == m_Front.link)
	{
		// Front�� Rear�� ��� newNode�� ����Ų��.
		m_Front.link = newNode;
		m_Rear.link = newNode;
	}
	else
	{
		// newNode�� Rear�� ����Ű�� ��� ������ ����
		// Rear�� newNode�� ����Ű�Եȴ�.
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

	// ������ Node�� Front�� ����Ű�� �ִ�.
	delNode = m_Front.link;
	// Front�� �� ���� Node�� ����Ű���� �Ѵ�.
	m_Front.link = m_Front.link->link;

	// Node�� �����Ѵ�.
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
