#pragma once
#include "ClassStack.h"

class UserInterface
{
public:
	UserInterface();
	~UserInterface();

public:
	int  PrintMenu();
	void Logic();

public:
	void Push();
	void Pop();
	void Clear();

private:
	ClassStack* Stack_ = nullptr;
};

