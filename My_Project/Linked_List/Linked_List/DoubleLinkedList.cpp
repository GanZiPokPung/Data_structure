#include "pch.h"
#include "DoubleLinkedList.h"

DoubleLinkedList::DoubleLinkedList()
{
	m_head.next = &m_tail;
	m_tail.prev = &m_head;

	m_head.prev = nullptr;
	m_tail.next = nullptr;

}

DoubleLinkedList::~DoubleLinkedList()
{
	Clear();
}

void DoubleLinkedList::Add(DATA& data)
{
	DNODE* newNode = new DNODE;
	newNode->data = data;
	newNode->prev = nullptr;
	newNode->next = nullptr;

	if (&m_tail == m_head.next &&
		&m_head == m_tail.prev)
	{
		m_head.next = newNode;
		newNode->prev = &m_head;
		m_tail.prev = newNode;
		newNode->next = &m_tail;
	}
	else
	{
		newNode->next = &m_tail;
		newNode->prev = m_tail.prev;
		m_tail.prev->next = newNode;
		m_tail.prev = newNode;
		
	}
}

void DoubleLinkedList::Delete(DATA& data)
{
	if (true == CheckEmpty())
	{
		cout << "Empty!" << endl;
		return;
	}

	DNODE* node = &m_head;
	while (&m_tail != node->next)
	{
		node = node->next;
		if (data == node->data)
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;
			node = nullptr;
			break;
		}
	}
}

void DoubleLinkedList::Clear()
{
	DNODE* node = &m_head;
	DNODE* eraseNode = nullptr;
	while (&m_tail != node->next)
	{
		node = node->next;
		eraseNode = node;
	}
	m_head.next = &m_tail;
	m_tail.prev = &m_head;
}

void DoubleLinkedList::Print()
{
	if (true == CheckEmpty())
	{
		cout << "Empty!" << endl;
		return;
	}

	DNODE* node = &m_head;
	cout << "HEAD <----> ";
	while (&m_tail != node->next)
	{
		node = node->next;
		cout << node->data.number << " <-----> ";
	}
	cout << "TAIL" << endl;
}

bool DoubleLinkedList::CheckEmpty()
{
	if (&m_tail == m_head.next ||
		&m_head == m_tail.prev)
		return true;
	else
		return false;
}
