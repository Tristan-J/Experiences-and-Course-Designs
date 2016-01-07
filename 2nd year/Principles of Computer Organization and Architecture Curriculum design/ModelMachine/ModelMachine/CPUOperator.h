#pragma once
#include "CPU.h"

/**
	CPUOperator�ṩ��CPU�Ĳ���
	ִ��΢���������̳���ProcessorBase����ʵ�����麯����

*/
extern CPU* _cpu;

class CPUOperator
{
	public:
		CPU* cpu;
	public:

		//static void setCPU(CPU* _cpu){cpu = _cpu;}
		CPUOperator(){cpu = _cpu;}//this->cpu = CPU::getInstance();};
		OP getOPCode();//��ȡ��ǰ�Ĳ���ָ������

		MM_INT16* Register(REGISTER Register);//�ɼĴ�����Ż�ȡ�Ĵ����洢��Ԫ

		/*
		*ʾ�������� cpuOpe Ϊ CPUOperator��ʵ��
		*���Ҫ�ɵ�ǰ����ָ���ȡĿ�ĵ�ַ�Ĵ����е����ݣ�����������:
		*	REGISTER regCode = cpuOpe.getDRegister();//Ŀ�ĵ�ַ�Ĵ������
		*	MM_INT16* reg = cpuOpe.Register(regCode);//�ɱ�Ż�ȡ�Ĵ�����ֵ ��û�д˼Ĵ����ͷ���NULL
		*	assert(reg!=NULL);//���޴˼Ĵ������˳�����
		*	memset(reg,0,sizeof(MM_INT16));//��Ŀ�ļĴ�������
		*/
		REGISTER getDRegister();//��ȡĿ�ĵ�ַ�Ĵ������
		REGISTER getSRegister();//��ȡԴ��ַ�Ĵ������

		AM getDAM();//��ȡĿ�ĵ�ַѰַ��ʽ ���޷���AM_ERROR
		AM getSAM();//��ȡԴ��ַѰַ��ʽ ���޷���AM_ERROR
};