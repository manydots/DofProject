#pragma once
#include "Gamex.h"
#include "Memory.h"
#include "Hook.h"
#include "FastCall.h"

// ������д��
Memory dx;

// ��ʼ��
void Gamex::DLL_Main(std::string exeType) {
	// �޸�233��ͷ�쳣
	FixPackage(exeType);
	// �ر�NPC���»ع�
	DisableBuyback(exeType);
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
