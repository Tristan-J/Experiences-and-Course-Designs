#include <stdio.h>

typedef int (*funcType)(int,int);

int	add(int a,int b)
{
	return a+b;
} 

typedef union
{
	unsigned short STG;//����16λ
	unsigned short WORD;//�Ĵ��� 16λ
	struct
	{
		unsigned char BYTE_L;//�Ĵ�����8λ
	 	unsigned char BYTE_H;//�Ĵ�����8λ
	} R;
	/*struct
	{
 		unsigned char S5:4;//����洢�� 3λ   �� 
		unsigned char S4:4;//���Ĵ洢�� 3λ    |		
		unsigned char S3:4;//�����洢�� 3λ	   | 
		unsigned char S2:4;//�ڶ��洢�� 3λ	   | 
		unsigned char S1:4;//��һ�洢�� 4λ	  �� 
	}	DID;//�����ֿ�
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
