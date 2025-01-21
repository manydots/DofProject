#include "HotKey.h"

std::vector<HOTKEY_INFO> HotKeyList;

void HandleTheEvents()
{
	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, 1))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
}

void SuperDelay(int nElapse, int nUnit)
{
	LARGE_INTEGER int64;
	HANDLE hTimer;

	if (1 == nUnit)
	{
		int64.QuadPart = -10 * nElapse;
		hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
		SetWaitableTimer(hTimer, &int64, 0, NULL, NULL, FALSE);
		while (WAIT_OBJECT_0 != MsgWaitForMultipleObjects(1, &hTimer, FALSE, INFINITE, QS_ALLINPUT))
		{
			HandleTheEvents();
		}
		CloseHandle(hTimer);
		return;
	}
	switch (nUnit)
	{
	case 0:
		nUnit = 1;
		break;
	case 2:
		nUnit = 1000;
		break;
	case 3:
		nUnit = 1000 * 60;
		break;
	case 4:
		nUnit = 1000 * 60 * 60;
		break;
	case 5:
		nUnit = 1000 * 60 * 60 * 24;
		break;
	default:
		break;
	}

	for (int i = 0; i < nUnit; i++)
	{
		int64.QuadPart = -10 * nElapse * 1000;
		hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
		SetWaitableTimer(hTimer, &int64, 0, NULL, NULL, FALSE);
		while (WAIT_OBJECT_0 != MsgWaitForMultipleObjects(1, &hTimer, FALSE, INFINITE, QS_ALLINPUT))
		{
			HandleTheEvents();
		}
		CloseHandle(hTimer);
		return;
	}
}

/*

.Function Name: HotkeyMonitor,监视一个热键, 当热键被触发时激活响应事件.(成功返回热键标识, 失败返回0).注:必须真实的按键才会触发热键
.Parameter pfnCallbackFunc, 子程序指针, , 响应事件(热键标识, 其它...), 事件参数数目不限!如果再次监视热键将响应事件!
.Parameter KeyCode, 字节型, , 触发事件的基本键
.Parameter FuncKeyStatus, 字节型, 可空, 1 Alt  2 Ctrl  4 Shift  8 Win 若要两个或以上的状态键, 则把它们的值相加，可以使用相应的宏MOD_ALT,MOD_CONTROL,MOD_SHIFT,MOD_WIN来位或运算
.Parameter AnotherKeyCode, 字节型, 可空, 如果你需要注册由两个普通键组合的热键, 可设置一个其它键代码.
.Parameter uElapse, 无符号整数型, 可空, 默认为10, 监视热键的周期时间(建议5 - 200之间)
.Parameter bDirectTrigger, 逻辑型, 可空, 默认为假:创建新的线程事件 真 : 直接调用事件等待返回

*/
HOTKEY_ID HotkeyMonitor(PFUNC pfnCallbackFunc, BYTE KeyCode, BYTE FuncKeyStatus, BYTE AnotherKeyCode, UINT uElapse, BOOL bDirectTrigger)
{
	HOTKEY_INFO TempHotkeyInfo;

	if (KeyCode <= 0)
		return 0;

	for (std::vector<HOTKEY_INFO>::iterator it = HotKeyList.begin(); it != HotKeyList.end(); it++)
	{
		if (it->KeyCode == KeyCode && it->FuncKey == FuncKeyStatus && it->AnotherKeyCode == AnotherKeyCode)
		{
			it->pfnCallbackFunc = pfnCallbackFunc;
			it->bDirectTrigger = bDirectTrigger;
			if (it->HotkeyID)
				return it->HotkeyID;
			it->HotkeyID = 1000001 + (it - HotKeyList.begin());
			return it->HotkeyID;
		}
	}

	TempHotkeyInfo.pfnCallbackFunc = pfnCallbackFunc;
	TempHotkeyInfo.KeyCode = KeyCode;
	TempHotkeyInfo.FuncKey = FuncKeyStatus;
	TempHotkeyInfo.AnotherKeyCode = AnotherKeyCode;
	TempHotkeyInfo.bDirectTrigger = bDirectTrigger;
	TempHotkeyInfo.HotkeyID = 1000001 + HotKeyList.size();

	HotKeyList.push_back(TempHotkeyInfo);

	if (1000001 == TempHotkeyInfo.HotkeyID)
		SetTimer(NULL, 666, uElapse, (TIMERPROC)&HotKeyMonThread);

	return TempHotkeyInfo.HotkeyID;
}

// 监视热键线程
VOID CALLBACK HotKeyMonThread(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	PFUNC pfnTempEvent;
	UINT uTempID;
	SHORT KeyStatusCache[256];
	INT byTemp = 0;

	for (int i = 1; i <= 255; i++)
	{
		KeyStatusCache[i] = 251;
		KeyStatusCache[i] = GetAsyncKeyState(i);
	}
	for (std::vector<HOTKEY_INFO>::iterator it = HotKeyList.begin(); it != HotKeyList.end(); it++)
	{
		if (it->HotkeyID)
		{
			byTemp = (BYTE)(it->KeyCode);
			byTemp = KeyStatusCache[byTemp];

			if (0 == byTemp || 1 == byTemp)
			{
				if (1 == it->byKeyStatus)
					it->byKeyStatus = 2;
				else
				{
					it->byKeyStatus = 0;
					continue;
				}
			}
			else if (byTemp < 0)
			{
				if (0 == it->byKeyStatus)
					it->byKeyStatus = 1;
				else if (it->byKeyStatus < 0)
					continue;
			}

			if (it->byKeyStatus > 0 && it->byKeyStatus != 88)
			{
				it->byKeyStatus = 88;
				if (it->FuncKey == ((KeyStatusCache[18] < 0 ? MOD_ALT : 0) | (KeyStatusCache[17] < 0 ? MOD_CONTROL : 0) | (KeyStatusCache[16] < 0 ? MOD_SHIFT : 0) | (KeyStatusCache[91] < 0 ? MOD_WIN : 0)))
				{
					if (it->AnotherKeyCode)
					{
						byTemp = it->AnotherKeyCode;
						if (KeyStatusCache[byTemp] >= 0)
							continue;
					}
					pfnTempEvent = it->pfnCallbackFunc;
					uTempID = it->HotkeyID;
					if (it->bDirectTrigger)
						CallWindowProcA((WNDPROC)pfnTempEvent, (HWND)uTempID, 0, 0, 0);
					else
						CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pfnTempEvent, (LPVOID)uTempID, 0, NULL));
				}
			}
		}
	}
}

/*

.Function Name: HotKeyUnMonitor, 逻辑型  撤消由监视热键注册的一个或全部热键(成功返回真,失败返回假)
.Parameter HotkeyID, HOTKEY_ID型, 可空, 欲撤消的热键标识,如果留空则撤消全部热键

*/

BOOL HotKeyUnMonitor(HOTKEY_ID HotkeyID)
{
	for (std::vector<HOTKEY_INFO>::iterator it = HotKeyList.begin(); it != HotKeyList.end(); it++)
	{
		if (0 == HotkeyID)
			it->HotkeyID = 0;
		else if (HotkeyID == it->HotkeyID)
		{
			it->HotkeyID = 0;
			return TRUE;
		}
	}
	return (0 == HotkeyID);
}