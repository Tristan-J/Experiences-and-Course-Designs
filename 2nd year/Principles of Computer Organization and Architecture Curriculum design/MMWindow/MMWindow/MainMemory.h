/**
 *	主存模拟程序，即模拟DMA控制器的功能，包括显存与输入缓冲
 *	一个存储单元为一个字节
 *	功能:
 *		读：由地址返回相应的值 ，一次读取两个字节
 *		写：由地址与所给的值写入主存 ， 一次写入两个字节
 *		填充输入缓冲：接受输入字符，并填充进输入缓冲存储单元中
 *		显示字符：显示显存中的字符
 *		填充程序：由所给的文件指针读取文件数据，并将数据填充进主存的指定单元，所给文件均以二进制方式读取
 *		边界错误判断：若所给地址超过存储空间的边界，应不响应此操作
 *
 *	外存总量：64KByte(65536Byte)
 *	主存大小：56KByte(57344Byte)  0~57343
 *	显存大小：4KByte (4096Byte)	  57344~61439
 *	输入缓冲大小：4KByte (4096Byte) 61440~65535
 *
 *	0__主存__0xDFFF|0xE000___显存___0xEFFF|0xF000__输入缓冲__0xFFFF 
**/

/**
 *	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1!!!需要注意的!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *		因为模型机寄存器为16位，并且只能16位一起同时操作，不能分开以8位为单位单独
 *	操作，即不能单独操作模型机寄存器的高8位或低8位，所以这给单独读取一字节数据造成
 *	了困难，为了解决这个问题，专门构造一个将1字节数据包装为2字节数据的操作:_WORD ByteWrap(BYTE),
 *	此操作接受一个一字节数据，将其包装后返回一个两字节数据，但其值不变。
 *	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  *	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1!!!需要注意的!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *		涉及操作Memory的，给Memory赋值统一使用memset，用变量或数组给Memory赋值统一使用memcpy
 *	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**/
#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <stddef.h>
#include <windows.h>

#define MAX_LEN_OF_MEMORY 65536
#define MIN_MEMORY 0
#define MAX_MEMORY (MAX_LEN_OF_MEMORY-1)
#define MIN_MAIN_MEMORY 0
#define MAX_MAIN_MEMORY 57343
#define MIN_VIDEO_MEMORY 57344
#define MAX_VIDEO_MEMORY 61439
#define MIN_INPUT_BUFFER 61440
#define MAX_INPUT_BUFFER 65535

typedef unsigned char BYTE;//一字节数据

//_WORD 为主存，显存，输入缓冲的存储单元
typedef union
{
	unsigned short word;
	struct
	{
		unsigned char BYTE_H;//高8位
		unsigned char BYTE_L;//低8位
	}	BYTE;

}	_WORD;

void InitMemory();

/*
	字节包装函数,将一字节数据包装成为两字节数据，值不变
*/
_WORD ByteWrap(BYTE byte);

/*
	取值操作
	address:地址，取值范围0~65535，从Memory+address开始两个字节，包括Memory+address
	result:从address开始的两字节数据,参考库函数 void *memcpy(void *dest, const void *src, size_t n);
	备注：若address超出其取值范围，则不响应此操作，赋result为NULL
	出错返回1，成功返回0
*/
int Read(_WORD address,_WORD* result);

/*
	赋值操作
	address:地址，取值范围0~65535，从Memory+address开始两个字节，包括Memory+address
	value:要赋给主存相应单元的值，参考库函数 memcpy
	备注：若address超出其取值范围，则不响应此操作
	注意：若写入的地址段为显存的地址段，写入后，要调用Display函数重新显示显存中的内容
*/
void Write(_WORD address,_WORD* value);

/*
	接受用户输入，填充输入缓冲，可接受的输入类型有：short(2字节)
	地址范围：61440~65535
	len:读取len个短整形
*/
void FillInputBuffer(int len);

/*
	显示显存中的内容 25行 80列 4000字节 2000字符
	地址范围：57344~61439
	注意：显存头两个字节（57344,57345），为状态字，第一位决定下一个数据的显示方式， 为0则从显存中读取所有数据，显示为字符型（c）；若为1,则从显存中读取所有数据，显示为整形（d），
		  若为字符显示模式，则高字节存放字符编码，低字节存放字符属性
*/
void Display();

/*
	清空显存,之后调用Display
	地址范围：57344~61439
*/
void ClearVideoMemory();


/*
	清空输入缓冲
	地址范围：61440~65535
*/
void ClearInputBuffer();


/*
	清空主存,之后调用Display
	地址范围：0~57343
*/
void ClearMainMemory();

/*
	清空主存，显存，输入缓冲
	地址范围：0-65535
*/
void ClearMemory();

/*
	从pFile中读取数据放入主存中
	address:放入数据的地址，若为NULL，则从0地址处开始放置数据
	地址范围：0~57343,若文件大小超过了主存的57344字节，则只将文件的前57344字节写入主存
	正常返回0，出错返回1
*/
int LoadAPP(_WORD* address,char* filename);

