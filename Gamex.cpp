#pragma once
#include "Gamex.h"
#include "Memory.h"
#include "Hook.h"
#include "FastCall.h"

// ������д��
Memory dx;

// ��ʼ��
void Gamex::DLL_Main() {

	// TODO ͨ��dnf.exe��ȡ�汾��Ϣ
	std::string exeType = "0627";

	// �޸�233��ͷ�쳣
	FixPackage(exeType);
	// �ر�NPC���»ع�
	DisableBuyback(exeType);
	// ����[Ctrl+v]ճ��Ȩ��
	SetClipboardData(exeType);
	// �޸���ĸ��R��&��I��
	FixLetterText(exeType);
	// �����Ż�(ȡ��[use zoom rate]��ǩ��ͷ����) �о�������
	// FreeZoomRate(exeType);
	// �޸� "//�ƶ���Ʒ" ����������
	FixItemPosCMD(exeType);
	// ����̨��DNF�ʼ�GM��ʶ
	FixGMofMail(exeType);
	// ������Ĭ����ʾ��������
	ShowSkillName(exeType);
};

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

	// 1031[δ���ԣ�ľ���������޸�]
	// dx.Writes(0x7458C7, static_cast<const void*>(bAddr), sizeof(bAddr));
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
