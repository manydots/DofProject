#pragma once
#include "dof.h"
#include "Hook.h"

Naked void _627_Hook_916024() {
	_asm {
		cmp eax, 0x80
		jl labnl1
		push 0x0091602A
		ret
		labnl1 :
		push 0x00915F60
			ret
	}
}
Naked void _627_Hook_915FD9() {
	_asm {
		cmp dword ptr ss : [ebp - 0xC] , 0x80
		jae labnl
		push 0x00915FDF
		ret
		labnl :
		push 0x009160B7
			ret
	}

}

INT keyCode_1 = 55; // ��չ1��λ ��λCode
INT keyCode_2 = 56; // ��չ2��λ ��λCode

int _627_call_965130 = 0x00965130;
int _627_call_9673C0 = 0x009673C0;
int _627_call_E67DF0 = 0x00E67DF0;
int _627_call_13CC057 = 0x013CC057;
Naked void _627_Hook_9160DD() {
	_asm {
		mov dword ptr ss : [ebp - 0xC] , 0x01A60580
		xor edi, edi
		labnl6 :
		//cmp dword ptr ss : [ebp - 0xC] , 0x01A605A0
		//je labnlR
		mov ecx, dword ptr ds : [esi + 0xB0]
			mov eax, dword ptr ds : [ecx]
			mov edx, dword ptr ss : [ebp - 0xC]
			mov eax, dword ptr ds : [eax + 0x2C]
			push edx
			call eax
			//cmp eax,0x0
			//je labnlRX
			mov ebx, dword ptr ss : [ebp - 0x8]
			mov byte ptr ss : [ebp - 0x2] , al
			test ebx, ebx
			je labnl1
			cmp byte ptr ss : [ebp - 0x3] , 0x0
			je labnl1
			lea ecx, dword ptr ds : [edi]
			push ecx
			mov ecx, ebx
			call _627_call_965130
			mov byte ptr ss : [ebp - 0x2] , al
			labnl1 :
		mov ecx, dword ptr ds : [0x1A5FB20]
			test ecx, ecx
			je labnl2
			call _627_call_E67DF0
			test al, al
			je labnl2
			mov byte ptr ss : [ebp - 0x2] , 0x0
			labnl2 :
			cmp edi, 0x8
			jae labnl3
			cmp byte ptr ds : [edi + esi + 0x38] , 0x0
			jne labnl4
			cmp byte ptr ss : [ebp - 0x2] , 0x0
			je labnl4
			cmp byte ptr ss : [ebp - 0x1] , 0x0
			jne labnl4
			mov byte ptr ds : [edi + esi + 0x4C] , 0x1
			mov byte ptr ss : [ebp - 0x1] , 0x1
			test ebx, ebx
			je labnl5
			cmp byte ptr ss : [ebp - 0x4] , 0x0
			je labnl5
			lea edx, dword ptr ds : [edi]
			push edx
			mov ecx, ebx
			call _627_call_9673C0
			jmp labnl5
			labnl3 :
		call _627_call_13CC057
			labnl4 :
		mov byte ptr ds : [edi + esi + 0x4C] , 0x0
			labnl5 :
			mov al, byte ptr ss : [ebp - 0x2]
			mov byte ptr ds : [edi + esi + 0x38] , al
			labnlRX :
		mov eax, dword ptr ss : [ebp - 0xC]
			add eax, 0x10
			inc edi
			mov dword ptr ss : [ebp - 0xC] , eax
			cmp eax, 0x01A605A0
			jl labnl6
			labnlR :
		pop edi
			pop esi
			pop ebx
			mov esp, ebp
			pop ebp
			ret

	}

}
int _627_call_4D3F50 = 0x004D3F50;
int _627_call_4D95C0 = 0x004D95C0;
Naked void _627_Hook_4B3392() {
	_asm {
		pop eax
		cmp eax, 0x1A
		je labnl1
		cmp eax, 0x1B
		je labnl2
		push eax
		call _627_call_4D95C0
		push 0x004B3397
		ret
		labnl1 :
		mov eax, keyCode_1
			push eax
			call _627_call_4D95C0
			push 0x004B3397
			ret
			labnl2 :
		mov eax, keyCode_2
			push eax
			call _627_call_4D95C0
			push 0x004B3397
			ret
	}
}
Naked void _627_Hook_75DE5E() {
	_asm {
		call _627_call_4D95C0
		push keyCode_1
		mov ecx, eax
		call _627_call_4D3F50
		mov dword ptr ds : [0x01A60588] , eax
		mov dword ptr ds : [0x01A60594] , esi
		call _627_call_4D95C0
		push keyCode_2
		mov ecx, eax
		call _627_call_4D3F50
		mov dword ptr ds : [0x01A60598] , eax
		mov dword ptr ds : [0x01A605A4] , esi
		pop edi
		pop esi
		ret
	}
}
Naked void _627_Hook_6C8CEA() {
	_asm {
		mov esi, eax
		cmp esi, 0x5
		ja labn2
		add esi, 0x14
		push 0x006C8D1A
		ret
		labn2 :
		cmp esi, 0x6
			je labnl3
			cmp esi, 0x7
			je labnl4
			push 0x006C8CF6
			ret
			labnl3 :
		mov esi, keyCode_1 //pvf������ CTRL
			push 0x006C8D1A
			ret
			labnl4 :
		mov esi, keyCode_2 //pvf������ ATL
			push 0x006C8D1A
			ret
	}

}
Naked void _627_Hook_6D8DA6() {
	_asm {
		cmp eax, 0x6
		jge labnl
		push 0x006D8DAB
		ret
		labnl :
		cmp eax, 0xD
			je labnl1
			cmp eax, 0xC
			je labnl2
			push 0x006D8DBF
			ret
			labnl1 :
		mov eax, keyCode_2
			push 0x006D8DC2
			ret
			labnl2 :
		mov eax, keyCode_1
			push 0x006D8DC2
			ret
	}
}
Naked void _627_Hook_11D2EE8() {
	_asm {
		cmp eax, 0x44
		jne labnl1
		mov dword ptr ds : [esi + 0x2B8] , 0x2
		mov dword ptr ds : [esi + 0x2BC] , 0x7
		labnl1 :
		mov eax, dword ptr ds : [esi + 0x2B8]
		sub eax, edi
		imul eax, dword ptr ds : [esi + 0x2BC]
		xor edi, edi
		push 0x011D2EF9
		ret
	}
}
Naked void _627_Hook_10636E6() {
	_asm {
		cmp dword ptr ds : [esp + 0x40] , 0x21
		jne labnl1
		cmp dword ptr ds : [esp + 0x44] , 0x22
		jne labnl1
		mov dword ptr ds : [edi + 0x4C] , 497
		mov dword ptr ds : [edi + 0x48] , 569
		labnl1 :
		add eax, dword ptr ds : [edi + 0x4C]
		mov ecx, ebx
		push 0x010636EB
		ret
	}
}
static INT _627_Call_734E20 = 0x00734E20;
static INT _627_Call_B09680 = 0x00B09680;
static INT _627_Call_13CC057 = 0x013CC057;
static INT _627_Call_y_11B4030 = 0x011B4030;
Naked void _627_Call_11B4030() {
	_asm {
		push ebp
		mov ebp, esp
		sub esp, 0xC
		cmp byte ptr ss : [ebp + 0x10] , 0x0
		push esi
		jne labnl1
		mov esi, dword ptr ds : [ecx + 0x5C]
		test esi, esi
		je labnl1
		mov edx, dword ptr ss : [ebp + 0x8]
		mov eax, dword ptr ss : [ebp + 0xC]
		add edx, dword ptr ds : [esi + 0x14]
		add eax, dword ptr ds : [esi + 0x18]
		jmp labnl7
		labnl1 :
		mov eax, dword ptr ss : [ebp + 0xC]//
			mov edx, dword ptr ss : [ebp + 0x8]
			labnl7 :
			cmp dword ptr ds : [ecx + 0x1C] , 0x0//
			jne labnl2
			cmp dword ptr ds : [ecx + 0x20] , 0x0
			jne labnl2
			mov dword ptr ds : [ecx + 0x78] , edx
			mov dword ptr ds : [ecx + 0x7C] , eax
			labnl2 :
		cmp dword ptr ds : [ecx + 0x6C] , 0x0//
			mov esi, dword ptr ds : [ecx + 0x14]
			mov dword ptr ds : [ecx + 0x1C] , esi
			mov esi, dword ptr ds : [ecx + 0x18]
			mov dword ptr ds : [ecx + 0x20] , esi
			cmp eax, 531
			jne labn17x1
			add edx, 33//����һ�в�λ��X���ƶ�33������
			cmp edx, 800//����һ�е��߸���λ�ƶ�������һ�е��߲�λ
			jne labn17x1
			mov eax, 497
			mov edx, 767//767
			jmp labnl7x
			labn17x1 :
		cmp edx, 767//����һ�е��߸���λ�ƶ�������һ�е�һ��λ��
			jne labnl7x
			cmp eax, 497//497
			jne labnl7x
			mov edx, 569//569
			mov eax, 531//531
			labnl7x :
		mov dword ptr ds : [ecx + 0x14] , edx
			mov dword ptr ds : [ecx + 0x18] , eax
			je labnl3
			sub edx, dword ptr ds : [ecx + 0x1C]
			push ebx
			sub eax, esi
			mov dword ptr ss : [ebp + 0x10] , eax
			push edi
			lea ebx, dword ptr ds : [ecx + 0x64]
			lea eax, dword ptr ss : [ebp - 0xC]
			push eax
			mov ecx, ebx
			mov dword ptr ss : [ebp + 0xC] , edx
			call _627_Call_734E20
			mov esi, dword ptr ss : [ebp - 0xC]
			mov edi, dword ptr ss : [ebp - 0x4]
			labnl9 :
			lea ecx, dword ptr ss : [ebp - 0xC]
			push ecx
			mov ecx, ebx
			call _627_Call_B09680
			test esi, esi
			je labnl4
			mov edx, dword ptr ds : [esi]
			test edx, edx
			je labnl4
			mov ecx, dword ptr ds : [eax]
			test ecx, ecx
			je labnl5
			mov ecx, dword ptr ds : [ecx]
			labnl5 :
			cmp edx, ecx//
			jne labnl4
			cmp edi, dword ptr ds : [eax + 0x8]
			je labnl6
			mov eax, edx
			test eax, eax
			je labnl4
			test edi, edi
			je labnl4
			cmp edi, dword ptr ds : [eax + 0x4]
			je labnl4
			mov ecx, dword ptr ds : [edi + 0x8]
			test ecx, ecx
			je labnl8
			mov edx, dword ptr ds : [ecx + 0x18]
			add edx, dword ptr ss : [ebp + 0x10]
			mov eax, dword ptr ds : [ecx + 0x14]
			add eax, dword ptr ss : [ebp + 0xC]
			push 0x1
			push edx
			push eax
			call _627_Call_11B4030
			labnl8 :
		mov eax, dword ptr ds : [esi]//
			test eax, eax
			je labnl4
			cmp edi, dword ptr ds : [eax + 0x4]
			je labnl4
			mov edi, dword ptr ds : [edi]
			jmp labnl9
			labnl4 :
		call _627_Call_13CC057//
			labnl6 :
		pop edi//
			pop ebx
			labnl3 :
		pop esi//
			mov esp, ebp
			pop ebp
			ret 0xC
	}
}
Naked void _627_Hook_10636F7() {
	_asm {
		cmp dword ptr ds : [esp + 0x48] , 0x21
		jne labnl1
		cmp dword ptr ds : [esp + 0x4c] , 0x22
		jne labnl1
		call _627_Call_11B4030
		push 0x010636FC
		ret
		labnl1 :
		call _627_Call_y_11B4030
			push 0x010636FC
			ret
	}
}
Naked void _627_Hook_11B4410() {
	_asm {
		mov eax, dword ptr ds : [esp]
		mov dword ptr ds : [ecx + 0x280] , eax
		push ebp

		mov ebp, esp
		push 0xFFFFFFFF
		push 0x014BC616

		push 0x011B441A
		ret
	}
}
INT _627_7_slot_x = 718;//��չ1��λX������
INT _627_7_slot_y = 520;//��չ1��λY������
INT _627_8_slot_x = 718;//��չ2��λX������
INT _627_8_slot_y = 558;//��չ2��λY������
Naked void _627_Hook_4CDCDC() {
	_asm {
		cmp ebx, 718
		jne labnl1
		push 0x1
		push _627_7_slot_y //y��
		push _627_7_slot_x //x��
		push 0x0004CDCE4
		ret
		labnl1 :
		cmp ebx, 748
			jne labnl2
			push 0x1
			push _627_8_slot_y //y��
			push _627_8_slot_x //x��
			push 0x0004CDCE4
			ret
			labnl2 :
		push 0x1
			push 0x22E
			push ebx
			push 0x0004CDCE4
			ret
	}
}
int _627_call_8D1CE0 = 0x8D1CE0;
int _627_call_1310110 = 0x1310110;
Naked void _627_Hook_917DB5() {
	_asm {
		cmp esi, 0x8
		ja lanbl917CF6
		cmp byte ptr ds : [edi + ebx + 0x46] , 0x0
		je lanbl917CF6
		mov ecx, dword ptr ss : [ebp + 0xC]
		mov dword ptr ss : [ebp - 0x4] , 0x4
		test ecx, ecx
		je lanbl917CA9
		call _627_call_8D1CE0
		cmp byte ptr ds : [edi + ebx + 0x46] , 0x0
		je lanbl917CA9
		mov ecx, dword ptr ss : [ebp + 0xC]
		sub esi, 0x6
		shl esi, 0x4
		add esi, 0x01A60580
		push esi
		call _627_call_1310110

		lanbl917CF6 :
		lea ecx, ds : [esi - 0xC6]
			push 0x00917DBB
			ret
			lanbl917CA9 :
		push 0x00917CA9
			ret
	}


}
Naked void _627_Hook_917D9F() {
	_asm {
		cmp esi, 0x6
		jne labnlctrl
		push 0x01A60580
		mov ecx, edi
		push 0x00917DAB
		ret
		labnlctrl :
		cmp esi, 0x7
			jne labnlR
			push 0x01A60590
			mov ecx, edi
			push 0x00917DAB
			ret
			labnlR :
		shl esi, 0x4
			add esi, 0x01A600D0
			push esi
			mov ecx, edi
			push 0x00917DAB
			ret
	}
}
Naked void _627_Hook_915F95() {
	_asm {
		mov ecx, dword ptr ds : [esi + 0xB0]
		mov edx, dword ptr ds : [ecx]
		mov edx, dword ptr ds : [edx + 0x2C]
		cmp edi, 0x6
		jne labnl1
		mov eax, 0x01A60580
		push 0x00915FA6
		ret
		labnl1 :
		cmp edi, 0x7
			jne labnl2
			mov eax, 0x01A60590
			push 0x00915FA6
			ret
			labnl2 :
		lea eax, dword ptr ds : [ebx + 0x1A600D0]
			push 0x00915FA6
			ret
	}
}
Naked void _627_Hook_916021() {
	_asm {
		cmp eax, 0x80
		jl labnl1
		push 0x0091602A
		ret
		labnl1 :
		push 0x00915F60
			ret

	}
}
Naked void _627_Hook_916081() {
	_asm {
		cmp byte ptr ds : [0x01A605F0 + edi] , 0x0
		jne labnl1
		push 0x00916088
		ret
		labnl1 :
		push 0x009160BC
			ret
	}
}
Naked void _627_Hook_9160C4() {
	_asm {
		mov byte ptr ds : [0x01A605F0 + edi] , al
		mov eax, dword ptr ss : [ebp - 0xC]
		add eax, 0x10
		push 0x009160CE
		ret
	}

}


void __fastcall SkilSlot_0627(int keyCode1, int keyCode2, int keyCode1x, int keyCode1y, int keyCode2x, int keyCode2y) {
	// ���¸�ֵ��λ&������Ϣ
	keyCode_1 = keyCode1; // ��չ1��λ ��λCode
	keyCode_2 = keyCode2; // ��չ2��λ ��λCode

	_627_7_slot_x = keyCode1x; // ��չ1��λX������
	_627_7_slot_y = keyCode1y; // ��չ1��λY������
	_627_8_slot_x = keyCode2x; // ��չ2��λX������
	_627_8_slot_y = keyCode2y; // ��չ2��λY������

	RtlCopyMemory((LPVOID)0x004CDCFA, "\x81\xFB\x0A\x03\x00\x00", 6);//ԭ����չ2����λ���ݡ�
	RtlCopyMemory((LPVOID)0x004C0AE6, "\x83\xF8\x08", 3);//��ʾ�ڻ�����
	RtlCopyMemory((LPVOID)0x004B33C7, "\x83\xFF\x08", 3);//������ʾ
	RtlCopyMemory((LPVOID)0x004CC4AE, "\x83\xFF\x08", 3);//��ֵ���չʾ��ȡ
	RtlCopyMemory((LPVOID)0x004CC383, "\x83\xFB\x08", 3);//��ֵ���չʾ��ȡ
	RtlCopyMemory((LPVOID)0x004BA475, "\x83\xFB\x08", 3);//ʹ�����ܹ��任��λ
	RtlCopyMemory((LPVOID)0x004BA1E3, "\x83\xFE\x08", 3);//ʹ�����ܹ��任��λ
	RtlCopyMemory((LPVOID)0x004BB64F, "\x83\xFE\x08", 3);//�ܹ��Ҽ�����
	RtlCopyMemory((LPVOID)0x00917D3D, "\x83\xFE\x09", 3);//ʹ�ܹ��ͷż���
	RtlCopyMemory((LPVOID)0x004FA050, "\x8D\x70\x08", 3);//����ѧϰ���ڣ����������λ����
	RtlCopyMemory((LPVOID)0x00917648, "\x83\xFB\x08", 3);//����ѧϰ������ʾ����ͼ��
	RtlCopyMemory((LPVOID)0x009176DE, "\x83\xFB\x08", 3);
	RtlCopyMemory((LPVOID)0x009167F8, "\x83\xFE\x08", 3);
	WriteJmp((LPVOID)0x004B3392, _627_Hook_4B3392);//����������ʾ
	WriteJmp((LPVOID)0x009160DD, _627_Hook_9160DD);//����ʶ��
	WriteJmp((LPVOID)0x009160C4, _627_Hook_9160C4);//������������
	WriteJmp((LPVOID)0x00916081, _627_Hook_916081);//������������
	WriteJmp((LPVOID)0x00917D9F, _627_Hook_917D9F);//�����ͷ�
	WriteJmp((LPVOID)0x0075DE5E, _627_Hook_75DE5E);//������ʶд��
	WriteJmp((LPVOID)0x006C8CEA, _627_Hook_6C8CEA);
	WriteJmp((LPVOID)0x006D8DA6, _627_Hook_6D8DA6);
	WriteJmp((LPVOID)0x011D2EE8, _627_Hook_11D2EE8);//����ѧϰ����Ĭ��ʮ�ĸ����ܲ�λ������pvfӰ��
	WriteJmp((LPVOID)0x010636E6, _627_Hook_10636E6);//����ѧϰ����Ĭ��ʮ�ĸ����ܲ�λ������pvfӰ��
	WriteJmp((LPVOID)0x010636F7, _627_Hook_10636F7);//����ѧϰ����Ĭ��ʮ�ĸ����ܲ�λ�Ű�
	WriteJmp((LPVOID)0x004CDCDC, _627_Hook_4CDCDC);//���ɲ�λ��ʱ��д������ֵ

	/*
	fr��
	Memory.protect(ptr(0x08604B1E), 4, 'rwx');
	ptr(0x08604B1E).writeByteArray([0x83, 0x7D, 0xEC, 0x07]);
	Memory.protect(ptr(0x08604B8C), 7, 'rwx');
	ptr(0x08604B8C).writeByteArray([0xC7, 0x45, 0xE4, 0x08 , 0x00 ,0x00,0x00]);
	Memory.protect(ptr(0x08604A09), 4, 'rwx');
	ptr(0x08604A09).writeByteArray([0x83, 0x7D, 0x0C, 0x07]);
	Memory.protect(ptr(0x086050b1), 7, 'rwx');
	ptr(0x086050b1).writeByteArray([0xC7,0x45,0xEC,0x08,0x00,0x00,0x00]);
	Memory.protect(ptr(0x0860511c), 7, 'rwx');
	ptr(0x0860511c).writeByteArray([0xC7,0x45,0xE8,0x08,0x00,0x00,0x00]);


	pvf:
	�����ɫ·����clientonly/hotkeysystem.co
	�����ɫ·����clientonly/hotkeysystemforcreator.co

	��ע:
	`��չ���ܿ��ټ� 7`	---[56] HookKey1
	`dungeon`
	`right`	17 ---[17] &L_Ctrl
	`right`	18 ---[18] &L_Alt

	[key]
	`��չ���ܿ��ټ� 7`	55
	`dungeon`
	`right`	17

	[key]
	`��չ���ܿ��ټ� 8`	56
	`dungeon`
	`right`	18
	*/
}