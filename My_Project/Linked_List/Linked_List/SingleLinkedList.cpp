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
	// 추가할 데이터를 가진 새로운 노드를 만든다.
	SNODE* newNode = new SNODE;
	memset(&newNode->data, 0, sizeof(DATA));
	newNode->data = data;
	newNode->next = nullptr;

	// head의 next가 비어있는 경우 (empty인 경우)
	if (nullptr == m_head.next)
	{
		// head의 next에 새로 만든 노드의 주소를 넣는다.
		m_head.next = newNode;
	}
	else
	{
		// head 노드에서 부터
		SNODE* node = &m_head;

		// 추가할 알맞는 노드까지 찾는다.
		while (nullptr != node->next)
		{
			// 데이터 값이 새로운 데이터 값과 같은 경우
			// 혹은 다음 데이터 값이 더 큰 경우
			if (node->data == newNode->data ||
				node->next->data > newNode->data)
			{
				// 중간에 삽입 해준다.
				newNode->next = node->next;
				node->next = newNode;
				return;
			}
		
			node = node->next;
		}
		// 끝에 도달한 경우
		node->next = newNode;
	}
}

void SingleLinkedList::Delete(DATA& data)
{
	// 비어 있는지 검사한다.
	if (true == CheckEmpty())
	{
		cout << "Empty!" << endl;
		return;
	}

	// Head 노드부터
	SNODE* node = &m_head;
	// 중간 삭제시 노드를 이어 붙이기 위해 전 노드 주소가 필요하다.
	SNODE* preNode = nullptr;
	while (nullptr != node->next)
	{
		preNode = node;
		node = node->next;

		// 삭제하려는 값이 들어간 노드를 찾은경우
		if (data == node->data)
		{
			// 삭제하려는 노드간 연결을 끊고
			// 삭제하기 전 노드와 다음 노드를 이어붙인다.
			preNode->next = node->next;
			node->next = nullptr;
			// 노드를 삭제한다.
			delete node;
			node = nullptr;
			return;
		}	
	}
}

void SingleLinkedList::Clear()
{
	// Head 노드부터 순회 돌면서 삭제작업을 한다.
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
	// 노드의 데이터를 모두 출력한다.
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
