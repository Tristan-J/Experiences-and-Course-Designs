#include "stdafx.h"
#include <iostream>
#include "operators1.h"

int Operators1::available(OP op){
	if (op == MOV || op == ADD|| op == SUB || op == AND || op == OR || op == EOR)
		return 1;
	return 0;
}

int Operators1::next() {
	int isEnd = 1;
	len = 0;
	MM_INT16* pMAR = cpuOpe.Register(MAR);
	MM_INT16* pRi = cpuOpe.Register(cpuOpe.getSRegister());
	MM_INT16* pRj = cpuOpe.Register(cpuOpe.getDRegister());
	MM_INT16* pC = cpuOpe.Register(C);
	MM_INT16* pD = cpuOpe.Register(D);
	MM_INT16* pMDR = cpuOpe.Register(MDR);
	MM_INT16* pPC = cpuOpe.Register(PC);
	AM Dmethod, Smethod;
	Smethod = cpuOpe.getSAM();
	Dmethod = cpuOpe.getDAM();
	switch (cycle){
	case 1:{
		// FT周期
		// PC + 1 -> PC
		MM_INT16* pRegister = cpuOpe.Register(PC);
		(*pRegister).WORD += 2;
		MicroCommand[len] = "PC+1->PC";
		len++;
		}
		break;
	case 2:{
		// ST周期

		 _WORD address;
		 _WORD result;
		 switch (Smethod){
		 case R_1:
			 // (R)
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
		 case R_2:
			 // -(R)
			 // Ri-1 ->Ri 
			 pRi->WORD--;
			 MicroCommand[len] = "Ri-1->Ri";
			 len++;
			 // Ri->MAR
			 pMAR->WORD = pRi->WORD;
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
			 // I/(R)+
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
			 // Ri+1->Ri
			 pRi->WORD++;
			 MicroCommand[len] = "Ri+1->Ri";
			 len++;
			 break;
		 case R_4:
			 // @/(R)+
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
			 // Ri+1->Ri
			 pRi->WORD++;
			 MicroCommand[len] = "Ri+1->Ri";
			 len++;
			 // C->MAR
			 pMAR->WORD = pC->WORD;
			 MicroCommand[len] = "C->MAR";
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
		 case R_5:
			 // X(R)
			 // PC->MAR
			 pMAR->WORD = pPC->WORD;
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
			 // PC+1->PC
			 pPC->WORD++;
			 MicroCommand[len] = "PC+1->PC";
			 len++;
			 // C+Ri->MAR
			 pMAR->WORD = pC->WORD + pRi->WORD;
			 MicroCommand[len] = "C+Ri->MAR";
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
		 default:
			 break;
   	     }
		 break;
	}
	case 3:{
		 _WORD address;
		 _WORD result;
		if (opr == MOV){
			switch (Dmethod){
			case R_1:
				// (R)
				// Rj->MAR
				pMAR->WORD = pRj->WORD;
				MicroCommand[len] = "Rj->MAR";
			    len++;
				break;
			case R_2:
				// -(R)
				// Rj-1->Rj
				pRj->WORD--;
				MicroCommand[len] = "Rj-1->Rj";
			    len++;
				// Rj->MAR
				pMAR->WORD = pRj->WORD;
				MicroCommand[len] = "Rj->MAR";
			    len++;
				break;
			case R_3:
				// (R)+
				// Rj->MAR
				pMAR->WORD = pRj->WORD;
				MicroCommand[len] = "Rj->MAR";
			    len++;
				// Rj+1->Rj
				pRj->WORD++;
				MicroCommand[len] = "Rj+1->Rj";
			    len++;
				break;
			case R_4:
				// @(R)+
				// Rj->MAR
				pMAR->WORD = pRj->WORD;
				MicroCommand[len] = "Rj->MAR";
			    len++;
				// Rj+1->Rj
				pRj->WORD++;
				MicroCommand[len] = "Rj+1->Rj";
			    len++;
				// M->MDR
				address.word = (*pMAR).WORD;
			    if (Read(address, &result) == 1)
			 	  exit(0);
			    pMDR->STG = result.word;
			    MicroCommand[len] = "M->MDR";
			    len++;
				// MDR->MAR
				pMAR->WORD = pMDR->WORD;
			    MicroCommand[len] = "MDR->MAR";
			    len++;
				break;
			case R_5:
				// X(R)
				// PC->MAR
				pMAR->WORD = pPC->WORD;
			    MicroCommand[len] = "PC->MAR";
			    len++;
				// PC+1->PC
				pPC->WORD++;
			    MicroCommand[len] = "PC-1->PC";
			    len++;
				// M->MDR
				address.word = (*pMAR).WORD;
			    if (Read(address, &result) == 1)
			 	  exit(0);
			    pMDR->STG = result.word;
			    MicroCommand[len] = "M->MDR";
			    len++;
				// MDR->D
				pD->WORD = pMDR->WORD;
			    MicroCommand[len] = "MDR->D";
			    len++;
				// D+Rj->MAR
				pMAR->WORD = pD->WORD + pRj->WORD;
			    MicroCommand[len] = "D+Rj->MAR";
			    len++;
				break;
			default:
				break;
			}
		}
		else {
			switch (Dmethod){
			case R_1:
				// (R)
				// Rj->MAR
				pMAR->WORD = pRj->WORD;
				MicroCommand[len] = "Rj->MAR";
			    len++;
				// M->MDR
				address.word = (*pMAR).WORD;
			    if (Read(address, &result) == 1)
			 	  exit(0);
			    pMDR->STG = result.word;
			    MicroCommand[len] = "M->MDR";
			    len++;
				// MDR->D
				pD->WORD = pMDR->WORD;
			    MicroCommand[len] = "MDR->D";
			    len++;
				break;
			case R_2:
				// -(R)
				// Rj-1->Rj
				pRj->WORD--;
				MicroCommand[len] = "Rj-1->Rj";
			    len++;
				// Rj->MAR
				pMAR->WORD = pRj->WORD;
				MicroCommand[len] = "Rj->MAR";
			    len++;
				// M->MDR
				address.word = (*pMAR).WORD;
			    if (Read(address, &result) == 1)
			 	  exit(0);
			    pMDR->STG = result.word;
			    MicroCommand[len] = "M->MDR";
			    len++;
				// MDR->D
				pD->WORD = pMDR->WORD;
			    MicroCommand[len] = "MDR->D";
			    len++;
				break;
			case R_3:
				// (R)+
				// Rj->MAR
				pMAR->WORD = pRj->WORD;
				MicroCommand[len] = "Rj->MAR";
			    len++;
				// M->MDR
				address.word = (*pMAR).WORD;
			    if (Read(address, &result) == 1)
			 	  exit(0);
			    pMDR->STG = result.word;
			    MicroCommand[len] = "M->MDR";
			    len++;
				// MDR->D
				pD->WORD = pMDR->WORD;
			    MicroCommand[len] = "MDR->D";
			    len++;
				// Rj+1->Rj
				pRj->WORD++;
				MicroCommand[len] = "Rj+1->Rj";
			    len++;
				break;
			case R_4:
				// @(R)+
				// Rj->MAR
				pMAR->WORD = pRj->WORD;
				MicroCommand[len] = "Rj->MAR";
			    len++;
				// M->MDR
				address.word = (*pMAR).WORD;
			    if (Read(address, &result) == 1)
			 	  exit(0);
			    pMDR->STG = result.word;
			    MicroCommand[len] = "M->MDR";
			    len++;
				// MDR->D
				pD->WORD = pMDR->WORD;
			    MicroCommand[len] = "MDR->D";
			    len++;
				// Rj+1->Rj
				pRj->WORD++;
				MicroCommand[len] = "Rj+1->Rj";
			    len++;
				// D->MAR
				pMAR->WORD = pD->WORD;
				MicroCommand[len] = "D->MAR";
			    len++;
				// M->MDR
				address.word = (*pMAR).WORD;
			    if (Read(address, &result) == 1)
			 	  exit(0);
			    pMDR->STG = result.word;
			    MicroCommand[len] = "M->MDR";
			    len++;
				// MDR->D
				pD->WORD = pMDR->WORD;
			    MicroCommand[len] = "MDR->D";
			    len++;
				break;
			case R_5:
				// X(R)
				// PC->MAR
				pMAR->WORD = pPC->WORD;
			    MicroCommand[len] = "PC->MAR";
			    len++;
				// M->MDR
				address.word = (*pMAR).WORD;
			    if (Read(address, &result) == 1)
			 	  exit(0);
			    pMDR->STG = result.word;
			    MicroCommand[len] = "M->MDR";
			    len++;
				// MDR->D
				pD->WORD = pMDR->WORD;
			    MicroCommand[len] = "MDR->D";
			    len++;
				// PC+1->PC
				pPC->WORD++;
			    MicroCommand[len] = "PC-1->PC";
			    len++;
				// D+Rj->MAR
				pMAR->WORD = pD->WORD + pRj->WORD;
			    MicroCommand[len] = "D+Rj->MAR";
			    len++;
				// M->MDR
				address.word = (*pMAR).WORD;
			    if (Read(address, &result) == 1)
			 	  exit(0);
			    pMDR->STG = result.word;
			    MicroCommand[len] = "M->MDR";
			    len++;
				// MDR->D
				pD->WORD = pMDR->WORD;
			    MicroCommand[len] = "MDR->D";
			    len++;
				break;
			default:
				break;
			}
		}
		break;
	}
	case 4:{
		_WORD address;
		_WORD value;
		if (opr == MOV){
			if (Smethod == R_0 && Dmethod == R_0){
				// SR, DR
				// Ri->Rj
				pRj->WORD = pRi->WORD;
			    MicroCommand[len] = "Ri->Rj";
			    len++;
			}
			else if (Smethod == R_0 && Dmethod != R_0){
				// SR, DR'
				// Ri->MDR
				pMDR->WORD = pRi->WORD;
			    MicroCommand[len] = "Ri->MDR";
			    len++;
				// MDR->M
				address.word = pMAR->STG;
				value.word = pMDR->STG;
				Write(address, &value);
				MicroCommand[len] = "MDR->M";
				len++;
			}
			else if (Smethod != R_0 && Dmethod == R_0){
				// SR', DR
				// C->Rj
				pRj->WORD = pC->WORD;
				MicroCommand[len] = "C->Rj";
				len++;
			}
			else if (Smethod != R_0 && Dmethod != R_0){
				// SR', DR'
				// C->MDR
				pMDR->WORD = pC->WORD;
				MicroCommand[len] = "C->MDR";
				len++;
				// MDR->M
				address.word = pMAR->STG;
				value.word = pMDR->STG;
				Write(address, &value);
				MicroCommand[len] = "MDR->M";
				len++;
			}
     	}
		else{
			if (Smethod == R_0 && Dmethod == R_0){
				// SR, DR
				// RiOPRj->Rj
				switch (opr)
				{
				case ADD:
					pRj->WORD += pRi->WORD;
					MicroCommand[len] = "RiADDRj->Rj";
					len++;
					break;
				case SUB:
					pRj->WORD = pRj->WORD - pRi->WORD;
					MicroCommand[len] = "RiSUBRj->Rj";
					len++;
					break;
				case AND:
					pRj->WORD = pRi->WORD & pRj->WORD;
					MicroCommand[len] = "RiANDRj->Rj";
					len++;
					break;
				case OR:
					pRj->WORD = pRi->WORD | pRj->WORD;
					MicroCommand[len] = "RiORRj->Rj";
					len++;
					break;
				case EOR:
					pRj->WORD = pRi->WORD ^ pRj->WORD;
					MicroCommand[len] = "RiEORRj->Rj";
					len++;
				default:
					break;
				}
			}
			else if (Smethod == R_0 && Dmethod != R_0){
				// SR, DR'
				// RiOPD->MDR
				switch (opr)
				{
				case ADD:
					pMDR->WORD = pRi->WORD + pD->WORD;
					MicroCommand[len] = "RiADDD->MDR";
					len++;
					break;
				case SUB:
					pMDR->WORD = pD->WORD - pRi->WORD;
					MicroCommand[len] = "RiSUBD->MDR";
					len++;
					break;
				case AND:
					pMDR->WORD = pRi->WORD & pD->WORD;
					MicroCommand[len] = "RiANDD->MDR";
					len++;
					break;
				case OR:
					pMDR->WORD = pRi->WORD | pD->WORD;
					MicroCommand[len] = "RiORD->MDR";
					len++;
					break;
				case EOR:
					pMDR->WORD = pRi->WORD ^ pMDR->WORD;
					MicroCommand[len] = "RiEORD->MDR";
					len++;
				default:
					break;
				}
				// MDR->M
				address.word = pMAR->STG;
				value.word = pMDR->STG;
				Write(address, &value);
				MicroCommand[len] = "MDR->M";
				len++;
			}
			else if (Smethod != R_0 && Dmethod == R_0){
				// SR', DR
				// C OP Rj->Rj
				switch (opr)
				{
				case ADD:
					pRj->WORD += pC->WORD;
					MicroCommand[len] = "CADDRj->Rj";
					len++;
					break;
				case SUB:
					pRj->WORD = pRj->WORD - pC->WORD;
					MicroCommand[len] = "CSUBRj->Rj";
					len++;
					break;
				case AND:
					pRj->WORD = pC->WORD & pRj->WORD;
					MicroCommand[len] = "CANDRj->Rj";
					len++;
					break;
				case OR:
					pRj->WORD = pC->WORD | pRj->WORD;
					MicroCommand[len] = "CORRj->Rj";
					len++;
					break;
				case EOR:
					pRj->WORD = pC->WORD ^ pRj->WORD;
					MicroCommand[len] = "CEORRj->Rj";
					len++;
				default:
					break;
				}
			}
			else if (Smethod != R_0 && Dmethod != R_0){
				// SR', DR'
				// C OP D->MDR
				switch (opr)
				{
				case ADD:
					pMDR->WORD = pC->WORD + pD->WORD;
					MicroCommand[len] = "CADDD->MDR";
					len++;
					break;
				case SUB:
					pMDR->WORD = pC->WORD - pD->WORD;
					MicroCommand[len] = "CSUBD->MDR";
					len++;
					break;
				case AND:
					pMDR->WORD = pC->WORD & pD->WORD;
					MicroCommand[len] = "CANDD->MDR";
					len++;
					break;
				case OR:
					pMDR->WORD = pC->WORD | pD->WORD;
					MicroCommand[len] = "CORD->MDR";
					len++;
					break;
				case EOR:
					pMDR->WORD = pC->WORD ^ pMDR->WORD;
					MicroCommand[len] = "CEORD->MDR";
					len++;
				default:
					break;
				}
				// MDR->M
				address.word = pMAR->STG;
				value.word = pMDR->STG;
				Write(address, &value);
				MicroCommand[len] = "MDR->M";
				len++;
			}
		}
		// PC->MAR
		pMAR->WORD = pPC->WORD;
		MicroCommand[len] = "PC->MAR";
		len++;
		isEnd = 0;
		break;
	}
		
	}
	//cycle++;
	ProcessorBase* p = static_cast<ProcessorBase*>(this);
	callback(p);
	cycle++;
	return isEnd;
}

void Operators1::execute() {
	cycle = 1;
	len = 0;
	opr = cpuOpe.getOPCode();
	next();
}

CPU_Cycle Operators1::getCurCPUCycle() {
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

const string* Operators1::getCurMicroCommand(int& length) {
	length = len;
	return MicroCommand;
}

string Operators1::OP2String(){
	switch (opr){
	case ADD:
		return "ADD";
	case SUB:
		return "SUB";
	case AND:
		return "AND";
	case OR:
		return "OR";
	case EOR:
		return "EOR";
	default:
		return "";
	}
}