#include "stdafx.h"

CPU::CPU():DEBUG_(false),curCycle(FT),status(IDLE),PBNum(0)
{
	_MAR_.STG = 0;
	_MDR_.STG = 0;
	_IR_.STG = 0;
	_PC_.STG = 0;
	_SP_.STG = 0;
	_PSW_.STG = 0;
	_R0_.STG = 0;
	_R1_.STG = 0;
	_R2_.STG = 0;
	_R3_.STG = 0;
	_C_.STG = 0;
	_D_.STG = 0;
	InitMemory();
}

CPU::~CPU()
{}

void CPU::readIR()
{
	static _WORD addr,result;
	addr.word = _PC_.STG;
	Read(addr,&result);
	_IR_.STG = result.word;
	cout<<"IR: "<<_IR_.STG<<endl;
	//_PC_.STG = _PC_.STG + 2; 
}

MM_INT16* CPU::Register(REGISTER Register)
{
	switch(Register)
	{
		case MAR:
			return &_MAR_;
			break;
		case MDR:
			return &_MDR_;
			break;
		case IR:
			return &_IR_;
			break;
		case PC:
			return &_PC_;
			break;
		case SP:
			return &_SP_;
			break;
		case PSW:
			return &_PSW_;
			break;
		case R0:
			return &_R0_;
			break;
		case R1:
			return &_R1_;
			break;
		case R2:
			return &_R2_;
			break;
		case R3:
			return &_R3_;
			break;
		case C:
			return &_C_;
			break;
		case D:
			return &_D_;
			break;
		default:
			return NULL;
	}
}

//��Shell����
const MM_INT16* CPU::getRegister(REGISTER Register)
{
	return this->Register(Register);
}

OP CPU::getOPCode()
{
	unsigned char op = (_IR_.STG&61440)>>12;
	switch(op)
	{
		case 0:
			return MOV;
			break;
		case 1:
			return ADD;
			break;
		case 2:
			return SUB;
			break;
		case 3:
			return AND;
			break;
		case 4:
			return OR; 
			break;
		case 5:
			return EOR;
			break;
		case 6:
			return COM;
			break;
		case 7:
			return NEG;
			break;
		case 8:
			return INC;
			break;
		case 9:
			return DEC;
			break;
		case 10:
			return SL;
			break;
		case 11:
			return SR;
			break;
		case 12:
			return JMP;
			break;
		case 13:
			return RST;
			break;
		case 14:
			return JSR;
			break;
		default:
			return OP_ERROR;
	}
}

REGISTER CPU::getDRegister()
{
	unsigned char dr = (_IR_.STG&3584)>>9;
	switch(dr)
	{
		case 1:
			return PC;//1
			break;
		case 2:
			return SP;//10
			break;
		case 3:
			return PSW;//11
			break;
		case 4:
			return R0;//100
			break;
		case 5:
			return R1;//101
			break;
		case 6:
			return R2;//110
			break;
		case 7:
			return R3;//111
			break;
		default:
			return REGISTER_ERROR;
	}
}

REGISTER CPU::getSRegister()
{//R0,R1,R2,R3,SP,PSW,PC 为可编程寄存器
	unsigned char sr = (_IR_.STG&56)>>3;

	switch(sr)
	{
		case 1:
			return PC;//1
			break;
		case 2:
			return SP;//10
			break;
		case 3:
			return PSW;//11
			break;
		case 4:
			return R0;//100
			break;
		case 5:
			return R1;//101
			break;
		case 6:
			return R2;//110
			break;
		case 7:
			return R3;//111
			break;
		default:
			return REGISTER_ERROR;
	}
}

AM CPU::getDAM()
{
	unsigned char d= (_IR_.STG&448)>>6;
	switch(d)
	{
		case 0:
			return R_0;
			break;
		case 1:
			return R_1;
			break;
		case 2:
			return R_2;
			break;
		case 3:
			return R_3;
			break;
		case 4:
			return R_4;
			break;
		default:
			return AM_ERROR;
	}
}

AM CPU::getSAM()
{
	unsigned char s = (_IR_.STG&7);
	switch(s)
	{
		case 0:
			return R_0;
			break;
		case 1:
			return R_1;
			break;
		case 2:
			return R_2;
			break;
		case 3:
			return R_3;
			break;
		case 4:
			return R_4;
			break;
		default:
			return AM_ERROR;
	}
}

const string* CPU::getCurMicroCommand(int& len)
{
	len = this->microCommandLen;
	return this->microCommand;
}

void CPU::execute()
{
	int i = 0;
	static bool goOn;
	goOn = true;
	while(this->status==RUNNING&&goOn)
	{
		readIR();
		int avail = 0;
		for(;i<PBNum;i++)
		{
			avail = PB[i]->available(this->getOPCode());
 			if(avail)
			{
				PB[i]->execute();
				cout<<"END\n";
				//cout<<"Step OK: "<<i<<endl;
				//this->CallBackShell(this);//֪ͨShell
				if(this->DEBUG_)
				{
					goOn = false;
				}
				break;
			}
		}
		if(!avail)
		{
			cout<<"ERROR CODE\n";
			goOn = false;     
			//错误处理
			AfxMessageBox("错误指令",MB_OK);
		}
	}
}

void CPU::CallBackCPU(ProcessorBase* pb)
{
	static int i = 0;
	this->curCycle = pb->getCurCPUCycle();
	this->microCommand = pb->getCurMicroCommand(this->microCommandLen);
	this->CallBackShell(this,pb);

	cout<<"Sub Step OK: "<<i++<<endl;

	//readIR();
	if(!this->DEBUG_)
		if(pb->next()==0)
			return;
	return;
}

CPU_Cycle CPU::getCPUCycle()
{
	return this->curCycle;
}

CPU_Status CPU::getCPUStatus()
{
	return this->status;
}

int CPU::addPB(ProcessorBase* pb)
{
	if(PBNum<PBNUM)
	{
		PB[PBNum++] = pb;
		return 1;
	}
	return 0;
}

int CPU::prepare()
{
	if(this->status==IDLE)
	{
		this->status = PREPARED;
		int i = 0;
		for(;i<PBNum;i++)
		{
			//this->PB[i]->setCallback(&CallBackCPU);//
		}
		return 0;
	}
	else
	{
		return 1;
	}
}

int CPU::start()
{
	if(this->status==PREPARED)
	{
		this->status = RUNNING;
		this->execute();
		return 0;
	}
	else
	{
		return 1;
	}
}

int CPU::stop()
{
	if(this->status==RUNNING)
	{
		this->status = STOP;
		return 0;
	}
	else
	{
		return 1;
	}
}

int CPU::restart()
{
	if(this->status==STOP)
	{
		this->status = RUNNING;
		this->execute();
		return 0;
	}
	else
	{
		return 1;
	}
}

int CPU::setIdle()
{
	if(this->status==STOP)
	{
		this->status = IDLE;
		int i = 0;
		for(;i<PBNum;i++)
		{
			this->PB[i]->setCallback(NULL);
		}
		return 0;
	}
	else
	{
		return 1;
	}
}

void CPU::nextOp()
 {
	this->execute();
}

void CPU::dispose()
{
	//delete cpu;
}
