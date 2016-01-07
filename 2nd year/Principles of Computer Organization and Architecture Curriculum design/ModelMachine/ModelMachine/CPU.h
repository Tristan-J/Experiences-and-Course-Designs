#ifndef __MODELMACHINE__
#define __MODELMACHINE__

#include <string>
#include <stddef.h>
#include <assert.h>
#include "BaseArgs.h"
#include "MainMemory.h"

class ProcessorBase;
using namespace std;

/*
*CPU类,单例模式
*存储CPU的各种信息，提供与CPU有关的操作
*/
class CPU
{
	private:
		MM_INT16 _MAR_,_MDR_,_IR_,_PC_,_SP_,_PSW_,_R0_,_R1_,_R2_,_R3_,_C_,_D_;//12个寄存器存储单元
		/*
		*调试模式下，cpu一次执行一条指令，调用next()执行下一周期动作，调用nextOp()执行下一条指令
		*/
		bool DEBUG;//是否为调试模式

		enum {PBNUM=3};
		ProcessorBase* PB[PBNUM];//3个微命令处理器
		int PBNum;//当前微命令处理器个数

		/*	CPU周期
		*
		*/
		CPU_Cycle curCycle;//CPU当前周期
		
		const string* microCommand;
		int microCommandLen;

		/*	CPU当前状态
		*	IDLE:得到cpu实例后，调用prepare()之前的状态,调用setIdle()即可重置cpu
		*	PREPARED:调用prepare()后，CPU完成准备
		*	RUNNING:调用start()或restart()后，cpu开始连续运行
		*	STOP:调用stop()后，cpu停止运行
		*
		*						PREPARED---start()--->RUNNING<------
		*						   /|\					|		   |
		*							|					|		   |
		*						prepare()			  stop()	restart()		
		*						   /|\					|		   |	
		*							|				   \|/		   |
		*	   entry-------------->IDLE<----setIdle()--STOP--------|
		*/
		CPU_Status status;

		void readIR();//从主存读取下一条指令

		MM_INT16* Register(REGISTER Register);//由寄存器编码获取寄存器存储单元

		OP getOPCode();//由指令寄存器_IR_中的信息获取当前指令的操作类型 OP枚举
		REGISTER getDRegister();//由指令寄存器_IR_中的信息获取当前指令的目的地址寄存器 若无返回REGISTER_ERROR枚举
		REGISTER getSRegister();//由指令寄存器_IR_中的信息获取当前指令的源地址寄存器 若无返回REGISTER_ERROR
		AM getDAM();//由指令寄存器_IR_中的信息获取当前指令的目的地址寻址方式 若无返回AM_ERROR
		AM getSAM();//由指令寄存器_IR_中的信息获取当前指令的源地址寻址方式 若无返回AM_ERROR
		void execute();//根据操作码和操作数执行指令

	public:
		//static CPU* cpu;//CPU实例
		CPU();//私有化构造函数，保证只有一个实例

		friend class CPUOperator;

		//static CPU* getInstance(){if(cpu==NULL)cpu = new CPU(); return cpu;};//获取CPU实例
		void setDEBUG(bool debug){this->DEBUG = debug;};//设置调试模式

		CPU_Cycle getCPUCycle();//获取CPU当期周期
		CPU_Status getCPUStatus();//获取CPU当前状态
		const string* getCurMicroCommand(int& len);//获取当前周期的微命令，用string数组存放，并把数组长度赋值给len
		const MM_INT16* getRegister(REGISTER Register);//获取寄存器值，由Shell调用
		int addPB(ProcessorBase* pb);//注册微命令处理器，失败返回0

		~CPU();

		/*
		*int prepare()
		*正常返回0
		*/
		int prepare();//初始化CPU，CPU完成准备， status置为PREPARED

		/*
		*int start()
		*正常返回0
		*/
		int start();//CPU开始连续运行 status置为RUNNING

		/*
		*int stop()
		*正常返回0
		*/
		int stop();//CPU暂停运行 status置为STOP

		/*
		*int restart()
		*正常返回0
		*/
		int restart();//CPU重新运行 status置为RUNNING，之前status需是STOP

		/*
		*int setIdle()
		*正常返回0
		*/
		int setIdle();//重置CPU，此时CPU处于调用prepare()之前的IDLE状态

		/*
		*int nextOp()
		*正常返回0
		*/
		void nextOp();//调试模式可用，执行下一条指令

		void dispose();

		/*
		*一级回调，由Shell赋予CPU调用
		*/
		typedef void (*CallBack1)(CPU* cpu);
		CallBack1 CallBackShell;

		/*
		*二级回调，由CPU赋予ProcessorBase调用 
		*/
		void CallBackCPU(ProcessorBase* pb);
};
#endif