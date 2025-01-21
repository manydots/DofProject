#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include <ctime>  // 包含时间处理的头文件
#include <iomanip>  // 包含用于设置输出格式的头文件
#include <filesystem>

#include "Constants.h"
#include "xini_file.h"
#include "Memory.h"
#include "Utils.h"
#include "Logger.h"
#include "GameStruct.h"
#include "Gamex.h"

namespace fs = std::filesystem; // 配置C++17 项目-配置属性- C/C++ -语言-  C++语言标准