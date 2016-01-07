#pragma once
#include "ProcessorBase.h"

class Operators1 : public ProcessorBase{
	public:
		Operators1(){};
		//OP为指令的操作类型，此函数由CPU调用。若自己的类负责运行op代表的操作，就返回1，否则返回0。
		int available(OP op);
		int next();//执行下一个周期的微命令,若已结束就返回0，否则返回1，此函数由CPU调用
		void execute(); //调用后开始处理微命令，此函数由CPU调用
		CPU_Cycle getCurCPUCycle(); //获取当前的CPU周期，此函数由CPU调用
		const string* getCurMicroCommand(int& length); //获取当前周期的微命令，用string数组存放，并把数组长度赋值给len，此函数由CPU调用

	private:
		string MicroCommand[10];
		int len;
		int cycle;
		OP opr;

		string OP2String();
};
