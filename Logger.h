#pragma once
#include "dof.h"

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

inline void LogMessage(const short& message, int openLog) {
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