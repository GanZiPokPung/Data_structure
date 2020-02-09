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
	// �߰��� �����͸� ���� ���ο� ��带 �����.
	SNODE* newNode = new SNODE;
	memset(&newNode->data, 0, sizeof(DATA));
	newNode->data = data;
	newNode->next = nullptr;

	// head�� next�� ����ִ� ��� (empty�� ���)
	if (nullptr == m_head.next)
	{
		// head�� next�� ���� ���� ����� �ּҸ� �ִ´�.
		m_head.next = newNode;
	}
	else
	{
		// head ��忡�� ����
		SNODE* node = &m_head;

		// �߰��� �˸´� ������ ã�´�.
		while (nullptr != node->next)
		{
			// ������ ���� ���ο� ������ ���� ���� ���
			// Ȥ�� ���� ������ ���� �� ū ���
			if (node->data == newNode->data ||
				node->next->data > newNode->data)
			{
				// �߰��� ���� ���ش�.
				newNode->next = node->next;
				node->next = newNode;
				return;
			}
		
			node = node->next;
		}
		// ���� ������ ���
		node->next = newNode;
	}
}

void SingleLinkedList::Delete(DATA& data)
{
	// ��� �ִ��� �˻��Ѵ�.
	if (true == CheckEmpty())
	{
		cout << "Empty!" << endl;
		return;
	}

	// Head ������
	SNODE* node = &m_head;
	// �߰� ������ ��带 �̾� ���̱� ���� �� ��� �ּҰ� �ʿ��ϴ�.
	SNODE* preNode = nullptr;
	while (nullptr != node->next)
	{
		preNode = node;
		node = node->next;

		// �����Ϸ��� ���� �� ��带 ã�����
		if (data == node->data)
		{
			// �����Ϸ��� ��尣 ������ ����
			// �����ϱ� �� ���� ���� ��带 �̾���δ�.
			preNode->next = node->next;
			node->next = nullptr;
			// ��带 �����Ѵ�.
			delete node;
			node = nullptr;
			return;
		}	
	}
}

void SingleLinkedList::Clear()
{
	// Head ������ ��ȸ ���鼭 �����۾��� �Ѵ�.
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
	// ����� �����͸� ��� ����Ѵ�.
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
