#pragma once
#include "Game.h"


// ����ڴ��Ƿ�����ҿɶ�
BOOL IsMemoryReadable(void* address, size_t length)
{
	MEMORY_BASIC_INFORMATION memInfo;
	SIZE_T bytesReturned = VirtualQuery(address, &memInfo, sizeof(MEMORY_BASIC_INFORMATION));

	if (bytesReturned == sizeof(MEMORY_BASIC_INFORMATION))
	{
		// ����ڴ�״̬�Ƿ�Ϊ���ύ��MEM_COMMIT��
		if (memInfo.State == MEM_COMMIT)
		{
			// ����ڴ汣�������Ƿ�Ϊ�ɶ���������д��ֻ����// ִ���ҿɶ�  PAGE_EXECUTE_READ
			if ((memInfo.Protect & (PAGE_READWRITE | PAGE_READONLY)) != 0)
			{
				// ����ڴ�����Ĵ�С�Ƿ��㹻
				if (memInfo.RegionSize >= length)
				{
					return true; // �ڴ�����ҿɶ�
				}
			}
		}
	}

	return false; // �ڴ治���ڡ����ɶ����������Բ������ȡ�������С����
}


// ���ֽڼ� TCHAR�ַ���(ANSI/Unicode)  BYTE *buffer
BOOL ReadMemoryBytes(TCHAR* buffer, DWORD address, size_t length)
{
	if (IsMemoryReadable((void*)address, length))
	{
		// �ڴ�&�ɶ�
		memcpy(buffer, (void*)address, length);
		return true;
	}
	return false;
}

// ��ȡDWORD����
DWORD ReadDWORD(DWORD address)
{
	return *(DWORD*)(address);
}


// �����ֽ�wchar_t*ת��Ϊ���ֽ�char*    
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


// �����ֽ�char*ת��Ϊ���ֽ�wchar_t*    
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

// дָ���ֽڼ����ڴ� addressĿ�� ptr���� length����
void WriteBytes(void* address, void* ptr, size_t length)
{
	std::memcpy(address, ptr, length);
}

// дVector�ֽڼ����ڴ� addressĿ���ڴ��ַ  Vector�ֽڼ�����
void WriteVectorBytes(void* address, std::vector<BYTE> Vector_BYTE)
{
	const void* ptr = reinterpret_cast<const void*>(Vector_BYTE.data());
	std::memcpy(address, ptr, Vector_BYTE.size());
}

// �ַ���ת�ֽڼ�
std::vector<BYTE> stringToBytes(const std::string& str)
{
	std::vector<BYTE> byteVector;
	byteVector.reserve(str.size()); // Ԥ�����ڴ����������
	// ���ַ���ת��Ϊ�ֽڼ�
	// for (BYTE ch : str)
	// {
	//     byteVector.push_back(static_cast<BYTE>(ch));
	// }
	// ��ͨѭ��
	for (size_t i = 0; i < str.size(); i++)
	{
		byteVector.push_back(static_cast<BYTE>(str[i]));
	}
	return byteVector;
}

// ת����ɫ
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

// vector��ɫתbyte
std::vector<BYTE> VectorToBytes(const std::string& hex)
{
	std::vector<uint8_t> hexBytes = hexStringToByteArray(hex);
	// std::cout << "vector length: " << hexBytes.size() << std::endl;
	// BYTE addr[3] = {0};
	// for (size_t i = 0; i < 3; ++i)
	// {
	//     addr[i] = hexBytes[i];
	// }
	// hexBytes.begin() + hexBytes.size() or hexBytes.begin() + 3 ȡ3���ֽ�
	std::vector<BYTE> addr(hexBytes.begin(), hexBytes.end());
	return addr;
}


namespace GameCall {
	// �����ı�call   type 14���ȹ���  17ϵͳ���� 37���˹���
	void SendText(PCWCHAR str, INT rgb, INT type) {
		UINT ecx = readVal(readVal(SHOP_BASE) + 0x40);
		game_notice(ecx, 0, str, rgb, type, 0, 0, 0);
	}
	// ����
	void Shout(PCWCHAR str, INT type) {
		UINT ecx = readVal(SHOUT_BASE);
		game_shout(ecx, 0, str, 3, type, 0);
	}
}
