#pragma once
#include <windows.h>
#include <vector>
using namespace std;

#define VEHADMIN CCLVEH::Instance()

struct _VehData
{
	char VehName_[512];
	char MoudleName_[512];
	int   MoudleOffset_;
	DWORD VehHookAdress_;
	DWORD HookCodeLen_;
	BOOL  IsOnce_;
	BYTE OldCode_; // �޸�Ϊ BYTE����Ϊͨ������ֻ�޸�һ���ֽڵ�ָ��
	void(*Fun_)(struct _EXCEPTION_POINTERS* ExceptionInfo);
};

LONG NTAPI veh_optimization(struct _EXCEPTION_POINTERS* ExceptionInfo);

class CCLVEH
{
public:
	static CCLVEH* Instance();
	~CCLVEH();

	vector<_VehData> VehList;
	HANDLE hMutex; // ʹ�û�������� CCriticalSection
	LPVOID m_Handle = 0;

	void AddVeh(char* VehName, char* MoudleName, DWORD MoudleOffset, DWORD VehHookAdress, DWORD HookCodeLen_, int IsOnce, void(*Fun)(struct _EXCEPTION_POINTERS* ExceptionInfo));

	void BreakAll();
	void BreakOne(DWORD CodeAdress);
	void InitVeh();
	void BreakRun(DWORD CodeAdress, _EXCEPTION_POINTERS* ExceptionInfo);
	void ExitVeh();
};