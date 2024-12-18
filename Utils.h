#pragma once

template<typename T = UINT>
inline T readVal(UINT address)
{
	return *(T*)(address);
}

template <typename T = UINT>
inline void writeVal(UINT address, T value)
{
	*(T*)(address) = value;
}