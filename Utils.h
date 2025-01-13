#pragma once
#include "dof.h"
#include <fcntl.h>
#include <io.h>
#include <intrin.h>

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

// wchar_tתchar
//inline std::string WCharToChar(const wchar_t* wstr) {
//	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//	return converter.to_bytes(wstr);
//}

// ��������̨
inline void CreateConsle()
{
	HWND consoleWindowHandle = NULL;
	// ����һ���µĿ���̨
	if (AllocConsole()) {
		// ��ȡ�´����Ŀ���̨���ھ��
		consoleWindowHandle = GetConsoleWindow();
		if (consoleWindowHandle != NULL) {
			// ��ӡ����̨���ھ��
			printf("Console window handle: %p\n", consoleWindowHandle);
		}
		else {
			printf("Failed to get console window handle.\n");
		}
	}
	else {
		printf("Failed to create a console.\n");
	}
	// ���ÿ���̨����Ĵ���ҳΪ UTF-8 (65001)
	// ���ÿ���̨����Ĵ���ҳΪ GBK (CP936)
	// SetConsoleOutputCP(936);

	// ���°󶨱�׼���롢����ʹ�����
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);
	freopen_s(&stream, "CONIN$", "r", stdin);

	// ����׼��ģʽ����Ϊ������ģʽ
	int _s1 = _setmode(_fileno(stdout), _O_BINARY);
	int _s2 = _setmode(_fileno(stdin), _O_BINARY);
	int _s3 = _setmode(_fileno(stderr), _O_BINARY);

	// �������
	printf("Console allocated successfully!\n");
}

inline void Cleanup() {
	// ִ������������������ӡ��رտ���̨��
	// ���磬�رտ���̨��
	FreeConsole();
}