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

// ������ַ�����־��Ϣ
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

inline void LogMessage(const INT& message, int openLog) {
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
