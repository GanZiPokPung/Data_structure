#include "pch.h"
#include "UserInterface.h"
#include "ClassStack.h"

UserInterface::UserInterface()
{
	Stack_ = new ClassStack;
}

UserInterface::~UserInterface()
{
	Stack_->Clear();
	SAFE_DELETE<ClassStack*>(Stack_);
}

int UserInterface::PrintMenu()
{
	cout << "=======================================" << endl;
	cout << "1.Push 2.Pop 3.Clear 4.Exit" << endl;

	int input;
	cin >> input;
	switch (input)
	{
	case 1: Push(); break;
	case 2: Pop(); break;
	case 3: Clear(); break;
	case 4: return -1;
	default:
		cout << "�߸��� �Է�!" << endl;
		break;
	}

	return 0;
}

void UserInterface::Logic()
{
	while (true)
	{
		if (-1 == PrintMenu())
			break;
	}
}

void UserInterface::Push()
{
	int number, size;
	cout << "�ĺ� ���ڸ� �Է����ּ���? "; cin >> number;
	cout << "�������� ũ�⸦ �Է����ּ���? ";cin >> size;

	cout << "������ ������ �Է����ּ���." << endl
		 << "------------------------------------------" << endl;
	
	string tmpData;
	cin >> tmpData;
	/*char* tmpData = new char[size];
	memset(tmpData, 0, size);
	fputs(tmpData, stdin);*/

	Stack_->Push(number, size, tmpData.c_str());

	cout << "------------------------------------------" << endl;
	cout << "�߰� �Ϸ�!" << endl;
}

void UserInterface::Pop()
{
	if (true == Stack_->IsEmpty())
	{
		cout << "��� �ֽ��ϴ�!" << endl;
		return;
	}

	DATA val;
	Stack_->Pop(&val);

	cout << "�ĺ� ���� : " << val.Number <<
		" ������ ũ�� : " << val.Size << endl;
	printf("������ ����\n%s\n", val.Contents);
}

void UserInterface::Clear()
{
	Stack_->Clear();
	cout << "��� �����Ͱ� �����Ǿ����ϴ�." << endl;
}
