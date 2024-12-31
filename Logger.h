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


// 获取文件版本信息
static std::string GetFileVersion(const std::string& filePath)
{
	DWORD dwHandle = 0;
	DWORD dwSize = GetFileVersionInfoSizeA(filePath.c_str(), &dwHandle);
	if (dwSize == 0)
	{
		std::cerr << "GetFileVersionInfoSize failed with error: " << GetLastError() << std::endl;
		return "";
	}

	std::vector<BYTE> buffer(dwSize);
	if (!GetFileVersionInfoA(filePath.c_str(), dwHandle, dwSize, buffer.data()))
	{
		std::cerr << "GetFileVersionInfo failed with error: " << GetLastError() << std::endl;
		return "";
	}

	VS_FIXEDFILEINFO* pFileInfo = nullptr;
	UINT uLen = 0;
	if (!VerQueryValueA(buffer.data(), "\\", (LPVOID*)&pFileInfo, &uLen))
	{
		std::cerr << "VerQueryValue failed with error: " << GetLastError() << std::endl;
		return "";
	}

	// 确保返回的是 VS_FIXEDFILEINFO 结构的大小
	if (uLen < sizeof(VS_FIXEDFILEINFO)) {
		std::cerr << "Invalid VS_FIXEDFILEINFO size." << std::endl;
		return "";
	}

	// 获取版本号
	WORD major = HIWORD(pFileInfo->dwFileVersionMS);
	WORD minor = LOWORD(pFileInfo->dwFileVersionMS);
	WORD revision = HIWORD(pFileInfo->dwFileVersionLS);
	WORD build = LOWORD(pFileInfo->dwFileVersionLS);

	return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision) + "." + std::to_string(build);
}

// 获取客户端版本类型
static std::string getExeType(const std::string& version) {
	std::string exeType = "0627";
	if (version == "1.180.2.1") {
		exeType = "0627";
	}
	else if (version == "1.200.4.1") {
		exeType = "0725";
	}
	else if (version == "1.260.5.1") {
		exeType = "1031";
	}
	return exeType;
}