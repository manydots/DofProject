#pragma once
#include "dof.h"
#include "Hook.h"

// 检查内存是否存在且可读
BOOL IsMemoryReadable(void* address, size_t length);

// 读字节集 TCHAR字符集(ANSI/Unicode)  BYTE *buffer
BOOL ReadMemoryBytes(TCHAR* buffer, DWORD address, size_t length);

// 读取DWORD整数
DWORD ReadDword(DWORD address);
FLOAT ReadFloat(DWORD Adress);


// 将宽字节wchar_t*转化为单字节char*    
char* UnicodeToAnsi(const wchar_t* szStr);
// 将单字节char*转化为宽字节wchar_t*    
wchar_t* AnsiToUnicode(const char* szStr);

// 写指针字节集到内存 address目标 ptr数据 length长度
void WriteBytes(void* address, void* ptr, size_t length);

// 写Vector字节集到内存 address目标内存地址  Vector字节集数据
void WriteVectorBytes(void* address, std::vector<BYTE> Vector_BYTE);

// 字符串转字节集
std::vector<BYTE> stringToBytes(const std::string& str);

// 转换颜色
std::vector<uint8_t> hexStringToByteArray(const std::string& hex);
// vector颜色转byte
std::vector<BYTE> VectorToBytes(const std::string& hex);

// 公告Call(喇叭基址)
using _game_notice = void(__fastcall*)(UINT ecx, UINT edx, PCWCHAR str, INT rgb, INT type, INT n1, INT n2, INT n3);
const _game_notice game_notice = (_game_notice)NOTICE_CALL;

// 喊话Call
using _game_shout = void(__fastcall*)(UINT ecx, UINT edx, PCWCHAR str, INT type, INT n2, INT n3);
const _game_shout game_shout = (_game_shout)SHOUT_CALL;

// 文本Call
using _game_text1 = void(__fastcall*)(UINT ecx, UINT edx, INT type);
const _game_text1 game_text1 = (_game_text1)0x1206550;
using _game_text2 = void(__fastcall*)(UINT ecx, UINT edx, INT x, INT y, INT rgb, PCWCHAR str);
const _game_text2 game_text2 = (_game_text2)0x1206BD0;
using _game_text3 = void(__fastcall*)(UINT ecx, UINT edx);
const _game_text3 game_text3 = (_game_text3)0x1206570;

namespace GameCall {
	// 发送文本call   type 14喇叭公告  17系统公告 37个人公告
	void SendText(PCWCHAR str, INT rgb, INT type);
	// 喊话  type 3附近人 1悄悄话（交易对话） 喇叭11 师徒8  工会6
	void Shout(PCWCHAR str, INT type = 3);
	// 绘制文本
	void DrawText2(INT x, INT y, INT rgb, PCWCHAR str);
}