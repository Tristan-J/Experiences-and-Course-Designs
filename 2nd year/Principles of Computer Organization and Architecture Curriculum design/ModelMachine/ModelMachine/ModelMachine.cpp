// ModelMachine.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MainMemory.h"
#include "ProcessorBase.h"
#include "ProcessorBase2.h"
#include "operators3.h"
#include "CPU.h"
#include <iostream>
#include <string>

using namespace std;

CPU* _cpu;

void callback(CPU* cpu)
{
	int len;
	const string* str = cpu->getCurMicroCommand(len);
	for(int i=0;i<len;i++)
		cout<<"CPUOpe: "<<str[i]<<" , ";
	cout<<"Cycle: "<<cpu->getCPUCycle();
	cout<<endl;
	//_cpu->nextOp();
}

int _tmain(int argc, _TCHAR* argv[])
{
	_cpu = new CPU();

	ProcessorBase2 pb2;
	Operators3 pb3;

	_cpu->addPB(static_cast<ProcessorBase*>(&pb2));
	_cpu->addPB(static_cast<ProcessorBase*>(&pb3));

	_WORD tmp;
	tmp.word = 0xaa00;
	_WORD addr;
	addr.word = 0;
	Write(addr,&tmp);
	/*addr.word = 2;
	tmp.word = 0x8a00;
	Write(addr,&tmp);*/
	
	_cpu->CallBackShell = &callback;
	_cpu->prepare();
	_cpu->setDEBUG(true);
	_cpu->start();
	//_cpu->nextOp();

	cin>>tmp.word;

	return 0;
}

