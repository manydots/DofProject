#include "Hook.h"
#include <windows.h>
void writeJmp(void* pfn, void* pCallback) {
	DWORD pTmp = NULL;
	VirtualProtect(pfn, 5, PAGE_EXECUTE_READWRITE, &pTmp);
	*(UCHAR*)((char*)pfn + 0) = 0xE9;
	*(UCHAR*)((char*)pfn + 1) = (ULONG)pCallback - (ULONG)pfn - 5;
	FlushInstructionCache(GetCurrentProcess(), pfn, 5);
	VirtualProtect(pfn, 5, pTmp, &pTmp);
}

void writeCall(void* pfn, void* pCallback) {
	DWORD pTmp = NULL;
	VirtualProtect(pfn, 5, PAGE_EXECUTE_READWRITE, &pTmp);
	*(UCHAR*)((char*)pfn + 0) = 0xE8;
	*(UCHAR*)((char*)pfn + 1) = (ULONG)pCallback - (ULONG)pfn - 5;
	FlushInstructionCache(GetCurrentProcess(), pfn, 5);
	VirtualProtect(pfn, 5, pTmp, &pTmp);
}