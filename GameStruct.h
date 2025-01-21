#pragma once
#include "Game.h"

struct Character
{
	wchar_t* Name;
	DWORD  HP;
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
	DWORD State; // 人物状态 1街上 2加载/选择副本 3副本里
};

class GameStruct
{

public:
	Character character;

	void Load();
	void ReleaseSkill(INT skillId = 22228, INT injury = 999999);
	void UseDungeonItem();
	wchar_t* GetName();
};