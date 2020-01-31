#include "pch.h"
#include "UserInterface.h"
#include "SingleLinkedList.h"
#include "DoubleLinkedList.h"

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
	delete m_linkedList;
	m_linkedList = nullptr;
}

void UserInterface::Initialize()
{
#ifdef Single
	m_linkedList = new SingleLinkedList;
#endif
#ifdef Double
	m_linkedList = new DoubleLinkedList;
#endif

	assert(m_linkedList);
}

void UserInterface::Logic()
{
	while (1)
	{
		PrintMenu();
		if (-1 == InputAndRun())
			break;
	}
}

void UserInterface::PrintMenu()
{
	cout << "========================================================" << endl;
	cout << "1. Add  2. Delete  3. Clear  4. Print  5. Exit" << endl;
	cout << "Input? ";
}

int UserInterface::InputAndRun()
{
	int input = 0;
	DATA data;
	cin >> input;
	switch (input)
	{
	case 1: 
		cout << "Input Number to add. Number? ";
		cin >> data.number;
		m_linkedList->Add(data);
		break;
	case 2:
		cout << "Input Number to delete. Number? ";
		cin >> data.number;
		m_linkedList->Delete(data);
		break;
	case 3: m_linkedList->Clear(); break;
	case 4: m_linkedList->Print(); break;
	case 5: return -1;
	default: cout << "Wrong Input! Try Again!" << endl; break;
	}

	return 0;
}
