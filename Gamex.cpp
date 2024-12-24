#pragma once
#include "Gamex.h"
#include "Memory.h"
#include "Hook.h"
#include "FastCall.h"
#include "Logger.h"
#include "xini_file.h"

// 创建读写类
Memory dx;

// 载入配置
static void loadConfig()
{
	std::string config_file = GetProgramDir() + '\\' + "dof.ini";
	xini_file_t xini_file(config_file);// 初始化配置文件读写类

	if (!fs::exists(config_file)) {
		xini_file["系统配置"]["服务器IP"] = "192.168.200.131";
		xini_file["系统配置"]["客户端版本"] = "0627";
		xini_file["系统配置"]["本地日志"] = 0;

		xini_file["功能配置"]["文本粘贴权限"] = 1;
		xini_file["功能配置"]["邮件GM标识"] = 1;
		xini_file["功能配置"]["关闭回购商店"] = 1;
		xini_file["功能配置"]["技能栏显示技能名称"] = 1;
		xini_file["功能配置"]["修复233包头"] = 1;
		xini_file["功能配置"]["修复移动物品"] = 1;
		xini_file["功能配置"]["修复字母显示"] = 1;
		xini_file["功能配置"]["禁用最小化其他窗口"] = 0;
		xini_file["功能配置"]["缩放优化"] = 0;
	}

	int openLog = xini_file["系统配置"]["本地日志"];
	LogMessage("EXE执行路径 " + config_file, openLog);
	std::string GameHost = (const char*)xini_file["系统配置"]["服务器IP"];
	LogMessage("服务器IP:" + GameHost, openLog);
	std::string exeType = (const char*)xini_file["系统配置"]["客户端版本"];
	LogMessage("客户端版本:" + exeType, openLog);


	int Feature1 = xini_file["功能配置"]["文本粘贴权限"];
	int Feature2 = xini_file["功能配置"]["邮件GM标识"];
	int Feature3 = xini_file["功能配置"]["关闭回购商店"];
	int Feature4 = xini_file["功能配置"]["技能栏显示技能名称"];
	int Feature5 = xini_file["功能配置"]["修复233包头"];
	int Feature6 = xini_file["功能配置"]["修复移动物品"];
	int Feature7 = xini_file["功能配置"]["修复字母显示"];
	int Feature8 = xini_file["功能配置"]["禁用最小化其他窗口"];
	int Feature9 = xini_file["功能配置"]["缩放优化"];

	if (Feature1 == 1) {
		// 开启[Ctrl+v]粘贴权限
		SetClipboardData(exeType);
		LogMessage("开启[Ctrl+v]粘贴权限", openLog);
	}

	if (Feature2 == 1) {
		// 开启台服DNF邮件GM标识
		FixGMofMail(exeType);
		LogMessage("开启台服DNF邮件GM标识", openLog);
	}
	if (Feature3 == 1) {
		// 关闭NPC重新回购
		DisableBuyback(exeType);
		LogMessage("关闭NPC重新回购", openLog);
	}
	if (Feature4 == 1) {
		// 技能栏默认显示技能名称
		ShowSkillName(exeType);
		LogMessage("技能栏默认显示技能名称", openLog);
	}
	if (Feature5 == 1) {
		// 修复233包头异常
		FixPackage(exeType);
		LogMessage("修复233包头异常", openLog);
	}
	if (Feature6 == 1) {
		// 修复 "//移动物品" 命令至脚下
		FixItemPosCMD(exeType);
		LogMessage("修复‘//移动物品’命令至脚下", openLog);
	}
	if (Feature7 == 1) {
		// 修复字母‘R’&‘I’
		FixLetterText(exeType);
		LogMessage("修复字母‘R’&‘I’", openLog);
	}
	if (Feature8 == 1) {
		// 禁用启动游戏时最小化其他窗口 @光头大佬
		DisableOtherWinMin(exeType);
		LogMessage("禁用启动游戏时最小化其他窗口", openLog);
	}
	if (Feature9 == 1) {
		// 缩放优化(取消[use zoom rate]标签镜头跟随) 感觉不明显
		FreeZoomRate(exeType);
		LogMessage("缩放优化(取消[use zoom rate]标签镜头跟随)", openLog);
	}
}

// 初始化
void Gamex::DLL_Main() {
	// TODO 通过dnf.exe获取版本信息 & 配置文件获取
	loadConfig();
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
	else if (exeType == "1031") {
		// 兼容1031exe
		dx.Writes(0x7458C7, static_cast<const void*>(bAddr), sizeof(bAddr));
	}
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

// 禁用启动游戏时最小化其他窗口 @光头大佬
void DisableOtherWinMin(std::string exeType) {
	if (exeType == "0627") {
		memset((LPVOID)0x006FC6FC, 0x90, 18);
	}
	else if (exeType == "1031") {
		//memset((LPVOID)0x7199CE, 0x90, 18);
		//*(char*)0x7199CA = 0xEB; // 10进制7444938 转化16进制 0x7199CA
		RtlCopyMemory((LPVOID)0x7199CA, "\xEB", 1); // 未测试
	}
}