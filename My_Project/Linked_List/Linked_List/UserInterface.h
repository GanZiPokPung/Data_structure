#pragma once
#include "LinkedList.h"

class UserInterface
{
public:
	UserInterface();
	~UserInterface();
public:
	void Initialize();
	void Logic();
	void PrintMenu();
	int InputAndRun();
private:
	LinkedList* m_linkedList = nullptr;
};

