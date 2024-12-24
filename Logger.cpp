#include "dof.h"
#include "Logger.h"

// 获取当前时间的字符串
static std::string getCurrentTime() {
	std::time_t now = std::time(nullptr);
	struct tm localTime;
	char buf[100];
	localtime_s(&localTime, &now); // 转换为本地时间
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &localTime);
	return std::string(buf);
}


void LogMessage(const std::string& message, int openLog) {
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
	}
}