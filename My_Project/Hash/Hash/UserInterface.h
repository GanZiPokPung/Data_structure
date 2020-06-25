#pragma once

class HashTable;
class UserInterface
{
public:
	UserInterface();
	~UserInterface();

public:
	void Logic();

private:
	bool PrintMenu();
	void Add();
	void Delete();
	void Find();
	void Print();

private:
	HashTable* hash = nullptr;
};

