#pragma once
#include "Gamex.h"
#include "Memory.h"
#include "Hook.h"
#include "FastCall.h"
#include "Logger.h"
#include "xini_file.h"

// ������д��
Memory dx;

// ��������
static void loadConfig()
{
	std::string programDir = GetProgramDir();
	std::string config_file = programDir + '\\' + "dof.ini";
	xini_file_t xini_file(config_file);// ��ʼ�������ļ���д��

	std::string programPath = programDir + "\\DNF.exe";
	std::string version = GetFileVersion(programPath); // �ͻ��˰汾��Ϣ

	if (!fs::exists(config_file)) {
		xini_file["ϵͳ����"]["������IP"] = "192.168.200.131";
		xini_file["ϵͳ����"]["�ͻ��˰汾"] = version;
		xini_file["ϵͳ����"]["������־"] = 0;

		xini_file["��������"]["����GM"] = 0;
		xini_file["��������"]["�ı�ճ��Ȩ��"] = 1;
		xini_file["��������"]["�ʼ�GM��ʶ"] = 1;
		xini_file["��������"]["�رջع��̵�"] = 1;
		xini_file["��������"]["��������ʾ��������"] = 0;
		xini_file["��������"]["�޸�233��ͷ"] = 1;
		xini_file["��������"]["�޸��ƶ���Ʒ"] = 1;
		xini_file["��������"]["�޸���ĸ��ʾ"] = 1;
		xini_file["��������"]["������С����������"] = 0;
		xini_file["��������"]["�����Ż�"] = 0;
		xini_file["��������"]["�޸�����֮��"] = 1;
		xini_file["��������"]["�޸�������������"] = 0;
		//xini_file["��������"]["Ĭ�ϴ���������"] = 0;

		xini_file["��ɫ����"]["��ɫ������ɫ"] = "#FFFFFF";
		xini_file["��ɫ����"]["NPC������ɫ"] = "#E6C89B";
	}

	int openLog = xini_file["ϵͳ����"]["������־"];
	LogMessage("ִ��·�� " + config_file, openLog);
	std::string GameHost = (const char*)xini_file["ϵͳ����"]["������IP"];
	LogMessage("������IP:" + GameHost, openLog);
	xini_file["ϵͳ����"]["�ͻ��˰汾"] = version;

	// ��ȡ�ͻ��˰汾����
	std::string exeType = getExeType(version);
	LogMessage("�ͻ��˰汾:" + exeType, openLog);


	int Feature1 = xini_file["��������"]["�ı�ճ��Ȩ��"];
	int Feature2 = xini_file["��������"]["�ʼ�GM��ʶ"];
	int Feature3 = xini_file["��������"]["�رջع��̵�"];
	int Feature4 = xini_file["��������"]["��������ʾ��������"];
	int Feature5 = xini_file["��������"]["�޸�233��ͷ"];
	int Feature6 = xini_file["��������"]["�޸��ƶ���Ʒ"];
	int Feature7 = xini_file["��������"]["�޸���ĸ��ʾ"];
	int Feature8 = xini_file["��������"]["������С����������"];
	int Feature9 = xini_file["��������"]["�����Ż�"];
	int Feature10 = xini_file["��������"]["�޸�����֮��"];
	int Feature11 = xini_file["��������"]["�޸�������������"];
	//int Feature12 = xini_file["��������"]["Ĭ�ϴ���������"];
	int Feature13 = xini_file["��������"]["����GM"];


	// NPC������ɫ
	std::string NPC_Color = (const char*)xini_file["��ɫ����"]["NPC������ɫ"];
	// ��ɫ������ɫ
	std::string Character_Color = (const char*)xini_file["��ɫ����"]["��ɫ������ɫ"];

	if (Feature1 == 1) {
		// ����[Ctrl+v]ճ��Ȩ��
		Gamex::SetClipboardData(exeType);
		LogMessage("����[Ctrl+v]ճ��Ȩ��", openLog);
	}
	if (Feature2 == 1) {
		// ����̨��DNF�ʼ�GM��ʶ
		Gamex::FixGMofMail(exeType);
		LogMessage("����̨��DNF�ʼ�GM��ʶ", openLog);
	}
	if (Feature3 == 1) {
		// �ر�NPC���»ع�
		Gamex::DisableBuyback(exeType);
		LogMessage("�ر�NPC���»ع�", openLog);
	}
	if (Feature4 == 1) {
		// ������Ĭ����ʾ��������
		Gamex::ShowSkillName(exeType);
		LogMessage("������Ĭ����ʾ��������", openLog);
	}
	if (Feature5 == 1) {
		// �޸�233��ͷ�쳣
		Gamex::FixPackage(exeType);
		LogMessage("�޸�233��ͷ�쳣", openLog);
	}
	if (Feature6 == 1) {
		// �޸� "//�ƶ���Ʒ" ����������
		Gamex::FixItemPosCMD(exeType);
		LogMessage("�޸���//�ƶ���Ʒ������������", openLog);
	}
	if (Feature7 == 1) {
		// �޸���ĸ��R��&��I��
		Gamex::FixLetterText(exeType);
		LogMessage("�޸���ĸ��R��&��I��", openLog);
	}
	if (Feature8 == 1) {
		// ����������Ϸʱ��С���������� @��ͷ����
		Gamex::DisableOtherWinMin(exeType);
		LogMessage("����������Ϸʱ��С����������", openLog);
	}
	if (Feature9 == 1) {
		// �����Ż�(ȡ��[use zoom rate]��ǩ��ͷ����) �о�������
		Gamex::FreeZoomRate(exeType);
		LogMessage("�����Ż�(ȡ��[use zoom rate]��ǩ��ͷ����)", openLog);
	}
	if (Feature10 == 1) {
		// �޸�����֮�� 
		Gamex::FixLordTower(exeType);
		LogMessage("�޸�����֮��ͨ�ط��س����̯��ֽ������&������Ч��β���BUG", openLog);
	}
	if (Feature11 == 1) {
		// �޸���ɫ����ְҵ��������
		Gamex::FixCharacterName(exeType);
		LogMessage("�޸���ɫ����ְҵ��������", openLog);
	}
	// [�쳣]
	//if (Feature12 == 1) {
	//	// Ĭ�ϴ���������0627 @����
	//	Gamex::CreateCreatorMage(exeType);
	//	LogMessage("Ĭ�ϴ���������", openLog);
	//}
	if (Feature13 == 1) {
		// ����GM
		Gamex::LocalGM_Mode(exeType);
		LogMessage("��������GM", openLog);
	}

	// ����NPC������ɫ
	if (!NPC_Color.empty()) {
		Gamex::OverloadNPC_Color(exeType, NPC_Color);
		LogMessage("����NPC������ɫ:" + NPC_Color, openLog);
	}
	// ���ý�ɫ������ɫ
	if (!Character_Color.empty()) {
		Gamex::OverloadCharacter_Color(exeType, Character_Color);
		LogMessage("���ý�ɫ������ɫ:" + Character_Color, openLog);
	}
}

// ��ʼ��
namespace Gamex {
	void DLL_Main() {
		// TODO ͨ��dnf.exe��ȡ�汾��Ϣ & �����ļ���ȡ
		loadConfig();
	}
	// �޸�233��ͷ�쳣
	void FixPackage(std::string exeType)
	{
		// �ֽڼ� д
		BYTE bAddr[6] = { 0xEB, 0x11, 0x90, 0x90, 0x90, 0x90 };
		// dx.Writes(0x7539015, static_cast<const void*>(bAddr), sizeof(bAddr));

		// ����0627exe
		if (exeType == "0627") {
			// д��1��ʹ��Memory��
			dx.Writes(0x727017, static_cast<const void*>(bAddr), sizeof(bAddr));
			// д��2��ʹ��memcpy
			// memcpy((void*)0x727017, "\xEB\x11\x90\x90\x90\x90", 6);
		}
		else if (exeType == "0725") {
			// ����0725exe
			dx.Writes(0x730947, static_cast<const void*>(bAddr), sizeof(bAddr));
		}
		else if (exeType == "1031") {
			// ����1031exe
			dx.Writes(0x7458C7, static_cast<const void*>(bAddr), sizeof(bAddr));
		}
	}


	// �ر�NPC���»ع�
	void DisableBuyback(std::string exeType) {
		// 0627 0x00EA8663
		if (exeType == "0627") {
			// �޸�������ȱ����
			WriteCall((void*)0x00EA8631, &my_getLineSize);
			// �ر�NPC���»ع�
			memcpy((void*)0x00EA8663, "\x66\xC7\x47\x0C\x00\x00\xEB\x4E\x90", 9);
		}
	}

	// ����[Ctrl+v]ճ��Ȩ��2.0
	void SetClipboardData(std::string exeType) {
		// 0627
		if (exeType == "0627") {
			// *(WORD*)0x011C53B0 = 0x01B0;
			memcpy((void*)0x011C53AA, "\xEB\x0C\x90\x90\x90\x90", 6);
		}
	}

	// �޸���ĸ��R��&��I��
	void FixLetterText(std::string exeType) {
		// 0627
		if (exeType == "0627") {
			// �޸���ĸ��R��
			WriteJmp((void*)0x015319C3, (void*)R_Text1);
			WriteJmp((void*)0x0150F49F, (void*)R_Text2);

			// �޸���ĸ��I��
			*(BYTE*)0x011EE391 = 0xEB;
			memcpy((void*)0x011EEDF5, "\xE9\x24\x02\x00\x00\x90", 6);
		}
	}

	// �����Ż�(ȡ��[use zoom rate]��ǩ��ͷ����)
	void FreeZoomRate(std::string exeType) {
		// 0627
		if (exeType == "0627") {
			*(BYTE*)0x008E3023 = 0xEB;
			memcpy((void*)0x008E3114, "\xEB\x0E\x90\x90\x90", 5);
		}
	}

	// �޸� "//�ƶ���Ʒ" ����������
	void FixItemPosCMD(std::string exeType) {
		// 0627
		if (exeType == "0627") {
			WriteCall((void*)0x00950716, (void*)my_setItemPosCMD2);
		}
	}

	// ����̨��DNF�ʼ�GM��ʶ
	void FixGMofMail(std::string exeType) {
		// 0627�޸��ʼ�GM��־
		if (exeType == "0627") {
			*(char*)0x0094E948 = 16;//֡��
			// Interface/newstyle/windows/Mail/AddingMailControl.img
			*(int*)0x0094E94A = 0x015CCE68;
			WriteJmp((void*)0x00949050, &setGMofMail);
		}
	}

	// ������Ĭ����ʾ��������
	void ShowSkillName(std::string exeType) {
		if (exeType == "0627") {
			// 0627Ĭ�Ͽ�����������
			*(WORD*)0x006D50FA = 0x12EB;
		}
	}

	// ����������Ϸʱ��С���������� @��ͷ����
	void DisableOtherWinMin(std::string exeType) {
		if (exeType == "0627") {
			memset((LPVOID)0x006FC6FC, 0x90, 18);
		}
		else if (exeType == "1031") {
			//memset((LPVOID)0x7199CE, 0x90, 18);
			//*(char*)0x7199CA = 0xEB; // 10����7444938 ת��16���� 0x7199CA
			RtlCopyMemory((LPVOID)0x7199CA, "\xEB", 1); // δ����
		}
	}

	// �޸�����֮�� 
	void FixLordTower(std::string exeType) {
		if (exeType == "0627") {
			// �޸�����֮��ͨ�ط��س����̯��ֽ��������3.0�Ż��棩
			WriteJmp((void*)0x00FFDA95, &fixNewBoundingRound);
			// �޸�����֮��������Ч��β���BUG
			*(char*)0x00436382 = -1;
		}
	}

	// �޸���ɫ����ְҵ��������
	void FixCharacterName(std::string exeType) {
		if (exeType == "0627") {
			*(BYTE*)0x0084995A = 0x8F;
		}
	}

	// Ĭ�ϴ���������0627 @����
	void CreateCreatorMage(std::string exeType) {
		if (exeType == "0627") {
			*(char*)0x10F3338 = 11;
			WriteJmp((void*)0x101F3341, &DefaultCharacter);
		}
	}

	// ����GM
	void LocalGM_Mode(std::string exeType) {
		if (exeType == "0627") {
			// ԭʼ 55 8B EC 51 81 C1 90 03 00 00   -> 03 00 00 �� 02 08 09
			memcpy((void*)0x00751830, "\x55\x8B\xEC\x51\x81\xC1\x90\x02\x08\x09", 10);
			// ԭʼ 81 C1 90 03 00 00 8D 45 FC 50 8D 03  -> 03 00 00 �� 02 08 09
			memcpy((void*)0x00751834, "\x81\xC1\x90\x02\x08\x09\x8D\x45\xFC\x50\x8D", 11);
		}
	}

	// ����NPC������ɫ
	void OverloadNPC_Color(std::string exeType, std::string NPC_Color) {
		if (exeType == "0627") {
			// NPC������ɫ  Ĭ����ɫ E6 C8 9B FF
			// memcpy((void*)0x007E9279, "\x39\x96\x5b", 3);
			// BYTE cAddr[3] = { 0xF3, 0x4B, 0x7D };
			// dx.Writes(0x007E9279, static_cast<const void*>(cAddr), sizeof(cAddr));

			std::vector<uint8_t> colorBytes = hexStringToByteArray(NPC_Color);
			if (colorBytes.size() == 3) {
				BYTE cAddr[3] = { 0 };
				for (size_t i = 0; i < 3; ++i) {
					cAddr[i] = colorBytes[i];
				}
				dx.Writes(0x007E9279, static_cast<const void*>(cAddr), sizeof(cAddr));
			}
		}
	}

	// ���ý�ɫ������ɫ[CE��HOOK��ɫ���Ʋ���Ҫ��ɫ��¼����]
	void OverloadCharacter_Color(std::string exeType, std::string Character_Color) {
		if (exeType == "0627") {
			// ��ɫ������ɫ  Ĭ����ɫ FF FF FF FF
			std::vector<uint8_t> characterBytes = hexStringToByteArray(Character_Color);
			if (characterBytes.size() == 3) {
				BYTE chAddr[3] = { 0 };
				for (size_t i = 0; i < 3; ++i) {
					chAddr[i] = characterBytes[i];
				}
				dx.Writes(0x00805B78, static_cast<const void*>(chAddr), sizeof(chAddr));
				dx.Writes(0x00806439, static_cast<const void*>(chAddr), sizeof(chAddr));
			}
		}
	}
};