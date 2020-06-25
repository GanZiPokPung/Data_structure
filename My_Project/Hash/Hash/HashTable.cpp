#include "HashTable.h"

HashTable::HashTable()
{
	table.assign(maxElementSize, list<DATA*>());
}

HashTable::~HashTable()
{
	for (int i = 0; i < table.size(); ++i)
	{
		for (auto iter = table[i].begin(); iter != table[i].end(); ++iter)
		{
			delete(*iter);
			(*iter) = nullptr;
		}
		table[i].clear();
	}
	table.clear();
}

bool HashTable::Add(string key, int age, string number)
{
	if (Find(nullptr, key))
		return false;

	int idx = HashFunction(key);
	DATA* newData = new DATA{ key, age, number };
	table[idx].push_back(newData);

	return true;
}

void HashTable::Delete(string key)
{
	int idx = HashFunction(key);
	for (auto iter = table[idx].begin(); iter != table[idx].end(); ++iter)
	{
		if ((*iter)->name == key)
		{
			iter = table[idx].erase(iter);
			return;
		}
	}
}

bool HashTable::Find(DATA * data, string key)
{
	int idx = HashFunction(key);
	for (auto iter = table[idx].begin(); iter != table[idx].end(); ++iter)
	{
		if ((*iter)->name == key)
		{
			if (data != nullptr)
				*data = *(*iter);
			return true;
		}
	}
	return false;
}

void HashTable::GetObjects(vector<DATA*>& output)
{
	for (int i = 0; i < table.size(); ++i)
	{
		if (table[i].empty()) continue;
		for (auto iter = table[i].begin(); iter != table[i].end(); ++iter)
		{
			output.push_back((*iter));
		}
	}
}

int HashTable::HashFunction(string key)
{
	int result = 0;
	for (int i = 0; i < key.size(); ++i)
	{
		result += 37 * result * int(key[i]);
	}
	return result % maxElementSize;
}
