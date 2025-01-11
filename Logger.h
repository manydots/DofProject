#pragma once
#include "dof.h"

inline void LogMessage(const std::string& message, int openLog) {
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
		log_file.close();
	}
}

inline void LogMessage(const short& message, int openLog) {
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
		log_file << "[" << timestamp << "][Packet]" << message << std::endl;

		log_file.close();
	}
}

inline void LogMessage(const wchar_t* message, int openLog) {
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

		// ���仺�������洢ת����Ķ��ֽ��ַ���
		int len = WideCharToMultiByte(CP_ACP, 0, message, -1, NULL, 0, NULL, NULL);
		char* mbstr = new char[len + 1];
		mbstr[len] = '\0'; // ȷ���ַ����� null ��β

		// ִ��ת��
		WideCharToMultiByte(CP_ACP, 0, message, -1, mbstr, len, NULL, NULL);

		// д��ʱ�������־��Ϣ
		log_file << "[" << timestamp << "][Message]" << mbstr << std::endl;
		delete[] mbstr;
		log_file.close();
	}
}