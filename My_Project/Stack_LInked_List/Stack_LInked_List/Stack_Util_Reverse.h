#pragma once
#include "LinkedListStack.h"

// 스택을 이용하여 문자열 역변환과 괄호검사 기능을 구현

class Stack_Util_Reverse
{
public:
	char* ReverseString(char* source);
	bool CheckBracketMatching(char* source);
private:
	LinkedListStack m_LLStack;
};

