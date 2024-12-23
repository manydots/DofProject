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