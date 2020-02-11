#pragma once

class DATA
{
public:
	DATA() {}
	DATA(int number, int size, const char* data)
		:Number(number),
		Size(size)
	{
		if (0 < size)
			Contents = new char[size];
		memset(Contents, 0, size);

		memcpy(Contents, data, strlen(data));
	}
	~DATA()
	{
		SAFE_DELETE_ARR<char*>(Contents);
	}

public:
	bool operator == (DATA& other)
	{
		return Number == other.Number;
	}
	void operator =(DATA& other)
	{
		Number = other.Number;
		Size = other.Size;

		SAFE_DELETE_ARR<char*>(Contents);

		Contents = new char[Size];
		memcpy(Contents, other.Contents, Size);
	}

public:
	int Number = 0;
	char* Contents = nullptr;
	int Size = 0;
};