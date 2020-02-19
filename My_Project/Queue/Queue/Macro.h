#pragma once

template<typename T>
void SAFE_DELETE(T*& value)
{
	if (nullptr != value)
	{
		delete value;
		value = nullptr;
	}
}

template<typename T>
void SAFE_DELETE_ARRAY(T*& value)
{
	if (nullptr != value)
	{
		delete[] value;
		value = nullptr;
	}
}