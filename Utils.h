#pragma once
#include "dof.h"

inline  uint8_t hexToByte(const std::string& hex)
{
	return static_cast<uint8_t>(std::stoi(hex, nullptr, 16));
}


// ��ȡexeִ�г���·��
inline std::string GetProgramDir()
{
	char szDir[2048] = { 0 };
	::GetModuleFileNameA(NULL, szDir, sizeof(szDir));
	std::string strResult = szDir;
	strResult = strResult.substr(0, strResult.find_last_of("\\"));
	return strResult;
}


// ��ȡ�ļ��汾��Ϣ
inline std::string GetFileVersion(const std::string& filePath)
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

	// ȷ�����ص��� VS_FIXEDFILEINFO �ṹ�Ĵ�С
	if (uLen < sizeof(VS_FIXEDFILEINFO)) {
		std::cerr << "Invalid VS_FIXEDFILEINFO size." << std::endl;
		return "";
	}

	// ��ȡ�汾��
	WORD major = HIWORD(pFileInfo->dwFileVersionMS);
	WORD minor = LOWORD(pFileInfo->dwFileVersionMS);
	WORD revision = HIWORD(pFileInfo->dwFileVersionLS);
	WORD build = LOWORD(pFileInfo->dwFileVersionLS);

	return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(revision) + "." + std::to_string(build);
}

// ��ȡ�ͻ��˰汾����
inline std::string getExeType(const std::string& version) {
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

// ��ȡ��ǰʱ����ַ���
inline static std::string getCurrentTime() {
	std::time_t now = std::time(nullptr);
	struct tm localTime;
	char buf[100];
	localtime_s(&localTime, &now); // ת��Ϊ����ʱ��
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &localTime);
	return std::string(buf);
}

// ƴ�ӿ��ַ�����
inline void formatAndConcat(wchar_t* buffer, size_t bufferSize, const wchar_t* str1, const wchar_t* str2) {
	// Ϊ�˼���������ﲻ��黺������С�Ƿ��㹻
	swprintf_s(buffer, bufferSize, L"%ls%ls", str1, str2);
}

// ƴ�ӿ��ַ����
inline void formatAndConcatSafe(wchar_t* buffer, size_t bufferSizeInBytes, const wchar_t* format, ...) {
	va_list args;
	va_start(args, format);
	if (bufferSizeInBytes < sizeof(wchar_t)) {
		// ����������������ͨ�����������Ϣ�����ô�����
		va_end(args);
		return;
	}
	int result = vswprintf_s(buffer, bufferSizeInBytes / sizeof(wchar_t), format, args); // ע�⣺�������ǳ��� sizeof(wchar_t) ���õ��ַ���
	if (result == -1) {
		// ��������������ô���������������Ϣ
		// ע�⣺��ʵ��Ӧ���У��������Ҫ�����ӵĴ������߼�
		wprintf(L"Error formatting string.\n");
	}
	else if (static_cast<size_t>(result) + 1 >= bufferSizeInBytes) {
		wprintf(L"Output may have been truncated due to insufficient buffer size.\n");
	}
	va_end(args);
}