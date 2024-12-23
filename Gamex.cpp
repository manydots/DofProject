#pragma once
#include "Gamex.h"
#include "Memory.h"
#include "Hook.h"
#include "FastCall.h"

// 创建读写类
Memory dx;

// 初始化
void Gamex::DLL_Main() {

	// TODO 通过dnf.exe获取版本信息
	std::string exeType = "0627";

	// 修复233包头异常
	FixPackage(exeType);
	// 关闭NPC重新回购
	DisableBuyback(exeType);
	// 开启[Ctrl+v]粘贴权限
	SetClipboardData(exeType);
	// 修复字母‘R’&‘I’
	FixLetterText(exeType);
	// 缩放优化(取消[use zoom rate]标签镜头跟随) 感觉不明显
	// FreeZoomRate(exeType);
	// 修复 "//移动物品" 命令至脚下
	FixItemPosCMD(exeType);
	// 开启台服DNF邮件GM标识
	FixGMofMail(exeType);
	// 技能栏默认显示技能名称
	ShowSkillName(exeType);
};

// 修复233包头异常
void FixPackage(std::string exeType)
{
	// 字节集 写
	BYTE bAddr[6] = { 0xEB, 0x11, 0x90, 0x90, 0x90, 0x90 };
	// dx.Writes(0x7539015, static_cast<const void*>(bAddr), sizeof(bAddr));

	// 兼容0627exe
	if (exeType == "0627") {
		// 写法1：使用Memory类
		dx.Writes(0x727017, static_cast<const void*>(bAddr), sizeof(bAddr));
		// 写法2：使用memcpy
		// memcpy((void*)0x727017, "\xEB\x11\x90\x90\x90\x90", 6);
	}
	else if (exeType == "0725") {
		// 兼容0725exe
		dx.Writes(0x730947, static_cast<const void*>(bAddr), sizeof(bAddr));
	}

	// 1031[未测试，木青插件中已修复]
	// dx.Writes(0x7458C7, static_cast<const void*>(bAddr), sizeof(bAddr));
}


// 关闭NPC重新回购
void DisableBuyback(std::string exeType) {
	// 0627 0x00EA8663
	if (exeType == "0627") {
		// 修复线条空缺问题
		WriteCall((void*)0x00EA8631, &my_getLineSize);
		// 关闭NPC重新回购
		memcpy((void*)0x00EA8663, "\x66\xC7\x47\x0C\x00\x00\xEB\x4E\x90", 9);
	}
}

// 开启[Ctrl+v]粘贴权限2.0
void SetClipboardData(std::string exeType) {
	// 0627
	if (exeType == "0627") {
		// *(WORD*)0x011C53B0 = 0x01B0;
		memcpy((void*)0x011C53AA, "\xEB\x0C\x90\x90\x90\x90", 6);
	}
}

// 修复字母‘R’&‘I’
void FixLetterText(std::string exeType) {
	// 0627
	if (exeType == "0627") {
		// 修复字母‘R’
		WriteJmp((void*)0x015319C3, (void*)R_Text1);
		WriteJmp((void*)0x0150F49F, (void*)R_Text2);

		// 修复字母‘I’
		*(BYTE*)0x011EE391 = 0xEB;
		memcpy((void*)0x011EEDF5, "\xE9\x24\x02\x00\x00\x90", 6);
	}
}

// 缩放优化(取消[use zoom rate]标签镜头跟随)
void FreeZoomRate(std::string exeType) {
	// 0627
	if (exeType == "0627") {
		*(BYTE*)0x008E3023 = 0xEB;
		memcpy((void*)0x008E3114, "\xEB\x0E\x90\x90\x90", 5);
	}
}

// 修复 "//移动物品" 命令至脚下
void FixItemPosCMD(std::string exeType) {
	// 0627
	if (exeType == "0627") {
		WriteCall((void*)0x00950716, (void*)my_setItemPosCMD2);
	}
}

// 开启台服DNF邮件GM标识
void FixGMofMail(std::string exeType) {
	// 0627修复邮件GM标志
	if (exeType == "0627") {
		*(char*)0x0094E948 = 16;//帧数
		// Interface/newstyle/windows/Mail/AddingMailControl.img
		*(int*)0x0094E94A = 0x015CCE68;
		WriteJmp((void*)0x00949050, &setGMofMail);
	}
}

// 技能栏默认显示技能名称
void ShowSkillName(std::string exeType) {
	if (exeType == "0627") {
		// 0627默认开启技能名称
		*(WORD*)0x006D50FA = 0x12EB;
	}
}
