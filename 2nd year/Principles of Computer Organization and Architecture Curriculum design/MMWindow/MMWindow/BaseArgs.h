#pragma once
/*	寄存器类型编码
*	MAR:地址寄存器		MDR:数据寄存器
*	IR:指令寄存器		PC:程序计数器
*	SP:栈顶地址寄存器	PSW:状态字寄存器
*	R0:通用寄存器		R1:通用寄存器
*	R2:通用寄存器		R3:通用寄存器
*	C:暂存器			D:暂存器
*	
*	MAR,MDR,IR,C,D均不可通过CPU指令读取或写入 由CPU内部调用
*	R0,R1,R2,R3,SP,PSW,PC 为可编程寄存器
*/
typedef enum{REGISTER_ERROR=-1,PC=1,SP,PSW,R0,R1,R2,R3,C,D,MAR,MDR,IR} REGISTER;

/*	CPU周期
*	FT:取指周期		ST:源周期
*	DT:目的周期		ET:执行周期
*	DMAT:DMA周期	IT:中断周期
*/
typedef enum{FT=1,ST,DT,ET,DMAT,IT} CPU_Cycle;//CPU当前周期

/*	CPU当前状态
*/
typedef enum{IDLE=1,PREPARED,RUNNING,STOP} CPU_Status;

/*	寻址方式
*	R_0:寄存器寻址		R_1:寄存器间址
*	R_2:自减型间址		R_3:自增型间址
*	R_4:自增型双间址	R_5:变址寻址
*	R_6:跳步
*	PSW寄存器只适用于R_0型寻址方式
*	PC寄存器不适用于R_2型寻址方式
*	
*/
typedef enum{AM_ERROR=-1,R_0=0,R_1,R_2,R_3,R_4,R_5,R_6} AM;//Addressing Mode 

/*	操作码
*	MOV:传送	ADD:加
*	SUB:减		AND:与
*	OR:或		EOR:异或
*	COM:求反	NEG:求补
*	INC:加1		DEC:减1
*	SL:左移		SR:右移
*	JMP:转移	RST:返回
*	JSR:转子
*/
typedef enum{OP_ERROR=-1,MOV=0,ADD,SUB,AND,OR,EOR,COM,NEG,INC,DEC,SL,SR,JMP,RST,JSR}	OP;

/*
*	16位联合体,用于模拟CPU以及16位指令
	
	       ---- --- --- --- ---
	STG   | 4  | 3 | 3 | 3 | 3 |
	       ---- --- --- --- ---
		   S1   S2  S3  S4  S5
*/
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
		char S1:4;//第一存储块 4位
		char S2:3;//第二存储块 3位
		char S3:3;//第三存储块 3位
		char S4:3;//第四存储块 3位
		char S5:3;//第五存储块 3位
	}	DID;//独立分块
	*/
}	MM_INT16;

#define UnitLEN sizeof(MM_INT16)