#pragma once

template<typename T>
inline void SAFE_DELETE(T& value)
{
	if (nullptr != value)
	{
		delete value;
		value = nullptr;
	}
}