#pragma once

template<typename T = UINT>
inline T readVal(UINT address)
{
	return *(T*)(address);
}

template <typename T = UINT>
inline void writeVal(UINT address, T value)
{
	*(T*)(address) = value;
}


inline  uint8_t hexToByte(const std::string& hex)
{
	return static_cast<uint8_t>(std::stoi(hex, nullptr, 16));
}

inline  std::vector<uint8_t> hexStringToByteArray(const std::string& hex)
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