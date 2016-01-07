#ifndef __PROCESSORBASE__
#define __PROCESSORBASE__

#include "CPUOperator.h"

class ProcessorBase
{
	protected:
		CPUOperator cpuOpe;
		/*CallBack(�ص�)˵��
		*�����Ǽ�ʱ֪ͨCPU
		*CPU::CallBack2 ԭ�Ͷ���: typedef void (*Cal lBack2)(ProcessorBase* pb);
		*����execute()�����а����·�ʽ����callback������this->callback(this);
		*Ҫ�󣺵���callbackʱ�Ѿ�����ͨ��getCurCPUCycle()��getCurMicroCommand()����ȡ��ǰ���ں�΢����
		*/
		typedef void (*CallBack2)(ProcessorBase* pb);
		CallBack2 _callback_;

		void callback(ProcessorBase* pb){cpuOpe.cpu->CallBackCPU(pb);}
	public:
		ProcessorBase(){};
		void setCallback(CallBack2 _callback){_callback_ = _callback;};
		virtual void execute()=0;//���ú�ʼ����΢����˺�����CPU����
		virtual CPU_Cycle getCurCPUCycle()=0;//��ȡ��ǰ��CPU���ڣ��˺�����CPU����
		virtual const string* getCurMicroCommand(int& len)=0;//��ȡ��ǰ���ڵ�΢�����string�����ţ��������鳤�ȸ�ֵ��len���˺�����CPU����
		virtual int available(OP op)=0;//OPΪָ��Ĳ������ͣ��˺�����CPU���á����Լ����ฺ������op����Ĳ������ͷ���1�����򷵻�0��
		virtual int next()=0;//ִ����һ�����ڵ�΢����,���ѽ����ͷ���0�����򷵻�1���˺�����CPU����
};

#endif