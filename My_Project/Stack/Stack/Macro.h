#pragma once

template <typename T>
inline void SAFE_DELETE(T& val)
{
	if (nullptr != val)
	{
		delete val;
		val = nullptr;
	}
}

template <typename T>
inline void SAFE_DELETE_ARR(T& val)
{
	if (nullptr != val)
	{
		delete[] val;
		val = nullptr;
	}
}