#pragma once
#include "LinkedListStack.h"

// ������ �̿��Ͽ� ���ڿ� ����ȯ�� ��ȣ�˻� ����� ����

class Stack_Util_Reverse
{
public:
	char* ReverseString(char* source);
	bool CheckBracketMatching(char* source);
private:
	LinkedListStack m_LLStack;
};

