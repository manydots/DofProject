#pragma once
#include "Gamex.h"
#include "Memory.h"
#include "Hook.h"
#include "FastCall.h"

// 创建读写类
Memory dx;

// 初始化
void Gamex::DLL_Main(std::string exeType) {
	// 修复233包头异常
	FixPackage(exeType);
	// 关闭NPC重新回购
	DisableBuyback(exeType);
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
