#pragma once
#include <iostream>
#include "dof.h"


namespace Gamex
{
	//#define _v(v1,v2) ((v1|v2)<<8)
	//#define rgb(r,g,b) ((BYTE)r|_v((BYTE)g,_v((BYTE)b,0xFFFFFF00)))
	//#define rgba(r,g,b,a) ((BYTE)r|_v((BYTE)g,_v((BYTE)b,(BYTE)a<<8)))

	/**
	 *
	 * exeType�ͻ������� 0627 0725 1031
	 * dnf.exe�汾
	 * 0627  1.180.2.1
	 * 0725  1.200.4.1
	 * 1031  1.260.5.1
	 *
	 *	- ͨ��dnf.exe��ȡ�汾��Ϣ
	 * 	- ͨ��.ini���ù�������/�ر�
	 *
	 * */
	void DLL_Main();

	void FixPackage(std::string exeType);
	void DisableBuyback(std::string exeType);
	void SetClipboardData(std::string exeType);
	void FixLetterText(std::string exeType);
	void FreeZoomRate(std::string exeType);
	void FixItemPosCMD(std::string exeType);
	void FixGMofMail(std::string exeType);
	void ShowSkillName(std::string exeType);
	void DisableOtherWinMin(std::string exeType);
	void FixLordTower(std::string exeType);
	void FixCharacterName(std::string exeType);
	void CreateCreatorMage(std::string exeType);
	void LocalGM_Mode(std::string exeType);
	void OverloadNPC_Color(std::string exeType, std::string NPC_Color);
	void OverloadCharacter_Color(std::string exeType, std::string NPC_Color);
}