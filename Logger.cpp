#include "dof.h"
#include "Logger.h"

// ��ȡ��ǰʱ����ַ���
static std::string getCurrentTime() {
	std::time_t now = std::time(nullptr);
	struct tm localTime;
	char buf[100];
	localtime_s(&localTime, &now); // ת��Ϊ����ʱ��
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &localTime);
	return std::string(buf);
}


void LogMessage(const std::string& message, int openLog) {
	if (openLog == 1) {
		std::ofstream log_file;
		log_file.open("DOF.log", std::ios_base::app); // �ļ�ĩβ���

		// ����ļ��Ƿ�ɹ���
		if (!log_file.is_open()) {
			std::cerr << "�޷�����־�ļ�" << std::endl;
			return;
		}

		// ��ȡ��ǰʱ��
		std::string timestamp = getCurrentTime();

		// д��ʱ�������־��Ϣ
		log_file << "[" << timestamp << "]" << message << std::endl;
	}
}