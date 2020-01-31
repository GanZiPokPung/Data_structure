#include "pch.h"
#include "SingleLinkedList.h"

SingleLinkedList::SingleLinkedList()
{
	m_head.next = nullptr;
}

SingleLinkedList::~SingleLinkedList()
{
	Clear();
}

void SingleLinkedList::Add(DATA& data)
{
	SNODE* newNode = new SNODE;
	memset(&newNode->data, 0, sizeof(DATA));
	newNode->data = data;
	newNode->next = nullptr;

	if (nullptr == m_head.next)
	{
		m_head.next = newNode;
	}
	else
	{
		SNODE* node = &m_head;
		while (nullptr != node->next)
		{
			node = node->next;
		}
		node->next = newNode;
	}
}

void SingleLinkedList::Delete(DATA& data)
{
	if (true == CheckEmpty())
	{
		cout << "Empty!" << endl;
		return;
	}

	SNODE* node = &m_head;
	SNODE* preNode = nullptr;
	while (nullptr != node->next)
	{
		preNode = node;
		node = node->next;
		if (data == node->data)
		{
			preNode->next = node->next;
			node->next = nullptr;
			delete node;
			node = nullptr;
			return;
		}	
	}
}

void SingleLinkedList::Clear()
{
	SNODE* node = &m_head;
	SNODE* eraseNode = nullptr;
	node = node->next;
	while (nullptr != node)
	{
		eraseNode = node;
		node = node->next;
		delete eraseNode;
		eraseNode = nullptr;
	}
	m_head.next = nullptr;
}

void SingleLinkedList::Print()
{
	if (true == CheckEmpty())
	{
		cout << "Empty!" << endl;
		return;
	}

	SNODE* node = &m_head;
	cout << "(HEAD) ---> ";
	node = node->next;
	while (nullptr != node)
	{
		cout << node->data.number << " ---> ";
		node = node->next;
	}
	cout << "nullptr" << endl;
}

bool SingleLinkedList::CheckEmpty()
{
	if (nullptr == m_head.next)
		return true;
	else
		return false;
}
