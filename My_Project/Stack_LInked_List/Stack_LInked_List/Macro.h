#pragma once

template<typename T>
inline void SAFE_DELETE(T*& val)
{
	if (nullptr != val)
	{
		delete val;
		val = nullptr;
	}
}