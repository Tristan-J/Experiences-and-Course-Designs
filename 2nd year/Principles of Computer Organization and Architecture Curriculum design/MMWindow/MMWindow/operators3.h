#ifndef OPERATORS3_H
#define OPERATORS3_H
#include "ProcessorBase.h"

class Operators3 : public ProcessorBase{
	public:
		Operators3(){};
		//OP为指令的操作类型，此函数由CPU调用。若自己的类负责运行op代表的操作，就返回1，否则返回0。
		int available(OP op);
		int next();//执行下一个周期的微命令,若已结束就返回0，否则返回1，此函数由CPU调用
		void execute();//调用后开始处理微命令，此函数由CPU调用
		CPU_Cycle getCurCPUCycle();//获取当前的CPU周期，此函数由CPU调用
		const string* getCurMicroCommand(int& len);//获取当前周期的微命令，用string数组存放，并把数组长度赋值给len，此函数由CPU调用
	private:
		string MicroCommand[10];
		int len;
		int cycle;
		OP opr;

		// 得到转移指令的后四位，即N' Z' V' C'的转移条件
		int getJMPCondition();
		// 得到转移指令的第五位IR5
		int getJMP_IR5();
		// 得到转移指令的9~11位,即PC,判断是PC'还是PC
		bool isPC();
		// 判断是否符合转移条件，转移成功
		bool isNJP();
		
};
#endif