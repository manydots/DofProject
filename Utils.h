#pragma once
#include "dof.h"
#include <fcntl.h>
#include <io.h>
#include <intrin.h>

#include <cwctype>

inline  uint8_t hexToByte(const std::string& hex)
{
	return static_cast<uint8_t>(std::stoi(hex, nullptr, 16));
}

// ��ӡ��������
template <typename T>
inline void printTypeName(const T&)
{
	if (std::is_same<T, int>::value)
	{
		std::cout << "Type is int" << std::endl;
	}
	else if (std::is_same<T, double>::value)
	{
		std::cout << "Type is double" << std::endl;
	}
	else
	{
		std::cout << "Unknown type" << std::endl;
	}
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

// ��ȡ��ǰʱ��Ŀ��ַ���
inline static std::wstring getCurrentTimeW()
{
	std::time_t now = std::time(nullptr);
	std::tm localTime;
	// ʹ�� localtime_s ���� localtime ��ȷ���̰߳�ȫ
	errno_t err = localtime_s(&localTime, &now);
	if (err != 0) {
		// ����������򵥵��׳��쳣
		throw std::runtime_error("Failed to convert time to local time.");
	}

	std::wstringstream wss;
	// ��������������ȷ��ʱ���ʽ��ȷ
	wss.imbue(std::locale(""));
	wss << std::put_time(&localTime, L"%Y-%m-%d %H:%M:%S");
	return wss.str();
}

// �жϿ��ַ����Ƿ�Ϊ����
inline bool isNumberW(const std::wstring& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		wchar_t ch = str[i];
		// cwctype
		if (!std::iswdigit(ch))
		{
			return false;
		}
	}
	return true;
}

// �����ַ������˵Ŀո�
inline static std::wstring trim(const std::wstring& str)
{
	size_t first = str.find_first_not_of(L" ");
	size_t last = str.find_last_not_of(L" ");

	// ����ַ���ȫ�ǿո����Ϊ�գ��򷵻ؿ��ַ���
	if (first == std::wstring::npos || last == std::wstring::npos)
	{
		return L"";
	}

	// ����ȥ�����˿ո������ַ���
	return str.substr(first, last - first + 1);
}

// �ָ���ַ��� Ĭ���Կո�(L' ')�ָ�, L','
inline static std::vector<std::wstring> splitStrW(const std::wstring& input, wchar_t delimiter = L' ')
{
	std::vector<std::wstring> tokens;
	std::wstring::size_type start = 0;
	std::wstring::size_type end = input.find(delimiter);

	while (end != std::wstring::npos)
	{
		tokens.push_back(input.substr(start, end - start));
		start = end + 1;
		end = input.find(delimiter, start);
	}

	// ������һ��token��������ڣ�
	if (start < input.size())
	{
		tokens.push_back(input.substr(start));
	}

	return tokens;
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
inline void CreateConsole()
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

	// ����stdoutΪ���ַ�ģʽ
	//_setmode(_fileno(stdout), _O_WTEXT);
	// ����stderrΪ���ַ�ģʽ
	//_setmode(_fileno(stderr), _O_WTEXT);

	// �������
	printf("Console allocated successfully!\n");
}

inline void Cleanup() {
	// ִ������������������ӡ��رտ���̨��
	// ���磬�رտ���̨��
	FreeConsole();
}