#pragma once
#include "dof.h"
#include "Hook.h"


INT INSER_DATA = (INT)malloc(1024);
INT INSER_TOP = (INT)malloc(1024);

int	_706410 = 0x006FC760;
int _75A8C0 = 0x00750CF0;
int _75A880 = 0x00750CB0;
int _75A8E0 = 0x00750D10;
int _E745B0 = 0x00E6B2B0;
int _7BBAD0 = 0x007B21B0;
int _788960 = 0x0077E2A0;
int _11BEBC0 = 0x011B4120;
int _119FEF0 = 0x01194FC0;
int _766160 = 0x0075BD70;
int _122B260 = 0x01220590;
int _E77470 = 0x00E6E070;
int	_895380 = 0x00807CF0;
int _FDEB50 = 0x00891EC0;
int _11A0DE0 = 0x01195EB0;
int _13C1817 = 0x013B6ACC;
int _97B8F0 = 0x00972220;
int _667D20 = 0x0065DE50;
int _41F4A0 = 0x0041F130;
int _110F7C0 = 0x0110F7C0;
int _B09680 = 0x00B09680;
int _40A000 = 0x0040A110;
int _15A2030 = 0x01594E28;
int _1A46390 = 0x01A367F0;
int _1AF4308 = 0x01AE4670;
int _F43310 = 0x00FD3440;
int _13D71D8 = 0x013CC488;
int _75A540 = 0x00750970;
int _1135B50 = 0x0112AF50;
int _13D6DA7 = 0x013CC057;
int _55FE50 = 0x0045F8B0;
int _7C4340 = 0x0110F7C0;
int _4039B0 = 0x007BCBD0;
int _7A0620 = 0x007965E0;
int _F4F710 = 0x00F44CE0;
int _F4E080 = 0x00F43650;
int _627_MECPY = 0x013CB380;

int _call_221B912 = 0x0221B912;
int _call_1127D60 = 0x01127D60;
int _call_2911D27 = 0x02911D27;
int _call_1127EC0 = 0x01127EC0;

Naked void _627_Call_F554E1() {
	_asm {
		push ebp
		mov ebp, esp
		sub esp, 0xC
		mov eax, dword ptr ds : [0x01A367F0]
		xor eax, ebp
		mov dword ptr ss : [ebp - 0x4] , eax
		push esi
		mov esi, ecx
		mov ecx, dword ptr ds : [esi + 0x180]
		mov eax, dword ptr ds : [ecx]
		mov edx, dword ptr ds : [eax + 0xF0]
		push edi
		mov edi, dword ptr ss : [ebp + 0x8]
		call edx
		test eax, eax
		je labnl1
		mov ecx, dword ptr ds : [esi + 0x180]
		mov eax, dword ptr ds : [ecx]
		mov edx, dword ptr ds : [eax + 0xE4]
		call edx
		cmp dword ptr ds : [eax] , 0x14
		jne labnl1
		push ebx
		mov ebx, dword ptr ds : [edi]
		push 0x0
		inc ebx
		lea eax, dword ptr ds : [ebx + 0x1]
		push 0xFFFFFFFF
		mov dword ptr ds : [edi] , eax
		mov ecx, dword ptr ds : [esi]
		push _1AF4308
		push 0xA459
		mov dword ptr ss : [ebp - 0xC] , ecx
		call _122B260
		mov edx, dword ptr ss : [ebp - 0xC]
		add esp, 0x4
		push eax
		mov eax, dword ptr ds : [edx + 0x80]
		push ebx
		mov ecx, esi
		call eax
		mov ecx, dword ptr ds : [esi + 0x180]
		mov edx, dword ptr ds : [ecx]
		mov eax, dword ptr ds : [edx + 0xE4]
		call eax
		movzx eax, word ptr ds : [eax + 0x20]
		mov dword ptr ss : [ebp - 0xC] , eax
		test al, 0x1
		je labnl2
		mov ebx, dword ptr ds : [edi]
		push 0x0
		lea ecx, dword ptr ds : [ebx + 0x1]
		push 0xFF3232FF
		mov dword ptr ds : [edi] , ecx
		mov edx, dword ptr ds : [esi]
		push _1AF4308
		push 0xA449
		mov dword ptr ss : [ebp - 0x8] , edx
		call _122B260
		add esp, 0x4
		push eax
		mov eax, dword ptr ss : [ebp - 0x8]
		mov edx, dword ptr ds : [eax + 0x80]
		push ebx
		mov ecx, esi
		call edx
		mov eax, dword ptr ss : [ebp - 0xC]
		labnl2 :
		test al, 0x2
		je labnl3
		mov ebx, dword ptr ds : [edi]
		push 0x0
		lea eax, dword ptr ds : [ebx + 0x1]
		push 0xFF00F2FF
		mov dword ptr ds : [edi] , eax
		mov ecx, dword ptr ds : [esi]
		push _1AF4308
		push 0xA44A
		mov dword ptr ss : [ebp - 0x8] , ecx
		call _122B260
		mov edx, dword ptr ss : [ebp - 0x8]
		add esp, 0x4
		push eax
		mov eax, dword ptr ds : [edx + 0x80]
		push ebx
		mov ecx, esi
		call eax
		mov eax, dword ptr ss : [ebp - 0xC]
		labnl3 :
		test al, 0x4
		je labnl4
		mov ebx, dword ptr ds : [edi]
		push 0x0
		lea ecx, dword ptr ds : [ebx + 0x1]
		push 0xFF4EFF41
		mov dword ptr ds : [edi] , ecx
		mov edx, dword ptr ds : [esi]
		push _1AF4308
		push 0xA44B
		mov dword ptr ss : [ebp - 0x8] , edx
		call _122B260
		add esp, 0x4
		push eax
		mov eax, dword ptr ss : [ebp - 0x8]
		mov edx, dword ptr ds : [eax + 0x80]
		push ebx
		mov ecx, esi
		call edx
		mov eax, dword ptr ss : [ebp - 0xC]
		labnl4 :
		test al, 0x8
		je labnl5
		mov ebx, dword ptr ds : [edi]
		push 0x0
		lea eax, dword ptr ds : [ebx + 0x1]
		push 0xFFFFB11B
		mov dword ptr ds : [edi] , eax
		mov ecx, dword ptr ds : [esi]
		push _1AF4308
		push 0xA44C
		mov dword ptr ss : [ebp - 0x8] , ecx
		call _122B260
		mov edx, dword ptr ss : [ebp - 0x8]
		add esp, 0x4
		push eax
		mov eax, dword ptr ds : [edx + 0x80]
		push ebx
		mov ecx, esi
		call eax
		mov eax, dword ptr ss : [ebp - 0xC]
		labnl5 :
		test al, 0x10
		je labnl6
		mov ebx, dword ptr ds : [edi]
		push 0x0
		lea ecx, dword ptr ds : [ebx + 0x1]
		push 0xFFFFF8AE
		mov dword ptr ds : [edi] , ecx
		mov edx, dword ptr ds : [esi]
		push _1AF4308
		push 0xA44D
		mov dword ptr ss : [ebp - 0x8] , edx
		call _122B260
		add esp, 0x4
		push eax
		mov eax, dword ptr ss : [ebp - 0x8]
		mov edx, dword ptr ds : [eax + 0x80]
		push ebx
		mov ecx, esi
		call edx
		mov eax, dword ptr ss : [ebp - 0xC]
		labnl6 :
		test eax, 0xFFEF
		je labnl7
		mov ebx, dword ptr ds : [edi]
		push 0x0
		push 0xFFFF6BB3
		lea eax, dword ptr ds : [ebx + 0x1]
		push _1AF4308
		mov dword ptr ds : [edi] , eax
		mov edi, dword ptr ds : [esi]
		push 0x8CFC
		call _122B260
		mov edx, dword ptr ds : [edi + 0x80]
		add esp, 0x4
		push eax
		push ebx
		mov ecx, esi
		call edx
		labnl7 :
		pop ebx
			labnl1 :
		mov ecx, dword ptr ss : [ebp - 0x4]
			pop edi
			xor ecx, ebp
			pop esi
			call _13D71D8
			mov esp, ebp
			pop ebp
			ret 0x4

	}
}

Naked void _627_F45F50() {
	_asm {
		push ebp
		mov ebp, esp
		push esi
		mov esi, dword ptr ss : [ebp + 0x8]
		push edi
		lea eax, dword ptr ss : [ebp + 0x8]
		push eax
		lea edi, dword ptr ds : [esi + 0x8]
		push edi
		mov ecx, esi
		call _11A0DE0
		cmp dword ptr ss : [ebp + 0x8] , 0xFFEF
		jne labnl1
		lea ecx, dword ptr ds : [esi + 0xC]
		lea edx, dword ptr ss : [ebp + 0x8]
		push edx
		lea eax, dword ptr ds : [ecx + 0x8]
		push eax
		call _11A0DE0
		mov ecx, dword ptr ss : [ebp + 0x8]
		push ecx
		mov ecx, dword ptr ds : [0x01A5FA8C]
		call _1135B50
		test eax, eax
		je labnl1
		cmp dword ptr ds : [eax + 0x628] , 0x0
		je labnl1
		movzx eax, word ptr ds : [eax + 0x4A0]
		test al, 0x1
		je labnl2
		labnl9 :
		pop edi
			mov eax, 0xFF3232FF
			pop esi
			pop ebp
			ret 0x4
			labnl2 :
			test al, 0x2
			je labnl3
			labnl10 :
		pop edi
			mov eax, 0xFF00F2FF
			pop esi
			pop ebp
			ret 0x4
			labnl3 :
			test al, 0x4
			jne labnl4
			test al, 0x8
			je labnl5
			labnl8 :
		pop edi
			mov eax, 0xFFFFB11B
			pop esi
			pop ebp
			ret 0x4
			labnl5 :
			test al, 0x10
			jne labnl12
			labnl1 :
		lea edx, dword ptr ss : [ebp + 0x8]
			push edx
			push edi
			mov ecx, esi
			call _11A0DE0
			mov eax, dword ptr ss : [ebp + 0x8]
			cmp eax, 0x8
			jg labnl7
			je labnl8
			dec eax
			je labnl9
			dec eax
			je labnl10
			sub eax, 0x2
			jne labnl11
			labnl4 :
		pop edi
			mov eax, 0xFF4EFF41
			pop esi
			pop ebp
			ret 0x4
			labnl7 :
			cmp eax, 0x10
			je labnl12
			cmp eax, 0xFFEF
			je labnl13
			labnl11 :
		pop edi
			xor eax, eax
			pop esi
			pop ebp
			ret 0x4
			labnl13 :
			pop edi
			mov eax, 0xFFFF6BB3
			pop esi
			pop ebp
			ret 0x4
			labnl12 :
			pop edi
			mov eax, 0xFFFFF8AE
			pop esi
			pop ebp
			ret 0x4



	}
}

Naked void _627_F43310() {
	_asm {
		push ebp
		mov ebp, esp
		mov eax, dword ptr ss : [ebp + 0x8]
		cmp eax, 0x8
		jg labnl1
		je labnl2
		dec eax
		je labnl3
		dec eax
		je labnl4
		sub eax, 0x2
		jne labnl7
		mov eax, 0xFF4EFF41
		pop ebp
		ret
		labnl4 :
		mov eax, 0xFF00F2FF
			pop ebp
			ret
			labnl3 :
		mov eax, 0xFF3232FF
			pop ebp
			ret
			labnl2 :
		mov eax, 0xFFFFB11B
			pop ebp
			ret
			labnl1 :
		cmp eax, 0x10
			je labnl5
			cmp eax, 0xFFEF
			je labnl6
			labnl7 :
		xor eax, eax
			pop ebp
			ret
			labnl6 :
		mov eax, 0xFFFF6BB3
			pop ebp
			ret
			labnl5 :
		mov eax, 0xFFFFF8AE
			pop ebp
			ret

	}
}

Naked void _627_807CF0() {
	_asm {
		push ebp
		mov ebp, esp
		sub esp, 0x28
		push esi
		lea eax, dword ptr ss : [ebp - 0x10]
		push eax
		mov esi, ecx
		call _110F7C0
		sub esp, 0xC
		mov ecx, esp
		mov dword ptr ds : [ecx] , 0x0
		mov dword ptr ds : [ecx + 0x4] , 0x0
		mov edx, dword ptr ds : [eax]
		mov dword ptr ss : [ebp - 0x4] , esp
		test edx, edx
		je _807D27
		mov edx, dword ptr ds : [edx]
		test edx, edx
		je _807D27
		mov edx, dword ptr ds : [edx]
		mov dword ptr ds : [ecx] , edx
		_807D27 :
		mov eax, dword ptr ds : [eax + 0x8]
			mov dword ptr ds : [ecx + 0x8] , eax
			lea ecx, dword ptr ss : [ebp - 0x1C]
			push ecx
			mov ecx, esi
			call _B09680
			sub esp, 0xC
			mov ecx, esp
			mov dword ptr ds : [ecx] , 0x0
			mov dword ptr ds : [ecx + 0x4] , 0x0
			mov edx, dword ptr ds : [eax]
			mov dword ptr ss : [ebp - 0x4] , esp
			test edx, edx
			je _807D5D
			mov edx, dword ptr ds : [edx]
			test edx, edx
			je _807D5D
			mov edx, dword ptr ds : [edx]
			mov dword ptr ds : [ecx] , edx
			_807D5D :
		mov eax, dword ptr ds : [eax + 0x8]
			mov dword ptr ds : [ecx + 0x8] , eax
			lea ecx, dword ptr ss : [ebp - 0x28]
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			pop esi
			mov esp, ebp
			pop ebp
			ret
	}
}

Naked void _627_FDEDD0() {
	_asm {
		push ebp
		mov ebp, esp
		push 0xFFFFFFFF
		push 0x0142F0EB
		mov eax, dword ptr fs : [0]
		push eax
		sub esp, 0xC0
		push ebx
		push esi
		push edi
		mov eax, dword ptr ds : [0x01A367F0]//背包基址
		xor eax, ebp
		push eax
		lea eax, dword ptr ss : [ebp - 0xC]
		mov dword ptr fs : [0] , eax
		mov ecx, 0x01AE6EB0
		call _627_807CF0
		mov ecx, dword ptr ds : [0x01AE6EA4]
		mov eax, dword ptr ds : [ecx]
		mov edx, dword ptr ds : [eax + 0x12C]
		call edx
		push eax
		mov ecx, 0x01AE6EB0
		call _FDEB50
		mov esi, 0x01AE6E7C
		labnl2 :
		mov ecx, dword ptr ds : [esi]
		test ecx, ecx
		je labnl1
		mov eax, dword ptr ds : [ecx]
		mov edx, dword ptr ds : [eax + 0x8]
		push 0x1
		call edx
		labnl1 :
		mov dword ptr ds : [esi] , 0x0
			add esi, 0x4
			cmp esi, 0x01AE6E90
			jl labnl2//_FDEE25
			mov ecx, dword ptr ds : [0x01AE6EB8]
			mov ebx, dword ptr ds : [0x01AE6EB4]
			sub ecx, ebx
			mov eax, 0x38E38E39
			imul ecx
			sar edx, 0x3
			mov eax, edx
			shr eax, 0x1F
			xor esi, esi
			add eax, edx
			je labnl3
			xor edi, edi
			cmp eax, esi
			jbe labnl4
			labnl6 :
		lea ecx, dword ptr ds : [edi + ebx + 0xC]
			lea eax, dword ptr ss : [ebp - 0x14]
			push eax
			lea edx, dword ptr ds : [ecx + 0x8]
			push edx
			call _11A0DE0
			cmp dword ptr ss : [ebp - 0x14] , 0x0
			jle labnl5
			lea ecx, dword ptr ss : [ebp - 0xCC]
			call _667D20
			mov ebx, eax
			mov ecx, dword ptr ds : [0x01AE6EB8]
			sub ecx, dword ptr ds : [0x01AE6EB4]
			mov eax, 0x38E38E39
			imul ecx
			sar edx, 0x3
			mov eax, edx
			shr eax, 0x1F
			add eax, edx
			mov dword ptr ss : [ebp - 0x4] , 0x0
			cmp eax, esi
			jbe labnl3
			mov ecx, dword ptr ds : [0x01AE6EB4]
			lea ecx, dword ptr ds : [edi + ecx + 0xC]
			lea edx, dword ptr ss : [ebp - 0x10]
			push edx
			lea eax, dword ptr ds : [ecx + 0x8]
			push eax
			call _11A0DE0
			mov ecx, dword ptr ss : [ebp - 0x10]
			push 0x1
			push ebx
			push ecx
			call _97B8F0
			add esp, 0xC
			lea ecx, dword ptr ss : [ebp - 0xCC]
			mov dword ptr ds : [esi * 4 + 0x01AE6E7C] , eax
			mov dword ptr ss : [ebp - 0x4] , 0xFFFFFFFF
			call _41F4A0
			labnl5 :
		mov ecx, dword ptr ds : [0x01AE6EB8]
			mov ebx, dword ptr ds : [0x01AE6EB4]
			sub ecx, ebx
			mov eax, 0x38E38E39
			imul ecx
			sar edx, 0x3
			mov eax, edx
			shr eax, 0x1F
			inc esi
			add eax, edx
			add edi, 0x24
			cmp eax, esi
			ja labnl6
			labnl3 :
		mov ecx, dword ptr ss : [ebp - 0xC]
			mov dword ptr fs : [0] , ecx
			pop ecx
			pop edi
			pop esi
			pop ebx
			mov esp, ebp
			pop ebp
			ret
			labnl4 :
		push 0x01556288
			call _13C1817
	}
}

Naked void _627_55FE50() {
	_asm {
		push ebp
		mov ebp, esp
		mov edx, dword ptr ds : [ecx + 0x8]
		mov eax, dword ptr ss : [ebp + 0x8]
		mov edx, dword ptr ds : [edx]
		mov ecx, dword ptr ds : [ecx]
		mov dword ptr ds : [eax + 0x4] , 0x0
		mov dword ptr ds : [eax + 0x8] , edx
		mov dword ptr ds : [eax] , ecx
		pop ebp
		ret 0x4

	}
}

Naked void _627_F46030() {
	_asm {
		push ebp
		mov ebp, esp
		sub esp, 0x808
		mov eax, dword ptr ds : [0x01A367F0]
		xor eax, ebp
		mov dword ptr ss : [ebp - 0x4] , eax
		push ebx
		mov ebx, dword ptr ss : [ebp + 0x8]
		push esi
		push edi
		mov edi, dword ptr ss : [ebp + 0xC]
		mov esi, ecx
		lea eax, dword ptr ss : [ebp - 0x808]
		push eax
		lea ecx, dword ptr ds : [ebx + 0x8]
		push ecx
		mov ecx, ebx
		call _11A0DE0
		mov eax, dword ptr ss : [ebp + 0x10]
		sub eax, 0x0
		je lanbl1
		dec eax
		jne lanbl18
		mov eax, dword ptr ss : [ebp - 0x808]
		cmp eax, 0x8
		jg lanbl3
		je lanbl4
		dec eax
		je lanbl5
		dec eax
		je lanbl6
		sub eax, 0x2
		jne lanbl18
		push 0xA44B
		call _122B260
		add esp, 0x4
		push eax
		push _15A2030
		call _119FEF0
		add esp, 0x4
		push eax
		lea edx, dword ptr ss : [ebp - 0x804]
		push 0x800
		push edx
		call _40A000
		mov ecx, dword ptr ds : [edi]
		add esp, 0x10
		lea eax, dword ptr ds : [ecx + 0x1]
		push 0x0
		mov dword ptr ds : [edi] , eax
		push 0x4
		lanbl8 :
		mov edx, dword ptr ds : [esi]
		call _627_F43310
		mov edx, dword ptr ds : [edx + 0x80]
		add esp, 0x4
		push eax
		push _1AF4308
		lea eax, dword ptr ss : [ebp - 0x804]
		push eax
		push ecx
		jmp lanbl7
		lanbl6 :
		push 0xA44A
			call _122B260
			add esp, 0x4
			push eax
			push _15A2030
			call _119FEF0
			add esp, 0x4
			push eax
			lea eax, dword ptr ss : [ebp - 0x804]
			push 0x800
			push eax
			call _40A000
			mov ecx, dword ptr ds : [edi]
			add esp, 0x10
			lea edx, dword ptr ds : [ecx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , edx
			push 0x2
			jmp lanbl8
			lanbl5 :
		push 0xA449
			call _122B260
			add esp, 0x4
			push eax
			push _15A2030
			call _119FEF0
			add esp, 0x4
			push eax
			lea eax, dword ptr ss : [ebp - 0x804]
			push 0x800
			push eax
			call _40A000
			mov ecx, dword ptr ds : [edi]
			add esp, 0x10
			lea edx, dword ptr ds : [ecx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , edx
			push 0x1
			jmp lanbl8
			lanbl4 :
		push 0xA44C
			call _122B260
			add esp, 0x4
			push eax
			push _15A2030
			call _119FEF0
			add esp, 0x4
			push eax
			lea eax, dword ptr ss : [ebp - 0x804]
			push 0x800
			push eax
			call _40A000
			mov ecx, dword ptr ds : [edi]
			add esp, 0x10
			lea edx, dword ptr ds : [ecx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , edx
			push 0x8
			jmp lanbl8
			lanbl3 :
		cmp eax, 0x10
			je lanbl9
			cmp eax, 0xFFEF
			jne lanbl18
			push 0x8CFC
			call _122B260
			add esp, 0x4
			push eax
			push _15A2030
			call _119FEF0
			add esp, 0x4
			push eax
			lea eax, dword ptr ss : [ebp - 0x804]
			push 0x800
			push eax
			call _40A000
			mov eax, dword ptr ds : [edi]
			add esp, 0x10
			mov dword ptr ss : [ebp - 0x808] , eax
			inc eax
			push 0x0
			mov dword ptr ds : [edi] , eax
			mov edi, dword ptr ds : [esi]
			push ebx
			mov ecx, esi
			call _627_F45F50//_627_F43310//_F45F50
			mov edx, dword ptr ss : [ebp - 0x808]
			push eax
			mov eax, dword ptr ds : [edi + 0x80]
			push _1AF4308
			lea ecx, dword ptr ss : [ebp - 0x804]
			push ecx
			push edx
			mov ecx, esi
			call eax
			pop edi
			pop esi
			pop ebx
			mov ecx, dword ptr ss : [ebp - 0x4]
			xor ecx, ebp
			call _13D71D8
			mov esp, ebp
			pop ebp
			ret 0xC
			lanbl9 :
			push 0xA44D
			call _122B260
			add esp, 0x4
			push eax
			push _15A2030
			call _119FEF0
			add esp, 0x4
			push eax
			lea ecx, dword ptr ss : [ebp - 0x804]
			push 0x800
			push ecx
			call _40A000
			mov ecx, dword ptr ds : [edi]
			add esp, 0x10
			lea edx, dword ptr ds : [ecx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , edx
			push 0x10
			jmp lanbl8
			lanbl1 :
		mov eax, dword ptr ss : [ebp - 0x808]
			cmp eax, 0x8
			jg lanbl11
			je lanbl12
			dec eax
			je lanbl13
			dec eax
			je lanbl14
			sub eax, 0x2
			jne lanbl18
			mov ebx, dword ptr ds : [edi]
			lea eax, dword ptr ds : [ebx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , eax
			mov edi, dword ptr ds : [esi]
			push 0x4
			call _627_F43310
			add esp, 0x4
			push eax
			push _1AF4308
			push 0xA44B
			jmp lanbl16
			lanbl14 :
		mov ebx, dword ptr ds : [edi]
			lea eax, dword ptr ds : [ebx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , eax
			mov edi, dword ptr ds : [esi]
			push 0x2
			call _627_F43310
			add esp, 0x4
			push eax
			push _1AF4308
			push 0xA44A
			jmp lanbl16
			lanbl13 :
		mov ebx, dword ptr ds : [edi]
			lea eax, dword ptr ds : [ebx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , eax
			mov edi, dword ptr ds : [esi]
			push 0x1
			call _627_F43310
			add esp, 0x4
			push eax
			push _1AF4308
			push 0xA449
			jmp lanbl16
			lanbl12 :
		mov ebx, dword ptr ds : [edi]
			lea eax, dword ptr ds : [ebx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , eax
			mov edi, dword ptr ds : [esi]
			push 0x8
			call _627_F43310
			add esp, 0x4
			push eax
			push _1AF4308
			push 0xA44C
			jmp lanbl16
			lanbl11 :
		cmp eax, 0x10
			je lanbl17
			cmp eax, 0xFFEF
			jne lanbl18
			mov ebx, dword ptr ds : [edi]
			lea eax, dword ptr ds : [ebx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , eax
			mov edi, dword ptr ds : [esi]
			push 0xFFEF
			call _627_F43310
			add esp, 0x4
			push eax
			push _1AF4308
			push 0x8CFC
			jmp lanbl16
			lanbl17 :
		mov ebx, dword ptr ds : [edi]
			lea eax, dword ptr ds : [ebx + 0x1]
			push 0x0
			mov dword ptr ds : [edi] , eax
			mov edi, dword ptr ds : [esi]
			push 0x10
			call _627_F43310
			add esp, 0x4
			push eax
			push _1AF4308
			push 0xA44D
			lanbl16:
		call _122B260
			mov edx, dword ptr ds : [edi + 0x80]
			add esp, 0x4
			push eax
			push ebx
			lanbl7 :
		mov ecx, esi
			call edx
			lanbl18 :
		mov ecx, dword ptr ss : [ebp - 0x4]
			pop edi
			pop esi
			xor ecx, ebp
			pop ebx
			call _13D71D8
			mov esp, ebp
			pop ebp
			ret 0xC


	}
}

Naked void _627_F5A370() {
	_asm {
		push ebp
		mov ebp, esp
		sub esp, 0x30
		push edi
		mov edi, ecx
		mov ecx, dword ptr ds : [edi + 0x17C]
		test ecx, ecx
		je labnl1
		mov eax, dword ptr ds : [ecx]
		mov edx, dword ptr ds : [eax + 0x12C]
		call edx
		mov ecx, eax
		mov edx, dword ptr ds : [ecx + 0x8]
		sub edx, dword ptr ds : [ecx + 0x4]
		mov eax, 0x38E38E39
		imul edx
		sar edx, 0x3
		mov eax, edx
		shr eax, 0x1F
		add eax, edx
		mov dword ptr ss : [ebp - 0xC] , ecx
		je labnl1
		push ebx
		push esi
		mov esi, dword ptr ss : [ebp + 0x8]
		inc dword ptr ds : [esi]
		mov edx, dword ptr ds : [esi]
		mov ebx, dword ptr ds : [ecx + 0x4]
		mov dword ptr ss : [ebp - 0x8] , edx
		mov edx, dword ptr ds : [ecx + 0x8]
		sub edx, ebx
		mov eax, 0x38E38E39
		imul edx
		sar edx, 0x3
		mov eax, edx
		shr eax, 0x1F
		add eax, edx
		mov dword ptr ss : [ebp + 0x8] , 0x0
		je labnl2
		mov dword ptr ss : [ebp - 0x4] , 0x0
		cmp dword ptr ss : [ebp + 0x8] , eax
		jae labnl3
		labnl9 :
		mov eax, dword ptr ss : [ebp - 0x4]
			push 0x1
			push esi
			add eax, ebx
			push eax
			mov ecx, edi
			call _627_F46030
			call _706410
			mov ecx, eax
			call _75A540
			test al, al
			je labnl41
			push 0x0
			push 0xFF3232FF
			push 0x1AE46A8
			push 0x4B6A
			labnl5:
		mov eax, dword ptr ds : [esi]
			mov dword ptr ss : [ebp - 0x8] , eax
			inc eax
			mov dword ptr ds : [esi] , eax
			mov ebx, dword ptr ds : [edi]
			call _122B260
			mov ecx, dword ptr ss : [ebp - 0x8]
			mov edx, dword ptr ds : [ebx + 0x80]
			add esp, 0x4
			push eax
			push ecx
			mov ecx, edi
			call edx
			jmp labnl6
			labnl41 :
		mov ebx, dword ptr ss : [ebp - 0xC]
			mov ecx, dword ptr ds : [ebx + 0x8]
			sub ecx, dword ptr ds : [ebx + 0x4]
			mov eax, 0x38E38E39
			imul ecx
			sar edx, 0x3
			mov eax, edx
			shr eax, 0x1F
			add eax, edx
			cmp dword ptr ss : [ebp + 0x8] , eax
			jae labnl3
			mov eax, dword ptr ds : [ebx + 0x4]
			mov ecx, dword ptr ss : [ebp - 0x4]
			lea ecx, dword ptr ds : [ecx + eax + 0xC]
			lea edx, dword ptr ss : [ebp - 0x10]
			push edx
			lea eax, dword ptr ds : [ecx + 0x8]
			push eax
			call _11A0DE0
			cmp dword ptr ss : [ebp - 0x10] , 0x0
			jne labnl4
			push 0x0
			push 0xFF8C8C8C
			push _1AF4308
			push 0xA447
			jmp labnl5
			labnl4 :
		mov ecx, dword ptr ds : [ebx + 0x8]
			sub ecx, dword ptr ds : [ebx + 0x4]
			mov eax, 0x38E38E39
			imul ecx
			sar edx, 0x3
			mov eax, edx
			shr eax, 0x1F
			add eax, edx
			cmp dword ptr ss : [ebp + 0x8] , eax
			jae labnl3
			mov edx, dword ptr ds : [ebx + 0x4]
			mov ecx, dword ptr ss : [ebp - 0x4]
			lea ecx, dword ptr ds : [ecx + edx + 0xC]
			lea eax, dword ptr ss : [ebp - 0x14]
			push eax
			lea edx, dword ptr ds : [ecx + 0x8]
			push edx
			call _11A0DE0
			mov eax, dword ptr ss : [ebp - 0x14]
			mov ecx, dword ptr ds : [0x01A5FA8C]
			push eax
			call _1135B50
			mov ebx, eax
			mov dword ptr ss : [ebp - 0x8] , ebx
			test ebx, ebx
			je labnl6
			cmp dword ptr ds : [ebx + 0x624] , 0x0
			je labnl6
			dec dword ptr ds : [esi]
			lea edx, dword ptr ss : [ebp - 0x24]
			lea ecx, dword ptr ds : [ebx + 0x618]
			push edx
			call _627_55FE50
			labnl8 :
		lea eax, dword ptr ss : [ebp - 0x30]
			push eax
			lea ecx, dword ptr ds : [ebx + 0x618]
			call _7C4340
			mov ebx, dword ptr ss : [ebp - 0x24]
			test ebx, ebx
			je labnl3
			mov edx, dword ptr ds : [ebx]
			test edx, edx
			je labnl3
			mov ecx, dword ptr ds : [eax]
			test ecx, ecx
			je labnl11
			mov ecx, dword ptr ds : [ecx]
			labnl11 :
			cmp edx, ecx
			jne labnl3
			mov ecx, dword ptr ss : [ebp - 0x1C]
			cmp ecx, dword ptr ds : [eax + 0x8]
			je labnl6
			mov eax, edx
			test eax, eax
			je labnl3
			test ecx, ecx
			je labnl3
			cmp ecx, dword ptr ds : [eax + 0x8]
			je labnl3
			mov ebx, dword ptr ds : [ecx + 0x10]
			test ebx, ebx
			jne labnl7
			test eax, eax
			je labnl3
			cmp byte ptr ds : [ecx + 0x15] , bl
			jne labnl3
			lea ecx, dword ptr ss : [ebp - 0x24]
			call _4039B0
			mov ebx, dword ptr ss : [ebp - 0x8]
			jmp labnl8
			labnl7 :
		mov ecx, dword ptr ss : [ebp - 0x8]
			movzx edx, word ptr ds : [ecx + 0x4A0]
			mov ecx, dword ptr ds : [edi + 0x17C]
			push edx
			push ebx
			call _7A0620
			movzx ecx, byte ptr ds : [edi + 0x1E0]
			mov eax, dword ptr ds : [edi + 0x22C]
			push 0x1
			push 0x0
			push ecx
			push 0x0
			push 0x1A
			push 0x0
			push esi
			push 0xFFFFFFFF
			push ebx
			push edi
			mov dword ptr ss : [ebp - 0x18] , eax
			mov dword ptr ds : [edi + 0x22C] , 0x1
			call _F4F710
			mov edx, dword ptr ss : [ebp - 0x18]
			add esp, 0x28
			mov dword ptr ds : [edi + 0x22C] , edx
			call _706410
			mov ecx, eax
			call _75A880
			test al, al
			jne labnl6
			call _706410
			mov ecx, eax
			call _75A8E0
			test al, al
			jne labnl6
			mov eax, dword ptr ss : [ebp - 0x8]
			push 0xFFEDD568
			push 0x1
			push esi
			add eax, 0xD0
			push eax
			mov ecx, edi
			call _F4E080
			labnl6 :
		inc dword ptr ds : [esi]
			mov edx, dword ptr ss : [ebp - 0xC]
			mov ecx, dword ptr ds : [esi]
			mov ebx, dword ptr ds : [edx + 0x4]
			inc dword ptr ss : [ebp + 0x8]
			add dword ptr ss : [ebp - 0x4] , 0x24
			mov eax, edx
			mov dword ptr ss : [ebp - 0x8] , ecx
			mov ecx, dword ptr ds : [eax + 0x8]
			sub ecx, ebx
			mov eax, 0x38E38E39
			imul ecx
			sar edx, 0x3
			mov eax, edx
			shr eax, 0x1F
			add eax, edx
			cmp dword ptr ss : [ebp + 0x8] , eax
			jb labnl9
			labnl2 :
		cmp dword ptr ds : [0x01AE45AC] , 0x2
			jne labnl10
			mov ecx, dword ptr ss : [ebp - 0x8]
			push 0x0
			push 0xFF00F0FF
			inc ecx
			push _1AF4308
			mov dword ptr ds : [esi] , ecx
			mov ebx, dword ptr ds : [edi]
			push 0xA45E
			call _122B260
			mov edx, dword ptr ss : [ebp - 0x8]
			add esp, 0x4
			push eax
			mov eax, dword ptr ds : [ebx + 0x80]
			push edx
			mov ecx, edi
			call eax
			mov ebx, dword ptr ds : [esi]
			push 0x0
			push 0xFF00F0FF
			lea ecx, dword ptr ds : [ebx + 0x1]
			push _1AF4308
			mov dword ptr ds : [esi] , ecx
			mov esi, dword ptr ds : [edi]
			push 0xA45F
			call _122B260
			mov edx, dword ptr ds : [esi + 0x80]
			add esp, 0x4
			push eax
			push ebx
			mov ecx, edi
			call edx
			pop esi
			pop ebx
			pop edi
			mov esp, ebp
			pop ebp
			ret 0x4
			labnl3:
		call _13D6DA7
			labnl10 :
		mov eax, dword ptr ss : [ebp - 0x8]
			dec eax
			mov dword ptr ds : [esi] , eax
			pop esi
			pop ebx
			labnl1 :
		pop edi
			mov esp, ebp
			pop ebp
			ret 0x4


	}
}

Naked void _627_Hook_6ACF80() {
	_asm {
		cmp dword ptr ds : [esp] , 0x00E6E32E
		je labnl1A
		xor al, al
		ret 0x8
		labnl1A :
		push ebp
		mov ebp, esp
		push edi
		mov edi, ecx
		call _706410
		mov ecx, eax
		call _75A8C0
		test al, al
		jne labnl1
		call _706410
		mov ecx, eax
		call _75A880
		test al, al
		jne labnl1
		call _706410
		mov ecx, eax
		call _75A8E0
		test al, al
		jne labnl1
		push ebx
		push esi
		push 0x0
		or ebx, 0xFFFFFFFF
		push ebx
		mov byte ptr ds : [edi + 0x1B9] , 0x1
		mov ecx, dword ptr ds : [0x01A5FB20]
		push 0x163
		call _E745B0
		mov ecx, dword ptr ds : [0x01AE6EA8]
		call _7BBAD0
		xor esi, esi
		mov edi, edi
		labnl3 :
		mov ecx, dword ptr ds : [esi + 0x01AE6E7C]
			test ecx, ecx
			je labnl2
			mov eax, dword ptr ds : [ecx]
			mov edx, dword ptr ds : [eax + 0x8]
			push 0x1
			call edx
			labnl2 :
		xor eax, eax
			mov dword ptr ds : [esi + 0x01AE6E7C] , eax
			mov dword ptr ds : [esi + 0x01AE6E90] , ebx
			add esi, 0x4
			cmp esi, 0x14
			jl labnl3
			mov esi, dword ptr ss : [ebp + 0x8]
			mov dword ptr ds : [0x01AE6EA4] , eax
			cmp esi, eax
			je labnl4
			mov eax, dword ptr ds : [esi]
			mov edx, dword ptr ds : [eax + 0x24]
			push 0x2
			mov ecx, esi
			call edx
			test al, al
			je labnl5
			mov ecx, esi
			mov dword ptr ds : [0x01AE6EA4] , esi
			call _788960
			test al, al
			mov ecx, edi
			call _627_FDEDD0
			mov ecx, dword ptr ds : [0x01AE6EB8]
			sub ecx, dword ptr ds : [0x01AE6EB4]
			mov eax, 0x38E38E39
			imul ecx
			sar edx, 0x3
			mov eax, edx
			shr eax, 0x1F
			add eax, edx
			dec eax
			je labnl6
			dec eax
			je labnl7
			dec eax
			je labnl8
			mov dword ptr ds : [0x01AE6EA4] , 0x0
			mov eax, dword ptr ds : [edi]
			mov edx, dword ptr ds : [eax + 0x64]
			mov ecx, edi
			call edx
			pop esi
			pop ebx
			xor al, al
			pop edi
			pop ebp
			ret 0x8
			labnl8:
		mov dword ptr ds : [edi + 0x1A8] , 0x4
			mov dword ptr ds : [edi + 0x1AC] , 0x8A
			labnl6 :
			mov dword ptr ds : [edi + 0x1A4] , 0x47
			labnl5 :
			cmp dword ptr ds : [0x01AE6EA4] , 0x0
			jne labnl9
			labnl4 :
		mov eax, dword ptr ds : [edi]
			mov edx, dword ptr ds : [eax + 0x64]
			mov ecx, edi
			call edx
			pop esi
			pop ebx
			xor al, al
			pop edi
			pop ebp
			ret 0x8
			labnl7:
		mov dword ptr ds : [edi + 0x1A4] , 0x25
			mov dword ptr ds : [edi + 0x1A8] , 0x68
			jmp labnl5
			labnl9 :
		mov ecx, dword ptr ds : [edi + 0xC]
			push 0xC8
			push 0x37
			call _11BEBC0
			mov ecx, dword ptr ds : [edi + 0x180]
			mov eax, dword ptr ds : [ecx]
			mov edx, dword ptr ds : [eax + 0x18]
			push 0x0
			call edx
			push 0x0
			push 0x0
			push ebx
			mov dword ptr ds : [0x01AE6E90] , ebx
			mov dword ptr ds : [0x01AE6E94] , ebx
			mov dword ptr ds : [0x01AE6E98] , ebx
			mov dword ptr ds : [0x01AE6E9C] , ebx
			mov dword ptr ds : [0x01AE6EA0] , ebx
			push 0x01563498
			mov byte ptr ds : [edi + 0x1B8] , 0x1
			call _119FEF0
			add esp, 0x4
			push eax
			call _766160
			add esp, 0x10
			pop esi
			pop ebx
			mov al, 0x1
			pop edi
			pop ebp
			ret 0x8
			labnl1:
		push 0x0
			push 0x4B43
			call _122B260
			mov ecx, dword ptr ds : [0x01A5FB20]
			add esp, 0x4
			push eax
			push 0x110
			call _E77470
			xor al, al
			pop edi
			pop ebp
			ret 0x8
	}

}

Naked void _627_Hook_F4E280() {
	_asm {
		push ebp
		mov ebp, esp
		push ecx
		mov eax, dword ptr ds : [0x1A367F0]
		xor eax, ebp
		mov dword ptr ss : [ebp - 0x4] , eax
		push esi
		mov esi, ecx
		push edi
		mov edi, dword ptr ss : [ebp + 0x8]
		pushad
		push edi
		mov ecx, esi
		call _627_F5A370
		cmp byte ptr ds : [esi + 0x18D] , 0x0
		je labnl1
		popad
		mov ecx, esi
		push 0x00F4E29E
		ret
		labnl1 :
		popad
			push 0x00F4E31C
			ret
	}

}

Naked void _627_Hook_7ACC08() {
	_asm {
		mov edx, dword ptr ds : [esi]
		mov eax, dword ptr ds : [edx + 0x10]
		push edi
		push ebx
		mov ecx, esi
		call eax
		mov edx, dword ptr ds : [esi]
		mov eax, dword ptr ds : [edx + 0x18]
		push edi
		push ebx
		mov ecx, esi
		call eax
		pop ebx
		pop edi
		pop esi
		pop ebp
		ret 0x14
	}
}

Naked void _627_Hook_7815B0() {
	_asm {
		push ebp
		mov ebp, esp
		push ecx
		push esi
		mov esi, ecx
		mov eax, dword ptr ds : [esi]
		mov edx, dword ptr ds : [eax + 0xF0]
		call edx
		cmp dword ptr ds : [eax] , 0xFFFF
		ja labnl1
		push 0x007815CA
		ret
		labnl1 :
		push 0x007816D0
			ret
	}
}

int a = 1;//时装槽位开关 = 0 关(只有等于0的时候关)
int b = 1;//装备槽位开关 = 0 关(只有等于0的时候关)
Naked void _627_Hook_78A7ED() {
	_asm {
		call edx
		cmp dword ptr ds : [eax] , 0xFFFF
		ja labnl1
		cmp dword ptr ds : [eax] , 0xA//额外加这一段，识别时装的，如果要装开关，就在下面再加一个判断，为真则跳
		jb labnlA
		pushad
		mov edi, dword ptr ds : [0x01B466D8]
		xor eax, eax
		mov ax, word ptr ds : [edi]
		cmp ax, 0x0
		je labnl3
		cmp ax, 0x1
		je labnl3
		cmp ax, 0x2
		je labnl3
		cmp ax, 0x4
		je labnl3
		cmp ax, 0x8
		je labnl3
		cmp ax, 0x10
		je labnl3
		cmp ax, 0xFFEF
		je labnl3
		jmp labnl2
		labnl3 :
		xor eax, eax
			mov ax, word ptr ds : [edi + 0x6]
			cmp ax, 0x0
			je labnl4
			cmp ax, 0x1
			je labnl4
			cmp ax, 0x2
			je labnl4
			cmp ax, 0x4
			je labnl4
			cmp ax, 0x8
			je labnl4
			cmp ax, 0x10
			je labnl4
			cmp ax, 0xFFEF
			je labnl4
			jmp labnl2
			labnl4 :
		xor eax, eax
			mov ax, word ptr ds : [edi + 0xC]
			cmp ax, 0x0
			je labnl5
			cmp ax, 0x1
			je labnl5
			cmp ax, 0x2
			je labnl5
			cmp ax, 0x4
			je labnl5
			cmp ax, 0x8
			je labnl5
			cmp ax, 0x10
			je labnl5
			cmp ax, 0xFFEF
			je labnl5
			jmp labnl2
			labnl5 :
		xor eax, eax
			mov ax, word ptr ds : [edi + 0x12]
			cmp ax, 0x0
			je labnl6
			jmp labnl2
			labnl6 :
		xor eax, eax
			mov eax, dword ptr ds : [edi + 0x14]
			cmp eax, 0x0
			je labnl7
			jmp labnl2
			labnl7 :
		xor eax, eax
			mov eax, dword ptr ds : [edi + 0x18]
			cmp eax, 0x0
			je labnl8
			jmp labnl2
			labnl8 :
		xor eax, eax
			mov ax, word ptr ds : [edi + 0x1C]
			cmp ax, 0x0
			je labnl9
			jmp labnl2
			labnl9 :
		mov ecx, 0x1F
			push ecx
			push edi
			push ebx
			call _627_MECPY
			add edi, 0x1E
			mov dword ptr ds : [0x01B466D8] , edi
			pop ebx
			pop edi
			pop ecx
			labnl2 :
		popad
			cmp b, 0x0
			jz labnl1
			push 0x0078A7F8
			ret
			labnl1 :
		push 0x0078A929
			ret
			labnlA :
		cmp a, 0x0
			jne labnlB
			push 0x0078A929
			ret
			labnlB :
		push 0x0078A7F8
			ret
	}
}

Naked void _627_Hook_797E40() {
	_asm {
		push ebp
		mov ebp, esp
		sub esp, 0x1C
		push esi
		mov esi, ecx
		mov eax, dword ptr ds : [esi]
		mov edx, dword ptr ds : [eax + 0xF0]
		mov dword ptr ss : [ebp - 0xC] , esi
		call edx
		cmp dword ptr ds : [eax] , 0xFFFF
		ja labnl1
		push 0x00797E5F
		ret
		labnl1 :
		push 0x0079801B
			ret
	}
}

Naked void _627_Hook_F10539() {
	_asm {
		mov eax, dword ptr ds : [esi + 0x1A0]
		mov ecx, dword ptr ds : [0x01A5FB24]
		push eax
		mov eax, 0x007B0620
		call eax
		cmp eax, 0xFFFFFFFF
		jne labnl
		mov edx, dword ptr ds : [esi]
		mov eax, dword ptr ds : [edx + 0x64]
		mov dword ptr ds : [esi + 0x1A0] , 0x0
		mov ecx, esi
		push 0x00F1054A
		ret
		labnl :
		push 0x00F1054F
			ret

	}
}

Naked void _627_Hook_7B926F() {
	_asm {
		pushad
		mov ecx, dword ptr ds : [0x01B470E0]
		push 0x0
		push 0x7
		mov eax, 0x011C10C0
		call eax
		test al, al
		jne labnl
		popad
		mov eax, dword ptr ds : [edx + 0xF0]
		call eax
		mov ecx, dword ptr ds : [eax]
		push 0x0
		push 0x6
		push 0x1
		push ecx
		mov ecx, dword ptr ss : [ebp - 0x8]
		push ebx
		mov edi, 0x007B64B0
		call edi
		pop edi
		pop esi
		pop ebx
		mov esp, ebp
		pop ebp
		ret 0x4
		labnl:
		mov ecx, dword ptr ds : [0x01A5FB20]
			push 0x0
			push esi
			push 0xB4
			mov eax, 0x00E6E070
			call eax
			popad
			push 0x7B9292
			ret
	}
}

Naked void _627_Hook_FD3F9D() {
	_asm {
		mov eax, dword ptr ds : [0x01AE6EA4]
		mov ecx, dword ptr ds : [0x01A5FB24]
		push eax
		mov eax, 0x007B0620
		call eax
		cmp eax, 0xFFFFFFFF
		jne labnl
		mov dword ptr ds : [0x01AE6EA4] , ebx
		mov edx, dword ptr ds : [edi]
		mov eax, dword ptr ds : [edx + 0x64]
		mov ecx, edi
		call eax
		pop ebx
		pop edi
		pop esi
		mov esp, ebp
		pop ebp
		ret 0x4
		labnl:
		push 0x00FD3B4E
			ret
	}
}

Naked void _627_Hook_F10767() {
	_asm {
		cmp eax, 0xFFFFFFFF
		je labnl
		add eax, 0x39
		mov ecx, dword ptr ds : [0x01AE36A4]
		push 0x00F1076D
		ret
		labnl :
		pop eax
			mov eax, dword ptr ds : [esi + 0x1A0]
			mov ecx, dword ptr ds : [0x01A5FB24]
			push edi
			push eax
			mov eax, 0x007B0620
			call eax
			mov ecx, dword ptr ds : [0x01AE36A4]
			push 0x00F1076D
			ret
	}
}

Naked void _627_Hook_FD37AE() {
	_asm {
		cmp eax, 0xFFFFFFFF
		jne labnl
		mov eax, dword ptr ds : [0x01AE6EA4]
		mov ecx, dword ptr ds : [0x01A5FB24]
		push esi
		push eax
		mov byte ptr ss : [ebp - 0x30] , 0x0
		mov eax, 0x007B0620
		call eax
		add eax, 0x68
		labnl :
		mov ecx, dword ptr ds : [0x01AE6EA4]
		push 0x00FD37B4
		ret
	}
}

Naked void _627_Hook_70BD0E() {
	_asm {
		movzx ecx, word ptr ss : [ebp - 0x4]
		cmp ecx, 0x69
		ja labnl1
		add esp, 0x10
		push ecx
		mov ecx, dword ptr ds : [0x01A5FB38]
		mov eax, 0x007B03C0
		call eax
		push 0x0070BD21
		ret
		labnl1 :
		sub ecx, 0x68
			add esp, 0x10
			push ecx
			mov ecx, dword ptr ds : [0x01A5FB24]
			mov eax, 0x007B03C0
			call eax
			push 0x0070BD21
			ret
	}
}

Naked void _627_Hook_F10BAD() {
	_asm {
		mov ecx, dword ptr ds : [0x01A5FB38]
		push edx
		mov eax, 0x007B0620
		call eax
		cmp eax, 0xFFFFFFFF
		je labnl
		push 0x00F10BB9
		ret
		labnl :
		mov edx, dword ptr ds : [esi + 0x19C]
			mov ecx, dword ptr ds : [0x01A5FB24]
			push edx
			mov eax, 0x007B0620
			call eax
			cmp eax, 0xFFFFFFFF
			je labn2
			push 0x00F10BB9
			ret
			labn2 :
		push 0x00F10BBE
			ret
	}
}

Naked void _627_Hook_746A22() {
	_asm {
		lea ecx, dword ptr ss : [ebp - 0x46C]
		test al, al
		jne labnl
		pushad
		mov edi, dword ptr ds : [0x01B466D8]
		mov ax, word ptr ds : [edi]
		cmp ax, 0x10
		ja labnl1
		popad
		lea eax, dword ptr ss : [ebp - 0x46C]
		push eax
		mov ecx, esi
		mov edx, 0x0078A7B0
		call edx
		xor eax, eax
		push 0x00746A8C
		ret
		labnl :
		push 0x00746A28
			ret
			labnl1 :
		popad
			push 0x00746A8C
			ret
	}
}

Naked void _627_Hook_78A933() {
	_asm {
		push eax
		xor eax, eax
		labnl3 :
		mov dword ptr ds : [ebx + 0x4 * eax] , 0x0
			add eax, 0x1
			cmp eax, 0x6
			jne labnl3
			add eax, 1
			mov word ptr ds : [ebx + 0x4 * eax] , 0x0
			pop eax
			pop ecx
			pop edi
			pop esi
			pop ebx
			mov esp, ebp
			pop ebp
			ret 0x4
	}
}

Naked void _627_Hook_74C473() {
	_asm {
		pushad
		mov eax, 0
		labnl2:
		imul ebx, eax, 0x4
			mov dword ptr ds : [INSER_DATA + ebx] , 0x0
			inc eax
			cmp eax, 158
			jb labnl2
			popad
			mov dword ptr ss : [ebp - 0x4] , ebx
			mov dword ptr ss : [ebp - 0x6C] , ebx
			push 0x0074C479
			ret
	}
}

Naked void _627_Hook_EAB94F() {
	_asm {
		mov dword ptr ds : [eax] , esi
		mov eax, dword ptr ss : [ebp - 0x18]
		add dword ptr ss : [ebp - 0x24] , 0x4C
		add eax, 0x4
		mov dword ptr ss : [ebp - 0x18] , eax
		mov eax, dword ptr ss : [ebp - 0x2C]
		pushad
		lea ebx, INSER_DATA
		imul edx, eax, 0x1F
		add ebx, edx
		mov dword ptr ds : [0x01B466D8] , ebx
		mov edx, dword ptr ds : [esi]
		mov edx, dword ptr ds : [edx + 0xDC]
		cmp edx, 0x0078A7B0
		jne labnl
		mov edi, 0x23
		lea eax, INSER_TOP + 0x4
		push eax
		mov ecx, esi
		call edx
		labnl :
		popad
			inc eax
			mov dword ptr ss : [ebp - 0x2C] , eax
			cmp eax, dword ptr ss : [ebp - 0x34]
			jl labnl1
			push 0x00EAB96E
			ret
			labnl1 :
		push 0x00EAB7DB
			ret
	}
}

Naked void _627_Hook_74C814() {
	_asm {
		pushad
		mov edi, dword ptr ds : [0x01B466D8]
		xor ebx, ebx
		mov bx, word ptr ds : [edi]
		cmp bx, 0x0
		je labnl3
		cmp bx, 0x1
		je labnl3
		cmp bx, 0x2
		je labnl3
		cmp bx, 0x4
		je labnl3
		cmp bx, 0x8
		je labnl3
		cmp bx, 0x10
		je labnl3
		cmp bx, 0xFFEF
		je labnl3
		jmp labnl
		labnl3 :
		xor ebx, ebx
			mov bx, word ptr ds : [edi + 0x6]
			cmp bx, 0x0
			je labnl4
			cmp bx, 0x1
			je labnl4
			cmp bx, 0x2
			je labnl4
			cmp bx, 0x4
			je labnl4
			cmp bx, 0x8
			je labnl4
			cmp bx, 0x10
			je labnl4
			cmp bx, 0xFFEF
			je labnl4
			jmp labnl
			labnl4 :
		imul esi, eax, 0x1f
			lea ecx, INSER_DATA
			add ecx, esi
			mov esi, 0x1F
			push esi
			push edi
			push ecx
			call _627_MECPY
			pop ecx
			pop edi
			pop esi
			add edi, 0x1E
			mov dword ptr ds : [0x01B466D8] , edi
			labnl :
		popad
			movzx edx, byte ptr ss : [ebp - 0x62]
			inc eax
			push 0x0074C819
			ret
	}
}

Naked void _627_Hook_74CBCE() {
	_asm {
		pushad
		mov edx, dword ptr ds : [esi]
		mov edx, dword ptr ds : [edx + 0xDC]
		cmp edx, 0x0078A7B0
		jne labnl
		mov edi, 0x23
		lea eax, INSER_TOP + 0x4
		push eax
		mov ecx, esi
		call edx
		labnl :
		popad
			mov dword ptr ss : [ebp - 0x4] , 0xFFFFFFFF
			push 0x0074CBD5
			ret
	}
}
int _627_call_7B1820 = 0x007B1820;
Naked void _627_Hook_747911() {
	_asm {
		call _627_call_7B1820
		pushad
		cmp ebx, 0x0
		je labnl1
		mov edx, dword ptr ds : [ebx]
		mov edx, dword ptr ds : [edx + 0xDC]
		cmp edx, 0x0078A7B0
		jne labnl1
		mov edi, 0x23
		lea eax, INSER_TOP + 0x4
		push eax
		mov ecx, ebx
		mov esi, ebx
		call edx
		labnl1 :
		popad
			push 0x00747916
			ret


	}
}
int _627_call_F8C0E0 = 0x00F8C0E0;
Naked void _627_Hook_719D6F() {
	_asm {
		mov eax, 0x00F8C0E0
		call eax
		pushad
		cmp esi, 0x0
		je labnl1
		mov edx, dword ptr ds : [esi]
		mov edx, dword ptr ds : [edx + 0xDC]
		cmp edx, 0x0078A7B0
		jne labnl1
		mov edi, 0x23
		lea eax, INSER_TOP + 0x4
		push eax
		mov ecx, esi
		call edx
		labnl1 :
		popad
			push 0x00719D74
			ret
	}
}


void __fastcall Mosaic_0627() {
	//-头 装备加时装镶嵌
	WriteCall((LPVOID)0x00F554E1, _627_Call_F554E1);//补全徽章信息显示
	WriteJmp((LPVOID)0x006ACF80, _627_Hook_6ACF80);//补全缺少的代码段,做了地址判断处理，免得在其他地方被调用导致的闪退。
	WriteJmp((LPVOID)0x00F4E280, _627_Hook_F4E280);//显示面板的徽章信息
	WriteJmp((LPVOID)0x007ACC08, _627_Hook_7ACC08);//时装图标显示孔位(不做处理不显示除开克隆)
	//以上是补码
	WriteJmp((LPVOID)0x007815B0, _627_Hook_7815B0);//装备图标显示孔位(不做处理不显示)
	WriteJmp((LPVOID)0x0078A7ED, _627_Hook_78A7ED);//让徽章以及孔位数据写入到装备中(不做处理没效果)
	WriteJmp((LPVOID)0x00797E40, _627_Hook_797E40);//装备徽章效果生效
	WriteJmp((LPVOID)0x00F10539, _627_Hook_F10539);//打孔窗口显示装备
	WriteJmp((LPVOID)0x007B926F, _627_Hook_7B926F);//让有镶嵌的装备/时装调用出徽章嵌入界面
	WriteJmp((LPVOID)0x00FD3F9D, _627_Hook_FD3F9D);//让装备和时装共存调用出镶嵌徽章的界面(持续显示)
	WriteJmp((LPVOID)0x00F10767, _627_Hook_F10767);//拓展发包编号(用于区分是装备还是时装)时装
	WriteJmp((LPVOID)0x00FD37AE, _627_Hook_FD37AE);//拓展发包编号(用于区分是装备还是时装)装备
	WriteJmp((LPVOID)0x0070BD0E, _627_Hook_70BD0E);//开孔完回包显示,用于决定是显示装备还是时装
	WriteJmp((LPVOID)0x00F10BAD, _627_Hook_F10BAD);//镶嵌完回包显示。
	WriteJmp((LPVOID)0x00746A22, _627_Hook_746A22);//商店回购显示
	WriteJmp((LPVOID)0x0078A933, _627_Hook_78A933);//清理外侵入者,让它让出这个位置
	WriteJmp((LPVOID)0x0074C473, _627_Hook_74C473);//外侵入者上位。
	WriteJmp((LPVOID)0x00EAB94F, _627_Hook_EAB94F);//对在回购中的有镶嵌的装备进行数据的处理(对躺在回购中的尸体进行鞭尸处理，狠狠地抽)
	WriteJmp((LPVOID)0x0074C814, _627_Hook_74C814);//分析包存储的信息
	WriteJmp((LPVOID)0x0074CBCE, _627_Hook_74CBCE);//掉落畜生,这个Hook就是拿刀砍死这个掉落的畜生
	WriteJmp((LPVOID)0x00747911, _627_Hook_747911);//修复称号簿数据不写入问题
	WriteJmp((LPVOID)0x00719D6F, _627_Hook_719D6F);//修复设计图返回多个装备或材料崩溃问题
	RtlCopyMemory((LPVOID)0x00746A1E, "\x84\xC9", 2);//邮箱中显示信息
	RtlCopyMemory((LPVOID)0x00E6EF8E, "\xE9\x8D\x00\x00\x00", 5);//让道具识别(不做额外处理,想更好看一点自己在这个地址分析)
	RtlCopyMemory((LPVOID)0x006B18B6, "\xEB\x4C", 2);//屏蔽掉原本的徽章嵌入窗口调用
	RtlCopyMemory((LPVOID)0x00E83651, "\x90\x90\x90\x90\x90\x90", 6);//拍卖行的装备徽章数据写入
	RtlCopyMemory((LPVOID)0x00E83687, "\x90\x90", 2);//拍卖行的装备徽章数据写入
	//-尾 装备加时装镶嵌
}