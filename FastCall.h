#pragma once
#include "Hook.h"
#include "GameStruct.h"
#include "CLVEH.h"
#include "Hotkey.h"

GameStruct gameStruct; // ��ʼ����ɫ��Ϣ�ṹ��
HOTKEY_ID vkid_F4 = 0;

// 0627�ر�NPC���»ع����޸�������ȱ���� @���д��� �ṩ
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

// �޸���ĸ��R��
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

// �޸� "//�ƶ���Ʒ" ����������
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

// ����һ�� ���ڸ���������ʹ�� ��//�ƶ���Ʒ�� ����
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

// �������� ʹ��һ��
// ��������Ч�����鲢��ʵ��ǰexe�ַ���������� 13018>//�ƶ���Ʒ
typedef bool(__thiscall* _setItemPos)(DWORD*);
_setItemPos setItemPos = (_setItemPos)0x0222EB06;
bool __fastcall my_setItemPosCMD2(DWORD* pthis)
{

	pthis[5277] = getXPos(pthis);
	pthis[5278] = getYPos(pthis);
	return setItemPos(pthis);
}

// ����̨��DNF�ʼ�GM��ʶ
typedef LPCWSTR(__thiscall* _getMailName)(DWORD*);
_getMailName getMailName = (_getMailName)0x9493B0;
static bool __fastcall setGMofMail(DWORD* pthis)
{
	LPCWSTR MailName = getMailName(pthis);
	if (wcscmp(L"GM", MailName) == 0 || wcscmp(L"ð�ռ���", MailName) == 0 || wcscmp(L"DNF����Ա", MailName) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 0627�޸�����֮��ͨ�ط��س����̯��ֽ��������3.0�Ż��棩
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

// 0627Ĭ�ϴ���������
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

// �ϵ�Ĵ�����
void hookCallBackFun(_EXCEPTION_POINTERS* ExceptionInfo) {
	// EIP(��ǰHOOK�ĵ�ַ)
	LogMessage("VEH -> EIP=%X��ECX=%X��EDX=%X������1=%X", ExceptionInfo->ContextRecord->Eip, ExceptionInfo->ContextRecord->Ecx, ExceptionInfo->ContextRecord->Edx, ReadDword(ExceptionInfo->ContextRecord->Esp + 4));
}

// �ȼ�F4�����ص�
void InjectHotKey() {
	gameStruct.ReleaseSkill();
	LogMessage("HotKey:[%s]������", "F4");
}

// 0627 HOOK������Ϣ
using _send_gcommand = INT(*)(PCWCHAR str);
const _send_gcommand send_gcommand = (_send_gcommand)0x951620;
INT sendCommand(PCWCHAR str, INT type)
{
	//wchar_t buffer[64];
	//formatAndConcat(buffer, _countof(buffer), L"CALL���", characterName);
	//send_notice(L"CALL", rgb(249, 38, 114), 37);
	//LogMessage(characterName, 1);
	/*char* pNewBuffer = UnicodeToAnsi(characterName);
	LogMessage(pNewBuffer, 1);*/

	// �����־(�ͻ�����������)
	LogMessage(str, 1);
	// �������̨��־
	LogMessage(UnicodeToAnsi(str));
	// �ж�strǰ�����ַ��Ƿ����'//'��ȷ���0
	if (wcsncmp(L"//", str, 2) == 0)
	{
		// TEST ��ȡ��ɫ����
		if (wcsncmp(L"//GET NAME", str, 10) == 0) {
			// TCHAR characterName[64] = { 0 };
			// ReadMemoryBytes(characterName, readVal(readVal(CHARACTER_BASE) + 0x258), 32);

			wchar_t buffer[64];
			formatAndConcatSafe(buffer, sizeof(buffer), L"CALL %ls", gameStruct.GetName());
			// #f92672
			GameCall::SendText(buffer, rgb(249, 38, 114), 37);
			return 1;
		}

		// TEST HOOK��//HOOK������VEH HOOK
		if (wcsncmp(L"//HOOK", str, 6) == 0) {
			GameCall::SendText(L"HOOK�����ɹ�", rgb(249, 38, 114), 37);

			// ����AddVeh���
			// CCLVEH::Instance()->AddVeh(const_cast<char*>("hook1"), 0, 0, SEND_CALL, 1, 0, hookCallBackFun); // ����CALL
			CCLVEH::Instance()->AddVeh(const_cast<char*>("hook2"), 0, 0, CACHE_CALL, 1, 0, hookCallBackFun); // ����CALL
			CCLVEH::Instance()->AddVeh(const_cast<char*>("hook3"), 0, 0, ENCRYPT_CALL1, 1, 0, hookCallBackFun); // ����CALL1
			CCLVEH::Instance()->AddVeh(const_cast<char*>("hook4"), 0, 0, ENCRYPT_CALL2, 1, 0, hookCallBackFun); // ����CALL2
			CCLVEH::Instance()->AddVeh(const_cast<char*>("hook5"), 0, 0, ENCRYPT_CALL4, 1, 0, hookCallBackFun); // ����CALL4

			// �¶ϵ�
			CCLVEH::Instance()->InitVeh();
			return 1;
		}

		// TEST UNHOOK��//UNHOOK���ر�VEH HOOK,ѡ���ɫǰ�����ֶ��ر�
		if (wcsncmp(L"//UNHOOK", str, 8) == 0) {
			GameCall::SendText(L"HOOK�رճɹ�", rgb(249, 38, 114), 37);
			// �رնϵ�
			CCLVEH::Instance()->ExitVeh();
			return 1;
		}

		// TEST ����F4�ȼ�(//HOTKEY)
		if (wcsncmp(L"//HOTKEY", str, 8) == 0) {
			GameCall::SendText(L"�ȼ�F4�����ɹ�", rgb(249, 38, 114), 37);
			vkid_F4 = HotkeyMonitor((PFUNC)&InjectHotKey, VK_F4);
			return 1;
		}

		// TEST �ر�F4�ȼ�(//UNHOTKEY)
		if (wcsncmp(L"//UNHOTKEY", str, 10) == 0) {
			GameCall::SendText(L"�ȼ�F4�رճɹ�", rgb(249, 38, 114), 37);
			HotKeyUnMonitor(vkid_F4);
			return 1;
		}


		// TEST �������ݣ�//SHOUT [����]��
		if (wcsncmp(L"//SHOUT", str, 7) == 0) {
			size_t length = std::wcslen(str);
			// ����һ��std::wstring����
			std::wstring wstr(str, length);
			std::wstring _str = wstr.substr(7);
			const wchar_t* pwchar_str = _str.c_str();
			GameCall::Shout(pwchar_str);
			return 1;
		}

		// TEST ��ȡ��ɫ��Ϣ
		if (wcsncmp(L"//GET STATE", str, 11) == 0) {
			gameStruct.Load();
			return 1;
		}

		// TEST ���³���ʹ��ҩ��
		if (wcsncmp(L"//USE", str, 5) == 0) {
			gameStruct.UseDungeonItem();
			return 1;
		}

		// TEST �ͷż��ܣ����ܴ��� �˺���
		if (wcsncmp(L"//SKILL", str, 7) == 0) {
			//SKILL 22228 1
			int _skillId = 22228; // �л�е����22228 ����[�޷����˺�]30567  ���ӱ�����ը22206
			int _injury = 999999; // �˺�999999
			size_t length = std::wcslen(str);
			// ����һ��std::wstring����
			std::wstring wstr(str, length);
			std::wstring _str = wstr.substr(7);
			// ����str���˵Ŀո�
			std::wstring trimStr = trim(_str);
			// ����һ�������ַ�����
			std::vector<std::wstring> tokens = splitStrW(trimStr);

			if (tokens.size() == 2) {
				// ʹ��std::stoi�����ַ��ַ���ת��Ϊint
				const wchar_t* skillId = tokens[0].c_str();
				const wchar_t* injury = tokens[1].c_str();

				// ��ȡ����
				if (skillId != nullptr && isNumberW(skillId))
				{
					_skillId = std::stoi(skillId, nullptr, 10); // ����3 10ʮ����
					LogMessage("����skillId:[%d]", (int*)_skillId);
				}

				// ��ȡ�˺�
				if (injury != nullptr && isNumberW(injury))
				{
					_injury = std::stoi(injury, nullptr, 10); // ����3 10ʮ����
					LogMessage("�˺�injury:[%d]", (int*)_injury);
				}
			}
			LogMessage("����[%d] �˺�[%d]", (int*)_skillId, (int*)_injury);
			gameStruct.ReleaseSkill(_skillId, _injury);
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