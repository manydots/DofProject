/***************************************************************************************************
Module: Memory.h
Author: Kotori Baby @ 2016
***************************************************************************************************/


#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __MEMORY_H__
#define __MEMORY_H__


////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _WINDLL
static_assert(false, "DLL-Only");
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////


#include <Windows.h>

#include <initializer_list>
#include <algorithm>
// Windows Í·ÎÄ¼þ
#include <unordered_map>
#include <filesystem>
////////////////////////////////////////////////////////////////////////////////////////////////////

class Memory {

public:
	Memory() {}
	~Memory() {}

private:
	Memory(const Memory&);
	Memory& operator=(const Memory&);

public:
	template<typename Type>
	Type Read(uintptr_t address) const {

		auto real_address = reinterpret_cast<Type*>(address);

		Type result = {};

		DWORD old_protect = 0;
		::VirtualProtect(real_address, sizeof(Type), PAGE_EXECUTE_READWRITE, &old_protect);

		__try {
			result = *real_address;
		}
		__except (::GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
			::VirtualProtect(real_address, sizeof(Type), old_protect, &old_protect);
			return 0;
		}

		::VirtualProtect(real_address, sizeof(Type), old_protect, &old_protect);

		return result;
	}

	template<typename Type>
	void Write(uintptr_t address, Type value) const {

		auto real_address = reinterpret_cast<Type*>(address);

		DWORD old_protect = 0;
		::VirtualProtect(real_address, sizeof(Type), PAGE_EXECUTE_READWRITE, &old_protect);

		__try {
			*real_address = value;
		}
		__except (::GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
			::VirtualProtect(real_address, sizeof(Type), old_protect, &old_protect);
			return;
		}

		::VirtualProtect(real_address, sizeof(Type), old_protect, &old_protect);
	}

	template<typename Type>
	Type Read(std::initializer_list<uintptr_t> offsets) const {

		if (offsets.size() == 0) {
			return 0;
		}

		return Read<Type>(GetFinalAddress(offsets));
	}

	template<typename Type>
	void Write(std::initializer_list<uintptr_t> offsets, Type value) const {

		if (offsets.size() == 0) {
			return;
		}

		Write<Type>(GetFinalAddress(offsets), value);
	}

	bool Reads(uintptr_t address, void* buffer, size_t size) const {

		auto real_address = reinterpret_cast<void*>(address);

		DWORD old_protect = 0;
		::VirtualProtect(real_address, size, PAGE_EXECUTE_READWRITE, &old_protect);

		__try {
			::RtlCopyMemory(buffer, real_address, size);

		}
		__except (::GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
			::VirtualProtect(real_address, size, old_protect, &old_protect);
			return false;
		}

		::VirtualProtect(real_address, size, old_protect, &old_protect);

		return true;
	}

	bool Writes(uintptr_t address, const void* buffer, size_t size) const {

		auto real_address = reinterpret_cast<void*>(address);

		DWORD old_protect = 0;
		::VirtualProtect(real_address, size, PAGE_EXECUTE_READWRITE, &old_protect);

		__try {
			::RtlCopyMemory(real_address, buffer, size);

		}
		__except (::GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
			::VirtualProtect(real_address, size, old_protect, &old_protect);
			return false;
		}

		::VirtualProtect(real_address, size, old_protect, &old_protect);

		return true;
	}

	bool Reads(std::initializer_list<uintptr_t> offsets, void* buffer, size_t size) const {

		if (offsets.size() == 0) {
			return false;
		}

		return Reads(GetFinalAddress(offsets), buffer, size);
	}

	bool Writes(std::initializer_list<uintptr_t> offsets, const void* buffer, size_t size) const {

		if (offsets.size() == 0) {
			return false;
		}

		return Writes(GetFinalAddress(offsets), buffer, size);
	}

	uintptr_t GetFinalAddress(std::initializer_list<uintptr_t> offsets) const {

		uintptr_t base = 0;

		__try {
			std::for_each(offsets.begin(), offsets.end() - 1, [&base](const uintptr_t& offset) {
				auto address = reinterpret_cast<uintptr_t*>(base + offset);
				DWORD old_protect = 0;
				::VirtualProtect(address, sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &old_protect);
				base = *address;
				::VirtualProtect(address, sizeof(uintptr_t), old_protect, &old_protect);
				});

		}
		__except (::GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ?
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
			return 0;
		}

		return base + *(offsets.end() - 1);
	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////


#endif


//////////////////////////////////////////// End Of File ///////////////////////////////////////////
