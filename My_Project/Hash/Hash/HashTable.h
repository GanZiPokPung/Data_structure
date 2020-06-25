#pragma once
#include "Includes.h"
class HashTable
{
public:
	HashTable();
	~HashTable();

public:
	bool Add(string key, int age, string number);
	void Delete(string key);
	bool Find(DATA* data, string key);
	void GetObjects(vector<DATA*>& output);

private:
	int HashFunction(string key);

private:
	int maxElementSize = 100;
	vector<list<DATA*>> table;
};

