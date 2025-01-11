#pragma once
#include "Game.h"


// 检查内存是否存在且可读
BOOL IsMemoryReadable(void* address, size_t length)
{
	MEMORY_BASIC_INFORMATION memInfo;
	SIZE_T bytesReturned = VirtualQuery(address, &memInfo, sizeof(MEMORY_BASIC_INFORMATION));

	if (bytesReturned == sizeof(MEMORY_BASIC_INFORMATION))
	{
		// 检查内存状态是否为已提交（MEM_COMMIT）
		if (memInfo.State == MEM_COMMIT)
		{
			// 检查内存保护属性是否为可读（包括读写、只读）// 执行且可读  PAGE_EXECUTE_READ
			if ((memInfo.Protect & (PAGE_READWRITE | PAGE_READONLY)) != 0)
			{
				// 检查内存区域的大小是否足够
				if (memInfo.RegionSize >= length)
				{
					return true; // 内存存在且可读
				}
			}
		}
	}

	return false; // 内存不存在、不可读、保护属性不允许读取或区域大小不足
}


// 读字节集 TCHAR字符集(ANSI/Unicode)  BYTE *buffer
BOOL ReadMemoryBytes(TCHAR* buffer, DWORD address, size_t length)
{
	if (IsMemoryReadable((void*)address, length))
	{
		// 内存&可读
		memcpy(buffer, (void*)address, length);
		return true;
	}
	return false;
}

// 读取DWORD整数
DWORD ReadDWORD(DWORD address)
{
	return *(DWORD*)(address);
}


// 将宽字节wchar_t*转化为单字节char*    
char* UnicodeToAnsi(const wchar_t* szStr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;

}


// 将单字节char*转化为宽字节wchar_t*    
wchar_t* AnsiToUnicode(const char* szStr)
{
	int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0);
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen);
	return pResult;

}

// 写指针字节集到内存 address目标 ptr数据 length长度
void WriteBytes(void* address, void* ptr, size_t length)
{
	std::memcpy(address, ptr, length);
}

// 写Vector字节集到内存 address目标内存地址  Vector字节集数据
void WriteVectorBytes(void* address, std::vector<BYTE> Vector_BYTE)
{
	const void* ptr = reinterpret_cast<const void*>(Vector_BYTE.data());
	std::memcpy(address, ptr, Vector_BYTE.size());
}

// 字符串转字节集
std::vector<BYTE> stringToBytes(const std::string& str)
{
	std::vector<BYTE> byteVector;
	byteVector.reserve(str.size()); // 预分配内存以提高性能
	// 将字符串转换为字节集
	// for (BYTE ch : str)
	// {
	//     byteVector.push_back(static_cast<BYTE>(ch));
	// }
	// 普通循环
	for (size_t i = 0; i < str.size(); i++)
	{
		byteVector.push_back(static_cast<BYTE>(str[i]));
	}
	return byteVector;
}

// 转换颜色
std::vector<uint8_t> hexStringToByteArray(const std::string& hex)
{
	std::vector<uint8_t> byteArray;
	std::string hexHash = (hex.front() == '#') ? hex.substr(1) : hex;
	if (hexHash.length() != 6)
	{
		std::cerr << "Invalid color hex string." << std::endl;
	}
	else
	{

		byteArray.push_back(hexToByte(hexHash.substr(0, 2)));
		byteArray.push_back(hexToByte(hexHash.substr(2, 2)));
		byteArray.push_back(hexToByte(hexHash.substr(4, 2)));
	}
	return byteArray;
}

// vector颜色转byte
std::vector<BYTE> VectorToBytes(const std::string& hex)
{
	std::vector<uint8_t> hexBytes = hexStringToByteArray(hex);
	// std::cout << "vector length: " << hexBytes.size() << std::endl;
	// BYTE addr[3] = {0};
	// for (size_t i = 0; i < 3; ++i)
	// {
	//     addr[i] = hexBytes[i];
	// }
	// hexBytes.begin() + hexBytes.size() or hexBytes.begin() + 3 取3个字节
	std::vector<BYTE> addr(hexBytes.begin(), hexBytes.end());
	return addr;
}


namespace GameCall {
	// 发送文本call   type 14喇叭公告  17系统公告 37个人公告
	void SendText(PCWCHAR str, INT rgb, INT type) {
		UINT ecx = readVal(readVal(SHOP_BASE) + 0x40);
		game_notice(ecx, 0, str, rgb, type, 0, 0, 0);
	}
	// 喊话
	void Shout(PCWCHAR str, INT type) {
		UINT ecx = readVal(SHOUT_BASE);
		game_shout(ecx, 0, str, 3, type, 0);
	}
}
