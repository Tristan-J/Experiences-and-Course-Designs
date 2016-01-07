#pragma once
/*	�Ĵ������ͱ���
*	MAR:��ַ�Ĵ���		MDR:���ݼĴ���
*	IR:ָ��Ĵ���		PC:���������
*	SP:ջ����ַ�Ĵ���	PSW:״̬�ּĴ���
*	R0:ͨ�üĴ���		R1:ͨ�üĴ���
*	R2:ͨ�üĴ���		R3:ͨ�üĴ���
*	C:�ݴ���			D:�ݴ���
*	
*	MAR,MDR,IR,C,D������ͨ��CPUָ���ȡ��д�� ��CPU�ڲ�����
*	R0,R1,R2,R3,SP,PSW,PC Ϊ�ɱ�̼Ĵ���
*/
typedef enum{REGISTER_ERROR=-1,PC=1,SP,PSW,R0,R1,R2,R3,C,D,MAR,MDR,IR} REGISTER;

/*	CPU����
*	FT:ȡָ����		ST:Դ����
*	DT:Ŀ������		ET:ִ������
*	DMAT:DMA����	IT:�ж�����
*/
typedef enum{FT=1,ST,DT,ET,DMAT,IT} CPU_Cycle;//CPU��ǰ����

/*	CPU��ǰ״̬
*/
typedef enum{IDLE=1,PREPARED,RUNNING,STOP} CPU_Status;

/*	Ѱַ��ʽ
*	R_0:�Ĵ���Ѱַ		R_1:�Ĵ�����ַ
*	R_2:�Լ��ͼ�ַ		R_3:�����ͼ�ַ
*	R_4:������˫��ַ	R_5:��ַѰַ
*	R_6:����
*	PSW�Ĵ���ֻ������R_0��Ѱַ��ʽ
*	PC�Ĵ�����������R_2��Ѱַ��ʽ
*	
*/
typedef enum{AM_ERROR=-1,R_0=0,R_1,R_2,R_3,R_4,R_5,R_6} AM;//Addressing Mode 

/*	������
*	MOV:����	ADD:��
*	SUB:��		AND:��
*	OR:��		EOR:���
*	COM:��	NEG:��
*	INC:��1		DEC:��1
*	SL:����		SR:����
*	JMP:ת��	RST:����
*	JSR:ת��
*/
typedef enum{OP_ERROR=-1,MOV=0,ADD,SUB,AND,OR,EOR,COM,NEG,INC,DEC,SL,SR,JMP,RST,JSR}	OP;

/*
*	16λ������,����ģ��CPU�Լ�16λָ��
	
	       ---- --- --- --- ---
	STG   | 4  | 3 | 3 | 3 | 3 |
	       ---- --- --- --- ---
		   S1   S2  S3  S4  S5
*/
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
		char S1:4;//��һ�洢�� 4λ
		char S2:3;//�ڶ��洢�� 3λ
		char S3:3;//�����洢�� 3λ
		char S4:3;//���Ĵ洢�� 3λ
		char S5:3;//����洢�� 3λ
	}	DID;//�����ֿ�
	*/
}	MM_INT16;

#define UnitLEN sizeof(MM_INT16)