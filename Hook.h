#pragma once
#define Naked __declspec(naked)

void WriteJmp(void* pfn, void* pCallback);
void WriteCall(void* pfn, void* pCallback);