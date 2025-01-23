#pragma once
#include "Gamex.h"
#include "Game.h"
#include "FastCall.h"
#include "Mosaic.h"
#include "SkilSlot.h"

// 创建读写类
Memory dx;

// 载入配置
static void loadConfig()
{
	std::string programDir = GetProgramDir();
	std::string config_file = programDir + '\\' + "dof.ini";
	xini_file_t xini_file(config_file);// 初始化配置文件读写类

	std::string programPath = programDir + "\\DNF.exe";
	std::string version = GetFileVersion(programPath); // 客户端版本信息

	if (!fs::exists(config_file)) {
		xini_file["系统配置"]["服务器IP"] = "192.168.200.131";
		xini_file["系统配置"]["客户端版本"] = version;
		xini_file["系统配置"]["本地日志"] = 0;
		xini_file["系统配置"]["HOOK聊天消息"] = 0;

		xini_file["功能配置"]["本地GM"] = 0; // 建议关闭
		xini_file["功能配置"]["装备镶嵌"] = 0;
		xini_file["功能配置"]["文本粘贴权限"] = 1;
		xini_file["功能配置"]["邮件GM标识"] = 1;
		xini_file["功能配置"]["关闭回购商店"] = 1;
		xini_file["功能配置"]["技能栏显示技能名称"] = 0;
		xini_file["功能配置"]["修复233包头"] = 1;
		xini_file["功能配置"]["修复移动物品"] = 1;
		xini_file["功能配置"]["修复字母显示"] = 1;
		xini_file["功能配置"]["禁用最小化其他窗口"] = 0;
		xini_file["功能配置"]["缩放优化"] = 0;
		xini_file["功能配置"]["修复领主之塔"] = 1;
		xini_file["功能配置"]["修复二觉名称乱码"] = 0;
		xini_file["功能配置"]["默认创建缔造者"] = 0;

		xini_file["颜色配置"]["启用"] = 0;
		xini_file["颜色配置"]["角色名称颜色"] = "#FFFFFF";
		xini_file["颜色配置"]["NPC名称颜色"] = "#E6C89B"; // Hook

		xini_file["键位配置"]["启用"] = 0;
		xini_file["键位配置"]["HookKey1"] = 55; // Hook菜单ID
		xini_file["键位配置"]["1键X轴"] = 718;
		xini_file["键位配置"]["1键Y轴"] = 520;
		xini_file["键位配置"]["HookKey2"] = 56; // Hook菜单ID
		xini_file["键位配置"]["2键X轴"] = 718;
		xini_file["键位配置"]["2键Y轴"] = 558;
	}

	int openLog = xini_file["系统配置"]["本地日志"];

	if (openLog == 1) {
		CreateConsole();
	}

	LogMessage("执行路径 %s", config_file);
	std::string GameHost = (const char*)xini_file["系统配置"]["服务器IP"];
	LogMessage("服务器IP:" + GameHost, openLog);
	LogMessage("服务器IP:%s", GameHost.c_str());
	xini_file["系统配置"]["客户端版本"] = version;

	// 获取客户端版本类型
	std::string exeType = getExeType(version);
	LogMessage("客户端版本:" + exeType, openLog);
	LogMessage("客户端版本:%s", exeType.c_str());

	int Feature1 = xini_file["功能配置"]["文本粘贴权限"];
	int Feature2 = xini_file["功能配置"]["邮件GM标识"];
	int Feature3 = xini_file["功能配置"]["关闭回购商店"];
	int Feature4 = xini_file["功能配置"]["技能栏显示技能名称"];
	int Feature5 = xini_file["功能配置"]["修复233包头"];
	int Feature6 = xini_file["功能配置"]["修复移动物品"];
	int Feature7 = xini_file["功能配置"]["修复字母显示"];
	int Feature8 = xini_file["功能配置"]["禁用最小化其他窗口"];
	int Feature9 = xini_file["功能配置"]["缩放优化"];
	int Feature10 = xini_file["功能配置"]["修复领主之塔"];
	int Feature11 = xini_file["功能配置"]["修复二觉名称乱码"];
	int Feature12 = xini_file["功能配置"]["默认创建缔造者"];
	int Feature13 = xini_file["功能配置"]["本地GM"];
	int Feature14 = xini_file["功能配置"]["装备镶嵌"];

	int Feature15 = xini_file["键位配置"]["启用"];
	int keyCode1 = xini_file["键位配置"]["HookKey1"];
	int keyCode2 = xini_file["键位配置"]["HookKey2"];

	int keyCode1x = xini_file["键位配置"]["1键X轴"];
	int keyCode1y = xini_file["键位配置"]["1键Y轴"];
	int keyCode2x = xini_file["键位配置"]["2键X轴"];
	int keyCode2y = xini_file["键位配置"]["2键Y轴"];

	int Feature30 = xini_file["系统配置"]["HOOK聊天消息"];
	int Feature40 = xini_file["颜色配置"]["启用"];
	// NPC名称颜色
	std::string NPC_Color = (const char*)xini_file["颜色配置"]["NPC名称颜色"];
	// 角色名称颜色
	std::string Character_Color = (const char*)xini_file["颜色配置"]["角色名称颜色"];

	if (Feature1 == 1) {
		// 开启[Ctrl+v]粘贴权限
		Gamex::SetClipboardData(exeType);
		LogMessage("开启[Ctrl+v]粘贴权限");
	}
	if (Feature2 == 1) {
		// 开启台服DNF邮件GM标识
		Gamex::FixGMofMail(exeType);
		LogMessage("开启台服DNF邮件GM标识");
	}
	if (Feature3 == 1) {
		// 关闭NPC重新回购
		Gamex::DisableBuyback(exeType);
		LogMessage("关闭NPC重新回购");
	}
	if (Feature4 == 1) {
		// 技能栏默认显示技能名称
		Gamex::ShowSkillName(exeType);
		LogMessage("技能栏默认显示技能名称");
	}
	if (Feature5 == 1) {
		// 修复233包头异常
		Gamex::FixPackage(exeType);
		LogMessage("修复233包头异常");
	}
	if (Feature6 == 1) {
		// 修复 "//移动物品" 命令至脚下
		Gamex::FixItemPosCMD(exeType);
		LogMessage("修复‘//移动物品’命令至脚下");
	}
	if (Feature7 == 1) {
		// 修复字母‘R’&‘I’
		Gamex::FixLetterText(exeType);
		LogMessage("修复字母‘R’&‘I’");
	}
	if (Feature8 == 1) {
		// 禁用启动游戏时最小化其他窗口 @光头大佬
		Gamex::DisableOtherWinMin(exeType);
		LogMessage("禁用启动游戏时最小化其他窗口");
	}
	if (Feature9 == 1) {
		// 缩放优化(取消[use zoom rate]标签镜头跟随) 感觉不明显
		Gamex::FreeZoomRate(exeType);
		LogMessage("缩放优化(取消[use zoom rate]标签镜头跟随)");
	}
	if (Feature10 == 1) {
		// 修复领主之塔 
		Gamex::FixLordTower(exeType);
		LogMessage("修复领主之塔通关返回城镇摆摊或分解机崩溃&结算音效多次播放BUG");
	}
	if (Feature11 == 1) {
		// 修复角色二觉职业名称乱码
		Gamex::FixCharacterName(exeType);
		LogMessage("修复角色二觉职业名称乱码");
	}
	if (Feature12 == 1) {
		// 默认创建缔造者0627 @蛐蛐
		Gamex::CreateCreatorMage(exeType);
		LogMessage("默认创建缔造者");
	}
	if (Feature13 == 1) {
		// 本地GM
		Gamex::LocalGM_Mode(exeType);
		LogMessage("开启本地GM");
	}
	if (Feature14 == 1) {
		// 装备+时装镶嵌
		if (exeType == "0627") {
			Mosaic_0627();
			LogMessage("真·装备时装镶嵌");
		}
	}
	if (Feature15 == 1) {
		// 14技能栏
		if (exeType == "0627") {
			SkilSlot_0627(keyCode1, keyCode2, keyCode1x, keyCode1y, keyCode2x, keyCode2y);
			LogMessage("真·14技能栏,同步修改PVF + Frida");
		}
	}

	// 设置NPC名称颜色
	if (!NPC_Color.empty() && Feature40 == 1) {
		Gamex::OverloadNPC_Color(exeType, NPC_Color);
		LogMessage("设置NPC名称颜色:%s", NPC_Color.c_str());
	}
	// 设置角色名称颜色
	if (!Character_Color.empty() && Feature40 == 1) {
		Gamex::OverloadCharacter_Color(exeType, Character_Color);
		LogMessage("设置角色名称颜色:%s", Character_Color.c_str());
	}
	// HOOK聊天消息
	if (Feature30 == 1) {
		Gamex::CommandHook(exeType);
	}
}

// 初始化
namespace Gamex {
	void DLL_Main() {
		// TODO 通过dnf.exe获取版本信息 & 配置文件获取
		loadConfig();
	}
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

	// 修复领主之塔 
	void FixLordTower(std::string exeType) {
		if (exeType == "0627") {
			// 修复领主之塔通关返回城镇摆摊或分解机崩溃（3.0优化版）
			WriteJmp((void*)0x00FFDA95, &fixNewBoundingRound);
			// 修复领主之塔结算音效多次播放BUG
			*(char*)0x00436382 = -1;
		}
	}

	// 修复角色二觉职业名称乱码
	void FixCharacterName(std::string exeType) {
		if (exeType == "0627") {
			*(BYTE*)0x0084995A = 0x8F;
		}
	}

	// 默认创建缔造者0627 @蛐蛐
	void CreateCreatorMage(std::string exeType) {
		if (exeType == "0627") {
			*(char*)0x10F3338 = 11;
			WriteJmp((void*)0x010F3341, &DefaultCharacter);
		}
	}

	// 本地GM
	void LocalGM_Mode(std::string exeType) {
		if (exeType == "0627") {
			// 原始 55 8B EC 51 81 C1 90 03 00 00   -> 03 00 00 改 02 08 09
			// memcpy((void*)0x00751830, "\x55\x8B\xEC\x51\x81\xC1\x90\x02\x08\x09", 10);
			RtlCopyMemory((LPVOID)0x00751830, "\x55\x8B\xEC\x51\x81\xC1\x90\x02\x08\x09", 10);
			// 原始 81 C1 90 03 00 00 8D 45 FC 50 8D 03  -> 03 00 00 改 02 08 09
			// memcpy((void*)0x00751834, "\x81\xC1\x90\x02\x08\x09\x8D\x45\xFC\x50\x8D", 11);
			RtlCopyMemory((LPVOID)0x00751834, "\x81\xC1\x90\x02\x08\x09\x8D\x45\xFC\x50\x8D", 11);
		}
	}

	// HOOK聊天消息(是否区分客户端版本?)
	void CommandHook(std::string exeType)
	{
		if (exeType == "0627") {
			// 95C103 - E8 0859FFFF - call DNF.exe+551A10
			/*BYTE hookedBytes[5] = { 0xE8,0x90,0x90,0x90,0x90 };
			*(DWORD*)(hookedBytes + 1) = (DWORD)sendCommand - (DWORD)0x95C103 - 5;
			WriteProcessMemory(INVALID_HANDLE_VALUE, (LPVOID)0x95C103, hookedBytes, 5, NULL);*/
			AttachHook(0x95C103, (DWORD)sendCommand);
		}
	}

	// 设置NPC名称颜色
	void OverloadNPC_Color(std::string exeType, std::string NPC_Color) {
		if (exeType == "0627") {
			// NPC名称颜色  默认颜色 E6 C8 9B FF
			// memcpy((void*)0x007E9279, "\x39\x96\x5b", 3);
			// BYTE cAddr[3] = { 0xF3, 0x4B, 0x7D };
			// dx.Writes(0x007E9279, static_cast<const void*>(cAddr), sizeof(cAddr));

			// 获取vector颜色BYTE
			std::vector<BYTE> vectorColors = VectorToBytes(NPC_Color);
			WriteVectorBytes((void*)0x007E9279, vectorColors);
		}
	}

	// 设置角色名称颜色[CE可HOOK颜色，推测需要角色登录后处理]
	void OverloadCharacter_Color(std::string exeType, std::string Character_Color) {
		if (exeType == "0627") {
			// 角色名称颜色  默认颜色 FF FF FF FF
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

