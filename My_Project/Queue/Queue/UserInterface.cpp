#include "pch.h"
#include "UserInterface.h"
#include "Queue_Array.h"
#include "Queue_LInkedList.h"

UserInterface::UserInterface()
{
	m_Queue = new Queue_LInkedList;
}

UserInterface::~UserInterface()
{
	SAFE_DELETE<Queue_Abstract>(m_Queue);
}

void UserInterface::Logic()
{
	while (true)
	{
		PrintMenu();
		if (-1 == InputProcess())
			return;
	}
}

void UserInterface::PrintMenu()
{
	cout << "=====================================================================" << endl;
	cout << "1.Enqueue  2.Dequeue  3.PeekFront  4.PeekRear  5.PrintAll  6.Exit" << endl;
	cout << "Select Number? ";
}

int UserInterface::InputProcess()
{
	int input = 0;
	cin >> input;

	DATA data;
	switch (input)
	{
	case 1:
	{
		cout << "�����͸� �Է��ϼ���? ";
		cin >> data.number;
		m_Queue->Enqueue(data);
		cout << "Enqueue �Ϸ�!" << endl;
		break;
	}
	case 2:
	{
		cout << "���� ������" << endl;
		if (true == m_Queue->Dequeue(&data))
			cout << "Number : " << data.number << endl;
		else
			cout << "Empty!" << endl;
		break;
	}
	case 3:
	{
		cout << "Front ������" << endl;
		if (true == m_Queue->PeekFront(&data))
			cout << "Number : " << data.number << endl;
		else
			cout << "Empty!" << endl;
		break;
	}
	case 4:
	{
		cout << "Rear ������" << endl;
		if (true == m_Queue->PeekRear(&data))
			cout << "Number : " << data.number << endl;
		else
			cout << "Empty!" << endl;
		break;
	}
	case 5:
	{
		m_Queue->PrintAll();
		break;
	}
	case 6:
		return -1;
	}

	return 0;
}
