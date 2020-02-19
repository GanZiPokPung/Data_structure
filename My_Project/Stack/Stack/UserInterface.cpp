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
	// �޴��� ����Ѵ�.
	cout << "=======================================" << endl;
	cout << "1.Push 2.Pop 3.Clear 4.Exit" << endl;

	// �Է¿� �´� ����� �����Ѵ�.
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
	// �����Ҷ����� �ݺ��Ѵ�.
	while (true)
	{
		if (-1 == PrintMenu())
			break;
	}
}

void UserInterface::Push()
{
	// �ʿ��� �����͸� �Է¹ް� Push�Ѵ�.
	int number, size;
	cout << "�ĺ� ���ڸ� �Է����ּ���? "; cin >> number;
	cout << "�������� ũ�⸦ �Է����ּ���? ";cin >> size;

	cout << "������ ������ �Է����ּ���." << endl
		 << "------------------------------------------" << endl;
	
	string tmpData;
	cin >> tmpData;

	Stack_->Push(number, size, tmpData.c_str());

	cout << "------------------------------------------" << endl;
	cout << "�߰� �Ϸ�!" << endl;
}

void UserInterface::Pop()
{
	// ��� �ִ��� Ȯ��
	if (true == Stack_->IsEmpty())
	{
		cout << "��� �ֽ��ϴ�!" << endl;
		return;
	}

	// ��� ���� �ʴٸ� Pop�� �ϸ鼭 Pop�� �����͸� �����´�.
	DATA val;
	Stack_->Pop(&val);

	// �������� ������ ����Ѵ�.
	cout << "�ĺ� ���� : " << val.Number <<
		" ������ ũ�� : " << val.Size << endl;
	printf("������ ����\n%s\n", val.Contents);
}

void UserInterface::Clear()
{
	// ��� �����͸� Clear�Ѵ�.
	Stack_->Clear();
	cout << "��� �����Ͱ� �����Ǿ����ϴ�." << endl;
}
