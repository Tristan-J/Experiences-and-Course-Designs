#pragma once

#include "stdafx.h"
#include "MainMemory.h"
#include <string>
#include <cstdio>
#include <math.h>

using namespace std;

void checkMemory(WORD address,int numWord,CWnd* handle,int numRow=8);
void CEditAppend(char* buffer,CWnd* handle);
unsigned short atosx(char* str);
unsigned long atolx(char* str);//ʮ�������ַ���תulong
unsigned int BinToHex(char* str);//������תʮ����