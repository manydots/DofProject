#pragma once
#include <iostream>
#include "dof.h"


void FixPackage(std::string exeType);
void DisableBuyback(std::string exeType);

namespace Gamex
{
	//#define _v(v1,v2) ((v1|v2)<<8)
	//#define rgb(r,g,b) ((BYTE)r|_v((BYTE)g,_v((BYTE)b,0xFFFFFF00)))
	//#define rgba(r,g,b,a) ((BYTE)r|_v((BYTE)g,_v((BYTE)b,(BYTE)a<<8)))

	// exeType客户端类型 0627 0725 1031
	void InitDof(std::string exeType);
}