#pragma once
#include "dof.h"
#include <fstream>
#include <ctime>  // ����ʱ�䴦���ͷ�ļ�
#include <iomanip>  // �����������������ʽ��ͷ�ļ�
#include <filesystem>

namespace fs = std::filesystem; // ����C++17 ��Ŀ-��������- C/C++ -����-  C++���Ա�׼
void LogMessage(const std::string& message, int openLog);

// ��ȡexeִ�г���·��
static std::string GetProgramDir()
{
	char szDir[2048] = { 0 };
	::GetModuleFileNameA(NULL, szDir, sizeof(szDir));
	std::string strResult = szDir;
	strResult = strResult.substr(0, strResult.find_last_of("\\"));
	return strResult;
}
