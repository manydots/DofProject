#include "CLVEH.h"
#include <string>

#pragma warning(disable:4996)

void VehWriteMemCode(DWORD Adress, BYTE ArgByte)
{
	DWORD OldPro;
	VirtualProtect((LPVOID)Adress, 1, PAGE_EXECUTE_READWRITE, &OldPro);
	*(BYTE*)Adress = ArgByte;
	VirtualProtect((LPVOID)Adress, 1, OldPro, NULL);
	FlushInstructionCache(GetCurrentProcess(), (LPCVOID)Adress, 1); // ȷ�����ı�Ӧ��
}

LONG NTAPI veh_optimization(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	DWORD Addr = (DWORD)ExceptionInfo->ExceptionRecord->ExceptionAddress;
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT)
	{
		CCLVEH::Instance()->BreakRun(Addr, ExceptionInfo);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP)
	{
		CCLVEH::Instance()->BreakOne(Addr);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_EXECUTE_HANDLER;
}

CCLVEH* CCLVEH::Instance()
{
	static CCLVEH instance;
	return &instance;
}

CCLVEH::~CCLVEH()
{
	ExitVeh();
}

void CCLVEH::AddVeh(char* VehName, char* MoudleName, DWORD MoudleOffset, DWORD VehHookAdress, DWORD HookCodeLen_, int IsOnce, void(*Fun)(struct _EXCEPTION_POINTERS* ExceptionInfo))
{
	_VehData Data;

	strcpy_s(Data.VehName_, VehName);

	if (MoudleName != NULL)
		strcpy_s(Data.MoudleName_, MoudleName);
	else
		memset(Data.MoudleName_, 0, 512);

	Data.MoudleOffset_ = MoudleOffset;
	Data.VehHookAdress_ = VehHookAdress;
	Data.HookCodeLen_ = HookCodeLen_;
	Data.IsOnce_ = IsOnce;
	Data.Fun_ = Fun;

	WaitForSingleObject(hMutex, INFINITE); // �ȴ������ٽ���
	VehList.push_back(Data);
	ReleaseMutex(hMutex); // �뿪�ٽ���
}

void CCLVEH::BreakAll()
{
	WaitForSingleObject(hMutex, INFINITE); // �ȴ������ٽ���

	for (auto& Data : VehList)
	{
		if (Data.MoudleName_[0] != 0)
		{
			Data.VehHookAdress_ = (DWORD)GetModuleHandleA(Data.MoudleName_) + Data.MoudleOffset_;
		}

		Data.OldCode_ = *(BYTE*)Data.VehHookAdress_;
		VehWriteMemCode(Data.VehHookAdress_, 0xcc); // INT 3 ָ��
	}

	ReleaseMutex(hMutex); // �뿪�ٽ���
}

void CCLVEH::BreakOne(DWORD CodeAdress)
{
	WaitForSingleObject(hMutex, INFINITE); // �ȴ������ٽ���

	for (auto& Data : VehList)
	{
		if (Data.MoudleName_[0] != 0)
		{
			Data.VehHookAdress_ = (DWORD)GetModuleHandleA(Data.MoudleName_) + Data.MoudleOffset_;
		}
		if (CodeAdress == Data.VehHookAdress_ + Data.HookCodeLen_)
		{
			VehWriteMemCode(Data.VehHookAdress_, 0xcc); // INT 3 ָ��
			break;
		}
	}

	ReleaseMutex(hMutex); // �뿪�ٽ���
}

void CCLVEH::BreakRun(DWORD CodeAdress, _EXCEPTION_POINTERS* ExceptionInfo)
{
	WaitForSingleObject(hMutex, INFINITE); // �ȴ������ٽ���

	for (auto& Data : VehList)
	{
		if (Data.MoudleName_[0] != 0)
		{
			Data.VehHookAdress_ = (DWORD)GetModuleHandleA(Data.MoudleName_) + Data.MoudleOffset_;
		}
		if (CodeAdress == Data.VehHookAdress_)
		{
			VehWriteMemCode(Data.VehHookAdress_, Data.OldCode_);
			if (Data.IsOnce_ == 0)
			{
				ExceptionInfo->ContextRecord->EFlags |= 0x100; // �ָ�������־
			}

			if (Data.Fun_ != NULL)
			{
				Data.Fun_(ExceptionInfo);
			}

			break;
		}
	}

	ReleaseMutex(hMutex); // �뿪�ٽ���
}

void CCLVEH::InitVeh()
{
	hMutex = CreateMutex(NULL, FALSE, NULL); // ����������
	m_Handle = AddVectoredExceptionHandler(0, (PVECTORED_EXCEPTION_HANDLER)veh_optimization);
	BreakAll();
}

void CCLVEH::ExitVeh()
{
	WaitForSingleObject(hMutex, INFINITE); // �ȴ������ٽ���

	RemoveVectoredExceptionHandler(m_Handle);

	for (auto& Data : VehList)
	{
		if (Data.MoudleName_[0] != 0)
		{
			Data.VehHookAdress_ = (DWORD)GetModuleHandleA(Data.MoudleName_) + Data.MoudleOffset_;
		}

		VehWriteMemCode(Data.VehHookAdress_, Data.OldCode_);
	}

	ReleaseMutex(hMutex); // �뿪�ٽ���
	CloseHandle(hMutex); // �رջ��������
}