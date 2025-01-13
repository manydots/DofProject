#pragma once
#include "dof.h"
#include "Hook.h"

// ����ڴ��Ƿ�����ҿɶ�
BOOL IsMemoryReadable(void* address, size_t length);

// ���ֽڼ� TCHAR�ַ���(ANSI/Unicode)  BYTE *buffer
BOOL ReadMemoryBytes(TCHAR* buffer, DWORD address, size_t length);

// ��ȡDWORD����
DWORD ReadDWORD(DWORD address);

// �����ֽ�wchar_t*ת��Ϊ���ֽ�char*    
char* UnicodeToAnsi(const wchar_t* szStr);
// �����ֽ�char*ת��Ϊ���ֽ�wchar_t*    
wchar_t* AnsiToUnicode(const char* szStr);

// дָ���ֽڼ����ڴ� addressĿ�� ptr���� length����
void WriteBytes(void* address, void* ptr, size_t length);

// дVector�ֽڼ����ڴ� addressĿ���ڴ��ַ  Vector�ֽڼ�����
void WriteVectorBytes(void* address, std::vector<BYTE> Vector_BYTE);

// �ַ���ת�ֽڼ�
std::vector<BYTE> stringToBytes(const std::string& str);

// ת����ɫ
std::vector<uint8_t> hexStringToByteArray(const std::string& hex);
// vector��ɫתbyte
std::vector<BYTE> VectorToBytes(const std::string& hex);

// ����Call(���Ȼ�ַ)
using _game_notice = void(__fastcall*)(UINT ecx, UINT edx, PCWCHAR str, INT rgb, INT type, INT n1, INT n2, INT n3);
const _game_notice game_notice = (_game_notice)NOTICE_CALL;

// ����Call
using _game_shout = void(__fastcall*)(UINT ecx, UINT edx, PCWCHAR str, INT type, INT n2, INT n3);
const _game_shout game_shout = (_game_shout)SHOUT_CALL;

namespace GameCall {
	// �����ı�call   type 14���ȹ���  17ϵͳ���� 37���˹���
	void SendText(PCWCHAR str, INT rgb, INT type);
	// ����  type 3������ 1���Ļ������׶Ի��� ����11 ʦͽ8  ����6
	void Shout(PCWCHAR str, INT type = 3);
}