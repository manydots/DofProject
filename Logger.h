#pragma once
#include "dof.h"
#include <fstream>
#include <ctime>  // 包含时间处理的头文件
#include <iomanip>  // 包含用于设置输出格式的头文件
#include <filesystem>

namespace fs = std::filesystem; // 配置C++17 项目-配置属性- C/C++ -语言-  C++语言标准
void LogMessage(const std::string& message, int openLog);

// 获取exe执行程序路径
static std::string GetProgramDir()
{
	char szDir[2048] = { 0 };
	::GetModuleFileNameA(NULL, szDir, sizeof(szDir));
	std::string strResult = szDir;
	strResult = strResult.substr(0, strResult.find_last_of("\\"));
	return strResult;
}
