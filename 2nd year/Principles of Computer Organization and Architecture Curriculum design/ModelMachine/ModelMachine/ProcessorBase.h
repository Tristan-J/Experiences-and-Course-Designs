#ifndef __PROCESSORBASE__
#define __PROCESSORBASE__

#include "CPUOperator.h"

class ProcessorBase
{
	protected:
		CPUOperator cpuOpe;
		/*CallBack(回调)说明
		*作用是及时通知CPU
		*CPU::CallBack2 原型定义: typedef void (*Cal lBack2)(ProcessorBase* pb);
		*请在execute()函数中按如下方式调用callback函数：this->callback(this);
		*要求：调用callback时已经可以通过getCurCPUCycle()和getCurMicroCommand()来获取当前周期和微命令
		*/
		typedef void (*CallBack2)(ProcessorBase* pb);
		CallBack2 _callback_;

		void callback(ProcessorBase* pb){cpuOpe.cpu->CallBackCPU(pb);}
	public:
		ProcessorBase(){};
		void setCallback(CallBack2 _callback){_callback_ = _callback;};
		virtual void execute()=0;//调用后开始处理微命令，此函数由CPU调用
		virtual CPU_Cycle getCurCPUCycle()=0;//获取当前的CPU周期，此函数由CPU调用
		virtual const string* getCurMicroCommand(int& len)=0;//获取当前周期的微命令，用string数组存放，并把数组长度赋值给len，此函数由CPU调用
		virtual int available(OP op)=0;//OP为指令的操作类型，此函数由CPU调用。若自己的类负责运行op代表的操作，就返回1，否则返回0。
		virtual int next()=0;//执行下一个周期的微命令,若已结束就返回0，否则返回1，此函数由CPU调用
};

#endif