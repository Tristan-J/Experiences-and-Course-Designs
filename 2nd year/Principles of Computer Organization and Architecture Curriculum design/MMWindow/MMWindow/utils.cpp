#include "stdafx.h"
#include "utils.h"
#include <ctype.h>

void CEditAppend(char* buffer,CWnd* handle)
{
	CEdit* edit = (CEdit*)handle;
	int start,end;
	edit->GetSel(start,end);
	edit->SetSel(end+1,end+151);
	edit->ReplaceSel(_T(buffer));
	//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),buffer,20,NULL,NULL);
}

//numRow 一行显示的字的个数
void checkMemory(WORD address,int numWord,CWnd* handle,int numRow)
{	
	//AllocConsole();
	SetConsoleTitle("CheckMemory");

	_WORD addr;
	_WORD tmpAddr,tmpValue;
	char* buffer = new char[150];
	addr.word = address;
	CEdit* edit = (CEdit*)handle;

	sprintf_s(buffer,150,"Address			          Words		              Characters\n");CEditAppend(buffer,handle);
	sprintf_s(buffer,150,"--------------   -------------------------------------------------------------------------------	  ----------\n");CEditAppend(buffer,handle);
	for(;numWord>0;numWord-=numRow)
	{
		sprintf_s(buffer,150,"%.8X   ",addr.word);CEditAppend(buffer,handle);

		tmpAddr.word = addr.word;
		int i=0;
		for(i=0;i<numRow&&i<numWord;i++,tmpAddr.word+=2)
		{
			Read(tmpAddr,&tmpValue);
			sprintf_s(buffer,150,"%.4X ",tmpValue.word);CEditAppend(buffer,handle);
		}

		for(;i<numRow;i++)
		{
			sprintf_s(buffer,150,"        ");CEditAppend(buffer,handle);
		}
		sprintf_s(buffer,150,"   ");CEditAppend(buffer,handle);
		
		tmpAddr.word = addr.word;
		for(int i=0;i<numRow&&i<numWord;i++,tmpAddr.word+=2)
		{
			Read(tmpAddr,&tmpValue);
			if((0x20<=tmpValue.word)&&(tmpValue.word<=0x7e))
			{
				sprintf_s(buffer,150,"%c",tmpValue.word);CEditAppend(buffer,handle);
			}
			else
			{
				sprintf_s(buffer,150,".");CEditAppend(buffer,handle);
			}
		}

		sprintf_s(buffer,150,"\n");CEditAppend(buffer,handle);
		addr.word += 2*numRow;
	}

	delete[] buffer;
	//FreeConsole();
}

unsigned short atosx(char* str)
{
 return (unsigned short)atolx(str);
} 

unsigned long atolx(char* str)
{
 unsigned long var=0;
 unsigned long t;
 int len = strlen(str);
 
 if (var > 8) //最长8位
  return -1;
 strupr(str);//统一大写
 for (; *str; str++)
 {
  if (*str>='A' && *str <='F')
   t = *str-55;//a-f之间的ascii与对应数值相差55如'A'为65,65-55即为A
  else
   t = *str-48;
  var<<=4;
  var|=t;
 }
 return var;
} 

unsigned int BinToHex(char* str)
{
	unsigned int result = 0;
	int strLen = strlen(str)-1;
	while(*str!='\0')
	{
		result += ((*str)-'1'+1)*pow((double)2,strLen--);
		str++;
	}
	
	return result;
}