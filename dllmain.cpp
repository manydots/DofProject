﻿#include "dof.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Gamex::DLL_Main(); // 初始化DllMain

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		//Cleanup(); // 添加后控制台无法输出游戏内部日志
		break;
	}
	return TRUE;
}