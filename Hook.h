#pragma once
#include <windows.h>
#define Naked __declspec(naked)
#define _v(v1,v2) ((v1|v2)<<8)
#define rgb(r,g,b) ((BYTE)r|_v((BYTE)g,_v((BYTE)b,0xFFFFFF00)))
#define rgba(r,g,b,a) ((BYTE)r|_v((BYTE)g,_v((BYTE)b,(BYTE)a<<8)))

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

void WriteJmp(void* pfn, void* pCallback);
void WriteCall(void* pfn, void* pCallback);