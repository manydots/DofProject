#pragma once
#include "dof.h"
#include <fcntl.h>
#include <io.h>
#include <intrin.h>

inline  uint8_t hexToByte(const std::string& hex)
{
	return static_cast<uint8_t>(std::stoi(hex, nullptr, 16));
}


// 获取exe执行程序路径
inline std::string GetProgramDir()
{
	char szDir[2048] = { 0 };
	::GetModuleFileNameA(NULL, szDir, sizeof(szDir));
	std::string strResult = szDir;
	strResult = strResult.substr(0, strResult.find_last_of("\\"));
	return strResult;
}


// 获取文件版本信息
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

// 获取当前时间的字符串
inline static std::string getCurrentTime() {
	std::time_t now = std::time(nullptr);
	struct tm localTime;
	char buf[100];
	localtime_s(&localTime, &now); // 转换为本地时间
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &localTime);
	return std::string(buf);
}

// 拼接宽字符两个
inline void formatAndConcat(wchar_t* buffer, size_t bufferSize, const wchar_t* str1, const wchar_t* str2) {
	// 为了简单起见，这里不检查缓冲区大小是否足够
	swprintf_s(buffer, bufferSize, L"%ls%ls", str1, str2);
}

// 拼接宽字符多个
inline void formatAndConcatSafe(wchar_t* buffer, size_t bufferSizeInBytes, const wchar_t* format, ...) {
	va_list args;
	va_start(args, format);
	if (bufferSizeInBytes < sizeof(wchar_t)) {
		// 处理错误情况，例如通过输出错误信息或设置错误码
		va_end(args);
		return;
	}
	int result = vswprintf_s(buffer, bufferSizeInBytes / sizeof(wchar_t), format, args); // 注意：这里我们除以 sizeof(wchar_t) 来得到字符数
	if (result == -1) {
		// 处理错误，例如设置错误码或输出错误信息
		// 注意：在实际应用中，你可能需要更复杂的错误处理逻辑
		wprintf(L"Error formatting string.\n");
	}
	else if (static_cast<size_t>(result) + 1 >= bufferSizeInBytes) {
		wprintf(L"Output may have been truncated due to insufficient buffer size.\n");
	}
	va_end(args);
}

// wchar_t转char
//inline std::string WCharToChar(const wchar_t* wstr) {
//	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//	return converter.to_bytes(wstr);
//}

// 创建控制台
inline void CreateConsle()
{
	HWND consoleWindowHandle = NULL;
	// 创建一个新的控制台
	if (AllocConsole()) {
		// 获取新创建的控制台窗口句柄
		consoleWindowHandle = GetConsoleWindow();
		if (consoleWindowHandle != NULL) {
			// 打印控制台窗口句柄
			printf("Console window handle: %p\n", consoleWindowHandle);
		}
		else {
			printf("Failed to get console window handle.\n");
		}
	}
	else {
		printf("Failed to create a console.\n");
	}
	// 设置控制台输出的代码页为 UTF-8 (65001)
	// 设置控制台输出的代码页为 GBK (CP936)
	// SetConsoleOutputCP(936);

	// 重新绑定标准输入、输出和错误流
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);
	freopen_s(&stream, "CONIN$", "r", stdin);

	// 将标准流模式设置为二进制模式
	int _s1 = _setmode(_fileno(stdout), _O_BINARY);
	int _s2 = _setmode(_fileno(stdin), _O_BINARY);
	int _s3 = _setmode(_fileno(stderr), _O_BINARY);

	// 测试输出
	printf("Console allocated successfully!\n");
}

inline void Cleanup() {
	// 执行清理操作，如解除钩子、关闭控制台等
	// 例如，关闭控制台：
	FreeConsole();
}