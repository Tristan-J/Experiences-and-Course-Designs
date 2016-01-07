#pragma once
#include "CPU.h"

/**
	CPUOperator提供对CPU的操作
	执行微命令的类请继承自ProcessorBase，并实现其虚函数，

*/
extern CPU* _cpu;

class CPUOperator
{
	public:
		CPU* cpu;
	public:

		//static void setCPU(CPU* _cpu){cpu = _cpu;}
		CPUOperator(){cpu = _cpu;}//this->cpu = CPU::getInstance();};
		OP getOPCode();//获取当前的操作指令类型

		MM_INT16* Register(REGISTER Register);//由寄存器编号获取寄存器存储单元

		/*
		*示例：其中 cpuOpe 为 CPUOperator的实例
		*如果要由当前操作指令获取目的地址寄存器中的内容，并将其置零:
		*	REGISTER regCode = cpuOpe.getDRegister();//目的地址寄存器编号
		*	MM_INT16* reg = cpuOpe.Register(regCode);//由编号获取寄存器的值 若没有此寄存器就返回NULL
		*	assert(reg!=NULL);//若无此寄存器则退出程序
		*	memset(reg,0,sizeof(MM_INT16));//将目的寄存器置零
		*/
		REGISTER getDRegister();//获取目的地址寄存器编号
		REGISTER getSRegister();//获取源地址寄存器编号

		AM getDAM();//获取目的地址寻址方式 若无返回AM_ERROR
		AM getSAM();//获取源地址寻址方式 若无返回AM_ERROR
};