#pragma once

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ�ļ����ų�����ʹ�õ�����
// Windows ͷ�ļ�
#include <windows.h>
#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include <ctime>  // ����ʱ�䴦���ͷ�ļ�
#include <iomanip>  // �����������������ʽ��ͷ�ļ�
#include <filesystem>

#include "Constants.h"
#include "xini_file.h"
#include "Memory.h"
#include "Utils.h"
#include "Logger.h"
#include "GameStruct.h"
#include "Gamex.h"

namespace fs = std::filesystem; // ����C++17 ��Ŀ-��������- C/C++ -����-  C++���Ա�׼