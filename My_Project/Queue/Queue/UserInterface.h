#pragma once
#include "Queue_Abstract.h"
class UserInterface
{
public:
	UserInterface();
	~UserInterface();
public:
	void Logic();
private:
	void PrintMenu();
	int  InputProcess();
private:
	Queue_Abstract* m_Queue = nullptr;
};

