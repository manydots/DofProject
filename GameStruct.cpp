#include "GameStruct.h"

void GameStruct::Load()
{
	UINT Character_Base = readVal(CHARACTER_BASE);
	character.Name = (wchar_t*)readVal(Character_Base + 0x258);
	character.X = ReadFloat(Character_Base + 0x18c);
	character.Y = ReadFloat(Character_Base + 0x190);
	character.Z = ReadFloat(Character_Base + 0x194);
	character.HP = ReadDword(Character_Base + 0x36A0); // 最大血量
	character.State = ReadDword(ReadDword(ReadDword(GAME_STATE) + 0x14) + 0x28); // 人物状态

	// 0x1A5FB18 房间编号基址  时间基址0x20A050 房间坐标偏移0x8C 副本当前X偏移0x610 副本当前Y偏移0x614
	character.RoomX = ReadDword(ReadDword(ReadDword(ReadDword(0x1A5FB18) + 0x20A050) + 0x8C) + 0x610);
	character.RoomY = ReadDword(ReadDword(ReadDword(ReadDword(0x1A5FB18) + 0x20A050) + 0x8C) + 0x614);
	LogMessage("自身属性：State=%d, X=%0.1f,Y=%0.1f,Z=%0.1f 房间坐标(%d,%d) MaxHP=%d", character.State, character.X, character.Y, character.Z, character.RoomX, character.RoomY, character.HP);
}

// 释放技能(技能代码 伤害 x轴 y轴 z轴)
void GameStruct::ReleaseSkill(INT skillId, INT injury) {
	this->Load();
	INT x = static_cast<INT>(character.X);
	INT y = static_cast<INT>(character.Y);
	INT z = static_cast<INT>(character.Z);

	// 手动获取人物位置
	_asm {
		pushad
		push 0
		push 0
		push 0
		push 0
		push 0
		push 0
		push 0x4
		push 0
		push 0
		push z // z轴
		push y // y轴
		push x // x轴
		push injury // 伤害
		push skillId // 技能代码
		mov ecx, dword ptr[CHARACTER_BASE] //人物基址
		mov ecx, [ecx]
		push ecx
		mov eax, SIMULATE_CALL // 模拟call
		call eax
		popad
	}
}

wchar_t* GameStruct::GetName() {
	UINT Character_Base = readVal(CHARACTER_BASE);
	character.Name = (wchar_t*)readVal(Character_Base + 0x258);
	char* name = UnicodeToAnsi(character.Name);
	LogMessage("角色名称：%s", name);

	return character.Name;
}


// 地下城中使用消耗品 itemId 物品id
static void UseConsumable(const int& itemId)
{
	LogMessage("地下城中使用消耗品Id:%d", itemId, "");

	_asm {
		pushad
		mov ecx, dword ptr[CHARACTER_BASE] // 人物基址
		mov edx, [ecx]
		mov eax, itemId // 物品id(16进制)
		push eax
		mov edx, [edx + 0x5E4]
		call edx
		popad
	}
}

// 地下城中使用药剂
void GameStruct::UseDungeonItem()
{
	/**
	* 2600027 神灵的庇佑 0x27ac5b
	* 2600261 28号 0x27ad45
	* 2680709 杜尔夫
	*/
	// 定义物品数组
	//int DrugsArr[2] = { 0x27ad45,0x27ac5b };
	// 计算元素个数
	/*size_t eleNum = sizeof(DrugsArr) / sizeof(DrugsArr[0]);
	for (size_t i = 0; i < eleNum; i++)
	{
		int itemId = DrugsArr[i];
		UseConsumable(itemId);
	}*/

	// 游戏崩溃 汇编直接注入正常???
	__asm {
		pushad
		mov ecx, [0x1ab7cdc]
		mov edx, [ecx]
		mov eax, 0x27ac5b
		push eax
		mov edx, [edx + 0x5E4]
		call edx
		popad
	}
}

