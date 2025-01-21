#pragma once
#ifndef _HOTKEY_H_
#define _HOTKEY_H_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <Windows.h>

#define MOD_NONE 0x0000
typedef unsigned int HOTKEY_ID;
typedef DWORD PFUNC;

typedef struct tagHOTKEY_INFO
{
	// 标识
	HOTKEY_ID HotkeyID;
	// 按键组合回调
	PFUNC pfnCallbackFunc;
	// 普通键
	BYTE KeyCode;
	// 功能键
	BYTE FuncKey;
	// 其他键
	BYTE AnotherKeyCode;
	// 键状态
	BYTE byKeyStatus;
	// 状态
	BOOL bStatus;
	// 直接触发
	BOOL bDirectTrigger;
} HOTKEY_INFO, * PHOTKEY_INFO;

void HandleTheEvents();
void SuperDelay(int nElapse, int nUnit = 0);

HOTKEY_ID HotkeyMonitor(PFUNC pfnCallbackFunc, BYTE KeyCode, BYTE FuncKeyStatus = MOD_NONE, BYTE AnotherKeyCode = 0, UINT uElapse = USER_TIMER_MINIMUM, BOOL bDirectTrigger = FALSE);
VOID CALLBACK HotKeyMonThread(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
BOOL HotKeyUnMonitor(HOTKEY_ID HotkeyID = 0);

#endif