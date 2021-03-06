#include "stdafx.h"
#include <iostream>

int Operators3::available(OP op){
	if (op == JMP || op == RST || op == JSR)
		return 1;
	return 0;
}

int Operators3::next(){
	int isEnd = 1;
	MM_INT16* pMAR = cpuOpe.Register(MAR);
	MM_INT16* pPC = cpuOpe.Register(PC);
	MM_INT16* pRi = cpuOpe.Register(cpuOpe.getDRegister());
	MM_INT16* pMDR = cpuOpe.Register(MDR);
	MM_INT16* pC = cpuOpe.Register(C);
	MM_INT16* pSP = cpuOpe.Register(SP);
	AM method;
	method = cpuOpe.getDAM();
	if (cycle == 1){
		// FT周期
		// PC + 1 -> PC
		MM_INT16* pRegister = cpuOpe.Register(PC);
		assert(pRegister != NULL);
		(*pRegister).WORD += 2;
		MicroCommand[len] = "PC+1->PC";
		len++;
	}
	else if (cycle == 2){
		// ST周期
		// 只有JSR才有ST周期
		if (opr == JSR){
			// 转子条件和转移条件相同，这里用isNJP()判断是否为NJSP
			if (!isNJP()){
				// 只有JSR的才有ST周期的活动
				_WORD address;
				_WORD result;
				switch (method)
				{
				case R_1:
					// Ri->MAR
					(*pMAR).WORD = (*pRi).WORD;
					MicroCommand[len] = "Ri->MAR";
					len++;
					// M->MDR
					address.word = (*pMAR).WORD;
					if (Read(address, &result) == 1)
						exit(0);
					pMDR->STG = result.word;
					MicroCommand[len] = "M->MDR";
					len++;
					// MDR->C
					(*pC).WORD = (*pMDR).WORD;
					MicroCommand[len] = "MDR->C";
					len++;
					break;
				case R_3:
					// Ri -> MAR
					(*pMAR).WORD = (*pRi).WORD;
					MicroCommand[len] = "Ri->MAR";
					len++;
					// M->MDR
					address.word = (*pMAR).WORD;
					if (Read(address, &result) == 1)
						exit(0);
					pMDR->STG = result.word;
					MicroCommand[len] = "M->MDR";
					len++;
					// MDR->C
					(*pC).WORD = (*pMDR).WORD;
					MicroCommand[len] = "MDR->C";
					len++;
					// Ri + 1->Ri
					(*pRi).WORD++;
					MicroCommand[len] = "Ri+1->Ri";
					len++;
				default:
					break;
				}
			}
		}
		// DT周期
		// JMP, RST, JSR均无DT周期
		// 直接转到ET周期
		cycle++;
	}
	else if (cycle == 4){
		if (opr == JMP || opr == RST){
			
			if (isNJP()){
				if (isPC()){
					// PC->MAR
					(*pMAR).WORD = (*pPC).WORD;
					MicroCommand[len] = "PC->MAR";
					len++;
				}
				else {
					// PC + 1 -> PC
					(*pPC).WORD++;
					MicroCommand[len] = "PC+1->PC";
					len++;
					// PC->MAR
					(*pMAR).WORD = (*pPC).WORD;
					MicroCommand[len] = "PC->MAR";
					len++;
				}
			}
			else {
				_WORD address;
				switch (method)
				{
				case R_6:
					// PC + 1 ->PC
					(*pPC).WORD++;
					MicroCommand[len] = "PC+1->PC";
					len++;
					// PC->MAR
					(*pMAR).WORD = (*pPC).WORD;
					MicroCommand[len] = "PC->MAR";
					len++;
					break;
				case R_0:
					// Ri -> PC
					(*pPC).WORD = (*pRi).WORD;
					MicroCommand[len] = "Ri->PC";
					len++;
					// Ri->MAR
					(*pMAR).WORD = (*pRi).WORD;
					MicroCommand[len] = "Ri->MAR";
					len++;
					break;
				case R_1:
					// Ri->MAR
					(*pMAR).WORD = (*pRi).WORD;
					MicroCommand[len] = "Ri->MAR";
					len++;
					// M->MDR
					address.word = (*pMAR).WORD;
					_WORD result;
					if (Read(address, &result) == 1)
						exit(0);
					pMDR->STG = result.word;
					MicroCommand[len] = "M->MDR";
					len++;
					// MDR->PC
					(*pPC).WORD = (*pMDR).WORD;
					MicroCommand[len] = "MDR->PC";
					len++;
					// MDR->MAR
					(*pMAR).WORD = (*pMDR).WORD;
					MicroCommand[len] = "MDR->MAR";
					len++;
					break;
				case R_3:
					// Ri->MAR
					(*pMAR).WORD = (*pRi).WORD;
					MicroCommand[len] = "Ri->MAR";
					len++;
					// M->MDR
					address.word = (*pMAR).WORD;
					if (Read(address, &result) == 1)
						exit(0);
					pMDR->STG = result.word;
					MicroCommand[len] = "M->MDR";
					len++;
					// MDR->PC
					(*pPC).WORD = (*pMDR).WORD;
					MicroCommand[len] = "MDR->PC";
					len++;
					// MDR->MAR
					(*pMAR).WORD = (*pMDR).WORD;
					MicroCommand[len] = "MDR->MAR";
					len++;
					// Ri+1->Ri
					(*pRi).WORD++;
					MicroCommand[len] = "Ri+1->Ri";
					len++;
					break;
				case R_5:
					// PC->MAR
					(*pMAR).WORD = (*pPC).WORD;
					MicroCommand[len] = "PC->MAR";
					len++;
					// M->MDR
					address.word = (*pMAR).WORD;
					if (Read(address, &result) == 1)
						exit(0);
					pMDR->STG = result.word;
					MicroCommand[len] = "M->MDR";
					len++;
					// MDR->C
					(*pC).WORD = (*pMDR).WORD;
					MicroCommand[len] = "MDR->C";
					len++;
					// PC + C-> PC
					(*pPC).WORD += (*pC).WORD;
					MicroCommand[len] = "PC+C->PC";
					len++;
					// PC->MAR
					(*pMAR).WORD = (*pPC).WORD;
					MicroCommand[len] = "PC->MAR";
					len++;
					break;
				default:
					break;
				}
			}
		isEnd = 0;
		}
		else if (opr == JSR){
			if (isNJP()){
				if (isPC()){
					// PC + 1 -> PC
					(*pPC).WORD++;
					MicroCommand[len] = "PC+1->PC";
					len++;
					// PC->MAR
					(*pMAR).WORD = (*pPC).WORD;
					MicroCommand[len] = "PC->MAR";
					len++;
				}
				else {
					// PC->MAR
					(*pMAR).WORD = (*pPC).WORD;
					MicroCommand[len] = "PC->MAR";
					len++;
				}
			}
			else {
				_WORD address;
				_WORD value;
				switch (method)
				{
				case R_0:
					// SP-1 -> SP
					(*pSP).WORD--;
					MicroCommand[len] = "SP-1->SP";
					len++;
					// SP->MAR
					(*pMAR).WORD = (*pSP).WORD;
					MicroCommand[len] = "SP->MAR";
					len++;
					// PC->MDR
					(*pMDR).WORD = (*pPC).WORD;
					MicroCommand[len] = "PC->MDR";
					len++;
					// MDR -> M
					_WORD address;
					_WORD value;
					address.word = pMAR->STG;
					value.word = pMDR->STG;
					Write(address, &value);
					MicroCommand[len] = "MDR->M";
					len++;
					// Ri->PC
					(*pPC).WORD = (*pRi).WORD;
					MicroCommand[len] = "Ri->PC";
					len++;
					// Ri->MAR
					(*pMAR).WORD = (*pRi).WORD;
					MicroCommand[len] = "Ri->MAR";
					len++;
					break;
				case R_1:
				case R_3:
					// SP-1->SP
					(*pSP).WORD--;
					MicroCommand[len] = "SP-1->SP";
					len++;
					// SP->MAR
					(*pMAR).WORD = (*pSP).WORD;
					MicroCommand[len] = "SP->MAR";
					len++;
					// PC->MDR
					(*pMDR).WORD = (*pPC).WORD;
					MicroCommand[len] = "PC->MDR";
					len++;
					// MDR -> M
					address.word = pMAR->STG;
					value.word = pMDR->STG;
					Write(address, &value);
					MicroCommand[len] = "MDR->M";
					len++;
					// C->PC
					(*pPC).WORD = (*pC).WORD;
					MicroCommand[len] = "C->PC";
					len++;
					// C->MAR
					(*pMAR).WORD = (*pC).WORD;
					MicroCommand[len] = "C->MAR";
					len++;
				default:
					break;
				}
			}
		}
	}
	else{
	}

	ProcessorBase* p = static_cast<ProcessorBase*>(this);
	callback(p);
	cycle++;
	return isEnd;
}
void Operators3::execute() {
	cycle = 1;
	len = 0;
	opr = cpuOpe.getOPCode();
	/*for (int i = 0; i < 10; i++)
		MicroCommand[i] = "";*/
	next();
}
CPU_Cycle Operators3::getCurCPUCycle() {
	switch (cycle){
		case 1:
			return FT;
		case 2:
			return ST;
		case 3:
			return DT;
		case 4:
			return ET;
		default:
			return FT;
	}
}

const string* Operators3::getCurMicroCommand(int& length) {
	length = len;
	return MicroCommand;
}

int Operators3::getJMPCondition(){
	int i;
	i = cpuOpe.getSRegister();
	if(i==-1)
		i=0;
	return i % 16;
}
int Operators3::getJMP_IR5(){
	int r4, r5;
	int id;
	id = cpuOpe.getSRegister();
	r4 = id % 32;
	r5 = id % 64;
	return (r5 - r4) / 32;
}

bool Operators3::isPC(){
	return cpuOpe.getDRegister() != REGISTER_ERROR;
}

bool Operators3::isNJP() {
	int i;
	i = getJMPCondition();
	return i != 0 && i != 1 && i != 2 && i != 4 && i != 8;
}

