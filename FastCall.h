#pragma once
#include "Gamex.h"

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