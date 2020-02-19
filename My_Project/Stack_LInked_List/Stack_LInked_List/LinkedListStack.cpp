#include "pch.h"
#include "LinkedListStack.h"

LinkedListStack::LinkedListStack()
{
	CreateLinkedStack();
}

LinkedListStack::~LinkedListStack()
{
	DeleteLinkedStack();
}

void LinkedListStack::CreateLinkedStack()
{
	m_stack = new LLSTACK;
	memset(m_stack, 0, sizeof(LLSTACK));
}

void LinkedListStack::DeleteLinkedStack()
{
	// 전체 삭제
	DeleteAll();
	// 할당 해제
	SAFE_DELETE<LLSTACK>(m_stack);
}

bool LinkedListStack::Push(NODE element)
{
	NODE* newNode = new NODE;
	newNode->Data = element.Data;
	newNode->Link = nullptr;

	if (nullptr != m_stack)
	{
		if (nullptr == m_stack->Top)
		{
			m_stack->Top = newNode;
		}
		else
		{
			newNode->Link = m_stack->Top;
			m_stack->Top = newNode;
		}

		m_stack->ElementCount++;
	}
	else
	{
		return false;
	}

	return true;
}

NODE LinkedListStack::Pop()
{
	NODE* pReturnVal = nullptr;
	NODE ReturnVal;
	memset(&ReturnVal, 0, sizeof(NODE));

	if (nullptr != m_stack)
	{
		if (false == IsEmpty())
		{
			pReturnVal = m_stack->Top;
			m_stack->Top = pReturnVal->Link;
			pReturnVal->Link = nullptr;

			ReturnVal.Data = pReturnVal->Data;

			SAFE_DELETE<NODE>(pReturnVal);
			m_stack->ElementCount--;
		}
	}

	return ReturnVal;
}

NODE LinkedListStack::Peek()
{
	NODE ReturnVal;
	memset(&ReturnVal, 0, sizeof(NODE));

	if (nullptr != m_stack)
	{
		if(false == IsEmpty())
			ReturnVal = *m_stack->Top;
	}

	return ReturnVal;
}

bool LinkedListStack::IsEmpty()
{
	return (0 == m_stack->ElementCount || nullptr == m_stack->Top);
}

void LinkedListStack::DeleteAll()
{
	if (nullptr != m_stack)
	{
		NODE* delNode = nullptr;
		NODE* node = m_stack->Top;

		while (nullptr != node)
		{
			delNode = node;
			node = node->Link;
			SAFE_DELETE<NODE>(delNode);
		}
	}
}

void LinkedListStack::PrintStack()
{
	if (nullptr != m_stack)
	{
		NODE* node = m_stack->Top;
		int i = 1;
		while (nullptr != node)
		{
			printf("[%d] - %d\n", m_stack->ElementCount - i, node->Data);
			node = node->Link;
			++i;
		}
	}
}
