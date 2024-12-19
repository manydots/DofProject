#include "Hook.h"
#include <windows.h>
void WriteJmp(void* pfn, void* pCallback) {
	DWORD pTmp = NULL;
	VirtualProtect(pfn, 5, PAGE_EXECUTE_READWRITE, &pTmp);
	*(UCHAR*)((char*)pfn + 0) = 0xE9;
	*(ULONG*)((char*)pfn + 1) = (ULONG)pCallback - (ULONG)pfn - 5;
	FlushInstructionCache(GetCurrentProcess(), pfn, 5);
	VirtualProtect(pfn, 5, pTmp, &pTmp);
}

void WriteCall(void* pfn, void* pCallback) {
	DWORD pTmp = NULL;
	VirtualProtect(pfn, 5, PAGE_EXECUTE_READWRITE, &pTmp);
	*(UCHAR*)((char*)pfn + 0) = 0xE8;
	*(DWORD*)((char*)pfn + 1) = (DWORD)pCallback - (DWORD)pfn - 5;
	FlushInstructionCache(GetCurrentProcess(), pfn, 5);
	VirtualProtect(pfn, 5, pTmp, &pTmp);
}