#include "pch.h"
#include "DoubleLinkedList.h"

DoubleLinkedList::DoubleLinkedList()
{
	// tail�� head�� ���� �������ش�.
	// ��� �ִ�.
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
	// �߰��� �����͸� ���� ���ο� ��带 �����.
	DNODE* newNode = new DNODE;
	newNode->data = data;
	newNode->prev = nullptr;
	newNode->next = nullptr;

	// ���� Empty�� ���
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
		// head ��忡�� ����
		DNODE* node = &m_head;

		// �߰��� �˸´� ������ ã�´�.
		while (&m_tail != node->next)
		{
			// ������ ���� ���ο� ������ ���� ���� ���
			// Ȥ�� ���� ������ ���� �� ū ���
			if (node->data == newNode->data ||
				node->next->data > newNode->data)
			{
				// �߰��� ���� ���ش�.
				newNode->next = node->next;
				node->next->prev = newNode;
				node->next = newNode;
				newNode->prev = node;
				return;
			}

			node = node->next;
		}

		// ���� ������ ���
		// �׳� tail�� ���̴� �װ��� �̿��Ͽ� �߰��ϸ� �ȴ�.
		newNode->next = &m_tail;
		newNode->prev = m_tail.prev;
		m_tail.prev->next = newNode;
		m_tail.prev = newNode;
	}
}

void DoubleLinkedList::Delete(DATA& data)
{
	// ��� �ִ��� �˻��Ѵ�.
	if (true == CheckEmpty())
	{
		cout << "Empty!" << endl;
		return;
	}

	// Head ������
	DNODE* node = &m_head;
	while (&m_tail != node->next)
	{
		node = node->next;

		// �����Ϸ��� ���� �� ��带 ã�����
		if (data == node->data)
		{
			// �����ϱ� �� ���� ���� ��带 ���� �̾���δ�.
			node->prev->next = node->next;
			node->next->prev = node->prev;
			// ��带 �����Ѵ�.
			delete node;
			node = nullptr;
			break;
		}
	}
}

void DoubleLinkedList::Clear()
{
	// Head ������ ��ȸ ���鼭 �����۾��� �Ѵ�.
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
	// ����� �����͸� ��� ����Ѵ�.
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
