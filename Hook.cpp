#pragma once
#include "Hook.h"

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


BOOL SimpleHook::HookByAddress(DWORD hookedFunc, DWORD myHookFunc)
{
	hookedAddr = hookedFunc;
	ReadProcessMemory(INVALID_HANDLE_VALUE, (LPCVOID)hookedAddr, hookedBytes, 5, NULL);

	*(DWORD*)(hookBytes + 1) = (DWORD)myHookFunc - (DWORD)hookedAddr - 5;
	return WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)hookedAddr, hookBytes, 5, NULL);
}

BOOL SimpleHook::HookByModule(LPCSTR lpModuleName, LPCSTR lpProcName, DWORD myHookFunc)
{
	HMODULE hmodule = GetModuleHandleA(lpModuleName);
	if (!hmodule)
		return FALSE;

	DWORD procAddress = (DWORD)GetProcAddress(hmodule, lpProcName);
	if (!procAddress)
		return FALSE;

	return HookByAddress(procAddress, myHookFunc);
}

BOOL SimpleHook::UnHook()
{
	if (!hookedAddr)
		return FALSE;

	return WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)hookedAddr, hookedBytes, 5, NULL);
}

BOOL SimpleHook::ReHook()
{
	if (!hookedAddr)
		return FALSE;

	return WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)hookedAddr, hookBytes, 5, NULL);
}