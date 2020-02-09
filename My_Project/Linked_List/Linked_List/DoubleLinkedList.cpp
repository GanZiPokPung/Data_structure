#include "pch.h"
#include "DoubleLinkedList.h"

DoubleLinkedList::DoubleLinkedList()
{
	// tail과 head를 서로 연결해준다.
	// 비어 있다.
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
	// 추가할 데이터를 가진 새로운 노드를 만든다.
	DNODE* newNode = new DNODE;
	newNode->data = data;
	newNode->prev = nullptr;
	newNode->next = nullptr;

	// 만약 Empty인 경우
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
		// head 노드에서 부터
		DNODE* node = &m_head;

		// 추가할 알맞는 노드까지 찾는다.
		while (&m_tail != node->next)
		{
			// 데이터 값이 새로운 데이터 값과 같은 경우
			// 혹은 다음 데이터 값이 더 큰 경우
			if (node->data == newNode->data ||
				node->next->data > newNode->data)
			{
				// 중간에 삽입 해준다.
				newNode->next = node->next;
				node->next->prev = newNode;
				node->next = newNode;
				newNode->prev = node;
				return;
			}

			node = node->next;
		}

		// 끝에 도달한 경우
		// 그냥 tail이 끝이니 그것을 이용하여 추가하면 된다.
		newNode->next = &m_tail;
		newNode->prev = m_tail.prev;
		m_tail.prev->next = newNode;
		m_tail.prev = newNode;
	}
}

void DoubleLinkedList::Delete(DATA& data)
{
	// 비어 있는지 검사한다.
	if (true == CheckEmpty())
	{
		cout << "Empty!" << endl;
		return;
	}

	// Head 노드부터
	DNODE* node = &m_head;
	while (&m_tail != node->next)
	{
		node = node->next;

		// 삭제하려는 값이 들어간 노드를 찾은경우
		if (data == node->data)
		{
			// 삭제하기 전 노드와 다음 노드를 서로 이어붙인다.
			node->prev->next = node->next;
			node->next->prev = node->prev;
			// 노드를 삭제한다.
			delete node;
			node = nullptr;
			break;
		}
	}
}

void DoubleLinkedList::Clear()
{
	// Head 노드부터 순회 돌면서 삭제작업을 한다.
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
	// 노드의 데이터를 모두 출력한다.
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
