#include "pch.h"
#include "Stack_Util_Reverse.h"

char* Stack_Util_Reverse::ReverseString(char* source)
{
	char* pReturn = nullptr;

	int size = strlen(source);
	if (0 == size)
		return nullptr;

	pReturn = new char[size + 1];

	NODE inputVal;
	for(int i = 0; i < size; ++i)
	{
		inputVal.Data = source[i];
		m_LLStack.Push(inputVal);
	}
	
	NODE outputVal;
	for (int i = 0; i < size; ++i)
	{
		outputVal = m_LLStack.Pop();
		pReturn[i] = outputVal.Data;
	}
	pReturn[size] = '\0';

	m_LLStack.DeleteAll();
	return pReturn;
}

bool Stack_Util_Reverse::CheckBracketMatching(char* source)
{
	int size = strlen(source);
	if (0 == size)
		return true;

	NODE inputVal;
	NODE outputVal;
	char symbol;
	for (int i = 0; i < size; ++i)
	{
		symbol = source[i];
		switch (symbol)
		{
		case '(':
		case '{':
		case '[':
			inputVal.Data = symbol;
			m_LLStack.Push(inputVal);
			break;
		case ')':
		case '}':
		case ']':
			outputVal = m_LLStack.Pop();
			if (0 == outputVal.Data)
			{
				m_LLStack.DeleteAll();
				return false;
			}
			else
			{
				char check = outputVal.Data;
				if (')' == symbol && '(' == check ||
					'}' == symbol && '{' == check ||
					']' == symbol && '[' == check)
				{
					// Right case
				}
				else
				{
					m_LLStack.DeleteAll();
					return false;
				}
			}
			break;
		}
	}

	if (false == m_LLStack.IsEmpty())
	{
		m_LLStack.DeleteAll();
		return false;
	}

	m_LLStack.DeleteAll();
	return true;
}
