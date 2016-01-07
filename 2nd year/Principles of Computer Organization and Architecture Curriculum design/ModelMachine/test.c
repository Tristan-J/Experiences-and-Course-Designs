#include <stdio.h>

typedef int (*funcType)(int,int);

int	add(int a,int b)
{
	return a+b;
} 

typedef union
{
	unsigned short STG;//整块16位
	unsigned short WORD;//寄存器 16位
	struct
	{
		unsigned char BYTE_L;//寄存器低8位
	 	unsigned char BYTE_H;//寄存器高8位
	} R;
	/*struct
	{
 		unsigned char S5:4;//第五存储块 3位   低 
		unsigned char S4:4;//第四存储块 3位    |		
		unsigned char S3:4;//第三存储块 3位	   | 
		unsigned char S2:4;//第二存储块 3位	   | 
		unsigned char S1:4;//第一存储块 4位	  高 
	}	DID;//独立分块
	*/
}	MM_INT16;

//1111 000 000 000 000 61440  (_PC_.STG&61440)>>12
//0000 111 000 000 000 3584	(_PC_.STG&3584)>>9
//0000 000 111 000 000 448	(_PC_.STG&448)>>6
//0000 000 000 111 000 56	(_PC_.STG&56)>>3
//0000 000 000 000 111 7	(_PC_.STG&7)
int main()
{
	funcType callback = &add;
	funcType funcAdd = callback;
	
	MM_INT16 _PC_;
	_PC_.STG = 448;
	
	printf("%.4X\n",(_PC_.STG&448)>>6);
	
	return 0;
}
