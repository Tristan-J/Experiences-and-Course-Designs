#include "stdafx.h"
#include "MainMemory.h"

BYTE Memory[MAX_LEN_OF_MEMORY];//主存(0~57343)，显存(57344~61439)，以及输入缓冲(61440~65535),每个单元为两字节 _WORD

void InitMemory()
{
	memset(Memory,0,MAX_LEN_OF_MEMORY);
}

_WORD ByteWrap(BYTE byte)
{
	_WORD Dst;
	memset(&Dst,0,sizeof(_WORD));
	memcpy(&Dst,&byte,sizeof(BYTE));
	return Dst;
}

int Read(_WORD address,_WORD* result)
{
	if(address.word<MIN_MEMORY||address.word>MAX_MEMORY)
	{
		return 1;
	}

	result->BYTE.BYTE_H = Memory[address.word];
	result->BYTE.BYTE_L = Memory[address.word+1];
	return 0;
}

void Write(_WORD address,_WORD* value)
{
	if(address.word<MIN_MEMORY||address.word>MAX_MEMORY)
	{
		return;
	}

	Memory[address.word] = value->BYTE.BYTE_H;
	Memory[address.word+1] = value->BYTE.BYTE_L;

	if(address.word>=MIN_VIDEO_MEMORY&&address.word<=MAX_VIDEO_MEMORY)
	{
		Display();
	}
}

void FillInputBuffer(int len)
{
	_WORD tmp;
	int begin = MIN_INPUT_BUFFER;
	while(len-->0)
	{
		std::cin>>tmp.word;
		Memory[begin++] = tmp.BYTE.BYTE_H;
		Memory[begin++] = tmp.BYTE.BYTE_L;
	}
}

void Display()
{
	_WORD status;
	_WORD tmp;
	int count = 0;
	status.BYTE.BYTE_H = Memory[MIN_VIDEO_MEMORY];
	status.BYTE.BYTE_L = Memory[MIN_VIDEO_MEMORY+1];
	if(status.word == 0)
	{
		for(count;count<4000;count+=2)
		{
			HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hCon,Memory[MIN_VIDEO_MEMORY+3+count]);
			printf("%c",Memory[MIN_VIDEO_MEMORY+2+count]);
		}
	}
	else if(status.word == 1)
	{
		for(count;count<4000;count+=2)
		{
			tmp.BYTE.BYTE_H = Memory[MIN_VIDEO_MEMORY+2+count];
			tmp.BYTE.BYTE_L = Memory[MIN_VIDEO_MEMORY+3+count];
			printf("%d",tmp.word);
		}
	}
}

void ClearVideoMemory()
{
	memset(Memory+MIN_VIDEO_MEMORY,0,MAX_VIDEO_MEMORY-MIN_VIDEO_MEMORY+1);
}

void ClearInputBuffer()
{
	memset(Memory+MIN_INPUT_BUFFER,0,MAX_INPUT_BUFFER-MIN_INPUT_BUFFER+1);
}

void ClearMainMemory()
{
	memset(Memory+MIN_MEMORY,0,MAX_MAIN_MEMORY-MIN_MAIN_MEMORY+1);
}

void ClearMemory()
{
	memset(Memory,0,MAX_LEN_OF_MEMORY);
}

int LoadAPP(_WORD* address,char* filename)
{
	_WORD tmp;
	if(address==NULL)
		tmp.word = 0;
	else
		tmp.word = address->word;

	int filesize;
	std::ifstream fin(filename,std::ios::in|std::ios::binary);
	if(!fin.good())
		return -1;
	fin.seekg(0,std::ios::end);
	filesize = (int)fin.tellg()-1;//去除文件尾
	fin.seekg(0,std::ios::beg);
	if(filesize>(MAX_MAIN_MEMORY-MIN_MAIN_MEMORY+1-tmp.word))
		filesize = MAX_MAIN_MEMORY-MIN_MAIN_MEMORY+1-tmp.word;
	fin.read(reinterpret_cast<char*>(Memory+tmp.word),filesize);
	return filesize;
}