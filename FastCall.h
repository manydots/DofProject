#pragma once
#include "Hook.h"

// 0627关闭NPC重新回购后修复线条空缺问题 @蛐蛐大佬 提供
typedef int(__thiscall* _getLineSize_t)(uint32_t*);
typedef uint32_t* (__thiscall* _getRedeemCUI_t)(uint32_t*, int);
_getLineSize_t getLineSize = (_getLineSize_t)0x011B5E80;
_getRedeemCUI_t getRedeemCUI = (_getRedeemCUI_t)0x011B5C80;
int __fastcall my_getLineSize(uint32_t* pthis)
{
	int length = getLineSize(pthis);
	int num = (*(uint32_t*)(pthis[175] + 36) - *(uint32_t*)(pthis[175] + 32)) >> 2; // MaxIndex
	uint32_t* page = getRedeemCUI(pthis, num - 1);
	if (page)
		length -= page[14]; // Weight
	return length;
}

// 修复字母‘R’
static const wchar_t* text_R = L"R";
Naked void R_Text1()
{
	_asm {
		mov eax, text_R
		mov dword ptr ds : [0x01B47208] , eax
		mov eax, 0x015319C8
		jmp eax
	}
}
Naked void R_Text2()
{
	_asm {
		mov eax, text_R
		mov dword ptr ds : [0x01ADE05C] , eax
		mov eax, 0x0150F4A4
		jmp eax
	}
}

// 修复 "//移动物品" 命令至脚下
typedef int(__thiscall* _getXPos)(void*);
typedef int(__thiscall* _getYPos)(void*);
typedef bool(__thiscall* _isObjectType)(DWORD*, int);
typedef DWORD* (__thiscall* _getObjectManager)(DWORD*);
typedef int(__stdcall* _sq_SetCurrentPos)(DWORD*, int, int, int);

typedef DWORD* (__thiscall* _getCollisionObject)(DWORD*, int);
typedef int(__thiscall* _getCollisionObjectNumber)(DWORD*);
_getXPos getXPos = (_getXPos)0x5ACCC0;
_getYPos getYPos = (_getYPos)0x5ACEA0;
_isObjectType isObjectType = (_isObjectType)0x7EF650;
_getObjectManager getObjectManager = (_getObjectManager)0x5ACBC0;
_sq_SetCurrentPos sq_SetCurrentPos = (_sq_SetCurrentPos)0xBA8680;
_getCollisionObject getCollisionObject = (_getCollisionObject)0x403A80;
_getCollisionObjectNumber getCollisionObjectNumber = (_getCollisionObjectNumber)0x403AB0;

// 方法一： 可在副本内无限使用 “//移动物品” 命令
bool __fastcall my_setItemPosCMD1(DWORD* pthis)
{
	DWORD* objectManager = getObjectManager(pthis);
	for (int i = 0; i < getCollisionObjectNumber(objectManager); i++)
	{
		DWORD* collisionObject = getCollisionObject(objectManager, i);
		if (collisionObject && isObjectType(collisionObject, 289)) //0BJECTTYPE ITEM <- 289
		{
			sq_SetCurrentPos(collisionObject, getXPos(pthis), getYPos(pthis), 0);
		}
	}
	return true;
}

// 方法二： 使用一次
// 若命令无效，请检查并核实当前exe字符串编号内容 13018>//移动物品
typedef bool(__thiscall* _setItemPos)(DWORD*);
_setItemPos setItemPos = (_setItemPos)0x0222EB06;
bool __fastcall my_setItemPosCMD2(DWORD* pthis)
{

	pthis[5277] = getXPos(pthis);
	pthis[5278] = getYPos(pthis);
	return setItemPos(pthis);
}

// 开启台服DNF邮件GM标识
typedef LPCWSTR(__thiscall* _getMailName)(DWORD*);
_getMailName getMailName = (_getMailName)0x9493B0;
static bool __fastcall setGMofMail(DWORD* pthis)
{
	LPCWSTR MailName = getMailName(pthis);
	if (wcscmp(L"GM", MailName) == 0 || wcscmp(L"冒险家收", MailName) == 0 || wcscmp(L"DNF管理员", MailName) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 0627修复领主之塔通关返回城镇摆摊或分解机崩溃（3.0优化版）
Naked void fixNewBoundingRound() {
	_asm {
		mov eax, 0x006FC760
		call eax
		mov ebx, [eax + 0xB0]
		cmp dword ptr ds : [ebx + 0x2A0] , 13
		jne label1
		mov dword ptr ds : [ebx + 0x2A0] , -1
		label1 :
		mov ecx, eax
		mov eax, 0x007529F0
		call eax
		mov eax, [eax + 0x4C]
		cmp eax, 0
		je label2
		mov edi, dword ptr ds : [eax + 0x644]
		push 0x00FFDAAA
		ret
		label2 :
		push 0x00FFDB0C
			ret
	}
}

// 0627默认创建缔造者
Naked void DefaultCharacter() {
	static DWORD pfCha_ret = 0x010F3347;
	_asm {
		cmp dword ptr ds : [0x01A5FE1C] , 0x01
		jae label1
		mov eax, 0xA
		label1 :
		mov DWORD PTR ds : [esi + 0xC0] , eax
		jmp pfCha_ret
	}
}

// 0627 HOOK聊天消息
using _send_gcommand = INT(*)(PCWCHAR str);
const _send_gcommand send_gcommand = (_send_gcommand)0x951620;
INT sendCommand(PCWCHAR str, INT type)
{
	//wchar_t buffer[64];
	//formatAndConcat(buffer, _countof(buffer), L"CALL你好", characterName);
	//send_notice(L"CALL", rgb(249, 38, 114), 37);
	//LogMessage(characterName, 1);
	/*char* pNewBuffer = UnicodeToAnsi(characterName);
	LogMessage(pNewBuffer, 1);*/

	// 输出日志(客户端输入内容)
	LogMessage(str, 1);
	// 输出控制台日志
	LogMessage(UnicodeToAnsi(str));
	// 判断str前两个字符是否等于'//'相等返回0
	if (wcsncmp(L"//", str, 2) == 0)
	{
		// TEST 获取角色名称
		if (wcsncmp(L"//GET NAME", str, 10) == 0) {
			TCHAR characterName[64] = { 0 };
			ReadMemoryBytes(characterName, readVal(readVal(CHARACTER_BASE) + 0x258), 32);
			//ReadMemoryBytes(characterName, ReadDWORD(ReadDWORD(CHARACTER_BASE) + 0x258), 32);
			wchar_t buffer[64];
			formatAndConcatSafe(buffer, sizeof(buffer), L"CALL %ls", characterName);
			// #f92672
			GameCall::SendText(buffer, rgb(249, 38, 114), 37);
			return 1;
		}

		// TEST 喊话内容（//SHOUT [内容]）
		if (wcsncmp(L"//SHOUT", str, 7) == 0) {
			size_t length = std::wcslen(str);
			// 创建一个std::wstring对象
			std::wstring wstr(str, length);
			std::wstring _str = wstr.substr(7);
			const wchar_t* pwchar_str = _str.c_str();
			GameCall::Shout(pwchar_str);
			return 1;
		}

		return send_gcommand(str);
	}

	//if (!wcsncmp(L"//dofile ", str, 9))
	//{
	//	// TODO
	//	return 1;
	//}
	return send_gcommand(str);
}