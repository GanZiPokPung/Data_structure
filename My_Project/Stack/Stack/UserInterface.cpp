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
	// 메뉴를 출력한다.
	cout << "=======================================" << endl;
	cout << "1.Push 2.Pop 3.Clear 4.Exit" << endl;

	// 입력에 맞는 기능을 수행한다.
	int input;
	cin >> input;
	switch (input)
	{
	case 1: Push(); break;
	case 2: Pop(); break;
	case 3: Clear(); break;
	case 4: return -1;
	default:
		cout << "잘못된 입력!" << endl;
		break;
	}

	return 0;
}

void UserInterface::Logic()
{
	// 종료할때까지 반복한다.
	while (true)
	{
		if (-1 == PrintMenu())
			break;
	}
}

void UserInterface::Push()
{
	// 필요한 데이터를 입력받고 Push한다.
	int number, size;
	cout << "식별 숫자를 입력해주세요? "; cin >> number;
	cout << "데이터의 크기를 입력해주세요? ";cin >> size;

	cout << "데이터 내용을 입력해주세요." << endl
		 << "------------------------------------------" << endl;
	
	string tmpData;
	cin >> tmpData;

	Stack_->Push(number, size, tmpData.c_str());

	cout << "------------------------------------------" << endl;
	cout << "추가 완료!" << endl;
}

void UserInterface::Pop()
{
	// 비어 있는지 확인
	if (true == Stack_->IsEmpty())
	{
		cout << "비어 있습니다!" << endl;
		return;
	}

	// 비어 있지 않다면 Pop을 하면서 Pop한 데이터를 가져온다.
	DATA val;
	Stack_->Pop(&val);

	// 데이터의 내용을 출력한다.
	cout << "식별 숫자 : " << val.Number <<
		" 데이터 크기 : " << val.Size << endl;
	printf("데이터 내용\n%s\n", val.Contents);
}

void UserInterface::Clear()
{
	// 모든 데이터를 Clear한다.
	Stack_->Clear();
	cout << "모든 데이터가 삭제되었습니다." << endl;
}
