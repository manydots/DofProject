#pragma once
#include "Game.h"

struct Character
{
	wchar_t* Name;
	DWORD  HP;
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
	DWORD State; // ����״̬ 1���� 2����/ѡ�񸱱� 3������
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