#pragma once

typedef struct _data
{
	int number;

public:
	void operator=(const _data& other)
	{
		number = other.number;
	}
	bool operator==(const _data& other)
	{
		return number == other.number;
	}
}DATA;

typedef struct _singleNode
{
	DATA data;
	_singleNode* next;
}SNODE;

typedef struct _doubleNode
{
	DATA data;
	_doubleNode* next;
	_doubleNode* prev;
}DNODE;