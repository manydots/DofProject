#include "GameStruct.h"

void GameStruct::Load()
{
	UINT Character_Base = readVal(CHARACTER_BASE);
	character.Name = (wchar_t*)readVal(Character_Base + 0x258);
	character.X = ReadFloat(Character_Base + 0x18c);
	character.Y = ReadFloat(Character_Base + 0x190);
	character.Z = ReadFloat(Character_Base + 0x194);
	character.HP = ReadDword(Character_Base + 0x36A0); // ���Ѫ��
	character.State = ReadDword(ReadDword(ReadDword(GAME_STATE) + 0x14) + 0x28); // ����״̬
	LogMessage("�������ԣ�State=%d, X=%f,Y=%f,Z=%f, MaxHP=%d", character.State, character.X, character.Y, character.Z, character.HP);
}

// �ͷż���(���ܴ��� �˺� x�� y�� z��)
void GameStruct::ReleaseSkill(INT skillId, INT injury) {
	this->Load();
	INT x = static_cast<INT>(character.X);
	INT y = static_cast<INT>(character.Y);
	INT z = static_cast<INT>(character.Z);

	// �ֶ���ȡ����λ��
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
		push z // z��
		push y // y��
		push x // x��
		push injury // �˺�
		push skillId // ���ܴ���
		mov ecx, dword ptr[CHARACTER_BASE] //�����ַ
		mov ecx, [ecx]
		push ecx
		mov eax, SIMULATE_CALL // ģ��call
		call eax
		popad
	}
}

wchar_t* GameStruct::GetName() {
	UINT Character_Base = readVal(CHARACTER_BASE);
	character.Name = (wchar_t*)readVal(Character_Base + 0x258);
	char* name = UnicodeToAnsi(character.Name);
	LogMessage("��ɫ���ƣ�%s", name);

	return character.Name;
}


// ���³���ʹ������Ʒ itemId ��Ʒid
static void UseConsumable(const int& itemId)
{
	LogMessage("���³���ʹ������ƷId:%d", itemId, "");

	_asm {
		pushad
		mov ecx, dword ptr[CHARACTER_BASE] // �����ַ
		mov edx, [ecx]
		mov eax, 0x27ad45 // ��Ʒid(16����)
		push eax
		mov edx, [edx + 0x5E4]
		call edx
		popad
	}
}

// ���³���ʹ��ҩ��
void GameStruct::UseDungeonItem()
{
	/**
	* 2600027 ����ı��� 0x27ac5b
	* 2600261 28�� 0x27ad45
	* 2680709 �Ŷ���
	*/
	// ������Ʒ����
	//int DrugsArr[2] = { 0x27ad45,0x27ac5b };
	// ����Ԫ�ظ���
	/*size_t eleNum = sizeof(DrugsArr) / sizeof(DrugsArr[0]);
	for (size_t i = 0; i < eleNum; i++)
	{
		int itemId = DrugsArr[i];
		UseConsumable(itemId);
	}*/

	// ��Ϸ���� ���ֱ��ע������???
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

