#pragma once
#include "DataTypes.h"

class ClassStack
{
public:
	ClassStack() {}
	~ClassStack();

public:
	bool IsEmpty() { return (-1 == Top); }

public:
	void Push(int number, int size, const char* data);
	void Pop(DATA* OutData);
	void Clear();

private:
	void Swap(int ChangeSize);

private:
	int Top = -1;
	int Size = 0;
	DATA** Container = nullptr;
	DATA** ForSwap = nullptr;
};

