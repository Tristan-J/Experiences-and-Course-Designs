#pragma once
#include "ProcessorBase.h"
#define MAX_OF_CurMicroCommandArray 5

class ProcessorBase2:public ProcessorBase
{
private:
    CPU_Cycle CurCPUCycle;//当前CPU周期
    string CurMicroCommandArray[MAX_OF_CurMicroCommandArray];//当前周期的操作名称string数组，随周期改变而改变
    int LenOfArray;//当前周期的操作名称string数组长度
    int DR;//标记是否为寄存器寻址
    //一些变量
    AM dam;//存放目的寻址方式
    REGISTER rRj;
    MM_INT16* pRj,*pMAR,*pMDR,*pD,*pPC;
	OP op2;


    void setCPUCycle(CPU_Cycle cycle);//进入到新CPU周期设置当前周期相关信息

    //处理指令
    void com();
    void neg();
    void inc();
    void dec();
    void sl();
    void sr();

    //处理寻址方式
/*
*	R_0:寄存器寻址		R_1:寄存器间址
*	R_2:自减型间址		R_3:自增型间址
*	R_4:自增型双间址	R_5:变址寻址
*	R_6:跳步
*	PSW寄存器只适用于R_0型寻址方式
*	PC寄存器不适用于R_2型寻址方式
*
*/
    //DT 部分
    void D_R1();
    void D_R2();
    void D_R3();
    void D_R4();
    void D_R5();

    //CPU周期
    void ft();//仅执行PC+1->PC
    void dt();
    void et2();//仅执行PC->MAR
    //一些操作
    void M_MDR_D();//M -> MDR ->D
    void Rj_MAR();//Rj -> MAR

public:
    void execute();//调用后开始处理微命令，此函数由CPU调用
    CPU_Cycle getCurCPUCycle();//获取当前的CPU周期，此函数由CPU调用
	const string* getCurMicroCommand(int& len);//获取当前周期的微命令，用string数组存放，并把数组长度赋值给len，此函数由CPU调用
	int available(OP op);//OP为指令的操作类型，此函数由CPU调用。若自己的类负责运行op代表的操作，就返回1，否则返回0。
	int next();//执行下一个周期的微命令,若已结束就返回0，否则返回1，此函数由CPU调用
	ProcessorBase2(){CurCPUCycle = FT;}

};
