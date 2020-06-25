#include "UserInterface.h"
#include "HashTable.h"


UserInterface::UserInterface()
{
	hash = new HashTable;
}


UserInterface::~UserInterface()
{
	delete hash;
	hash = nullptr;
}

void UserInterface::Logic()
{
	bool check = true;
	while (check)
	{
		check = PrintMenu();
	}
}

bool UserInterface::PrintMenu()
{
	cout << "--------------------MENU--------------------" << endl;
	cout << "1. Add  2. Delete  3. Find  4.Print  5.Exit" << endl;
	int input;
	cin >> input;
	switch (input)
	{
	case 1: Add(); break;
	case 2: Delete(); break;
	case 3: Find(); break;
	case 4: Print(); break;
	case 5:
	default:
		return false;
		break;
	}

	return true;
}

void UserInterface::Add()
{
	int age;
	string key, number;
	cout << "Add -> Name : ";
	cin >> key;
	cout << "Add -> Age : ";
	cin >> age;
	cout << "Add -> Number : ";
	cin >> number;
	bool check = hash->Add(key, age, number);
	if(!check) cout << "이미 정보가 존재합니다!" << endl;
}

void UserInterface::Delete()
{
	string key;
	cout << "Delete -> Name : ";
	cin >> key;
	hash->Delete(key);
}

void UserInterface::Find()
{
	string key;
	cout << "Find -> Name : ";
	cin >> key;
	DATA data;
	bool check = hash->Find(&data, key);
	if (check)
	{
		cout << "찾기 성공!" << endl;
		cout << "나이 : "; cout << data.age << endl;
		cout << "전화번호 : "; cout << data.number << endl;
	}
	else
	{
		cout << "찾기 실패!" << endl;
	}
}

void UserInterface::Print()
{
	vector<DATA*> infos;
	hash->GetObjects(infos);

	for (int i = 0; i < infos.size(); ++i)
	{
		cout << "이름 : "; cout << infos[i]->name << endl;
		cout << "나이 : "; cout << infos[i]->age << endl;
		cout << "전화번호 : "; cout << infos[i]->number << endl << endl;
	}
}
