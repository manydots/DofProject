#pragma once
#include <iostream>
#include "dof.h"


void FixPackage(std::string exeType);
void DisableBuyback(std::string exeType);
void SetClipboardData(std::string exeType);
void FixLetterText(std::string exeType);

namespace Gamex
{
	//#define _v(v1,v2) ((v1|v2)<<8)
	//#define rgb(r,g,b) ((BYTE)r|_v((BYTE)g,_v((BYTE)b,0xFFFFFF00)))
	//#define rgba(r,g,b,a) ((BYTE)r|_v((BYTE)g,_v((BYTE)b,(BYTE)a<<8)))

	/**
	 *
	 * exeType�ͻ������� 0627 0725 1031
	 * dnf.exe�汾
	 * 0627  1.1180.2.1
	 * 0725  1.1200.4.1
	 * 1031  1.1260.5.1
	 * 
	 * TODO
	 *	- ͨ��dnf.exe��ȡ�汾��Ϣ
	 * 	- ͨ��.ini���ù�������/�ر�
	 * 
	 * */
	void DLL_Main(std::string exeType = "0627");
}