#pragma once

typedef struct _tagData
{
	int number;
public:
	_tagData() {}
	_tagData(int num)
	{
		number = num;
	}
}DATA;

typedef struct _tagNode
{
	DATA	   data;
	_tagNode*  link;
}NODE;