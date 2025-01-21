#pragma once
#include "dof.h"

inline void LogMessage(const char* format, ...) {
	printf("[Log][%s]", getCurrentTime().c_str());
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	printf("\n");
}

// 输出宽字符串日志信息
inline void LogMessageW(const wchar_t* buf, ...)
{
	wprintf(L"[Log][%ls]", getCurrentTimeW().c_str());

	setlocale(LC_ALL, "");
	wchar_t* nbuf = new wchar_t[1024];
	va_list va;
	va_start(va, buf);
	vswprintf(nbuf, 1024, buf, va);
	va_end(va);

	wprintf(L"%ls\n", nbuf);
}

inline void LogMessage(const std::string& message, int openLog) {
	if (openLog == 1) {
		std::ofstream log_file;
		log_file.open("DOF.log", std::ios_base::app); // 文件末尾添加

		// 检查文件是否成功打开
		if (!log_file.is_open()) {
			std::cerr << "无法打开日志文件" << std::endl;
			return;
		}

		// 获取当前时间
		std::string timestamp = getCurrentTime();

		// 写入时间戳和日志信息
		log_file << "[" << timestamp << "]" << message << std::endl;
		log_file.close();
	}
}

inline void LogMessage(const INT& message, int openLog) {
	if (openLog == 1) {
		std::ofstream log_file;
		log_file.open("DOF.log", std::ios_base::app); // 文件末尾添加

		// 检查文件是否成功打开
		if (!log_file.is_open()) {
			std::cerr << "无法打开日志文件" << std::endl;
			return;
		}

		// 获取当前时间
		std::string timestamp = getCurrentTime();

		// 写入时间戳和日志信息
		log_file << "[" << timestamp << "][Packet]" << message << std::endl;

		log_file.close();
	}
}

inline void LogMessage(const wchar_t* message, int openLog) {
	if (openLog == 1) {
		std::ofstream log_file;
		log_file.open("DOF.log", std::ios_base::app); // 文件末尾添加

		// 检查文件是否成功打开
		if (!log_file.is_open()) {
			std::cerr << "无法打开日志文件" << std::endl;
			return;
		}

		// 获取当前时间
		std::string timestamp = getCurrentTime();

		// 分配缓冲区来存储转换后的多字节字符串
		int len = WideCharToMultiByte(CP_ACP, 0, message, -1, NULL, 0, NULL, NULL);
		char* mbstr = new char[len + 1];
		mbstr[len] = '\0'; // 确保字符串以 null 结尾

		// 执行转换
		WideCharToMultiByte(CP_ACP, 0, message, -1, mbstr, len, NULL, NULL);

		// 写入时间戳和日志信息
		log_file << "[" << timestamp << "][Message]" << mbstr << std::endl;
		delete[] mbstr;
		log_file.close();
	}
}
