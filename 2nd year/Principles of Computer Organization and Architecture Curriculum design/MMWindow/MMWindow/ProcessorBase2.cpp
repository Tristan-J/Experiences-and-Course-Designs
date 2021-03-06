#include "stdafx.h"

int ProcessorBase2::next()
{
	static int i = 0;
	//cout<<"Sub Step Index: "<<i++<<" CurCPUCycle: "<<CurCPUCycle<<endl;
    switch(CurCPUCycle)
    {
        case FT:
            CurCPUCycle = DT;
            execute();
            return 1;
        case DT:
            CurCPUCycle = ET;
            execute();
            return 1;
        case ET:
            CurCPUCycle = FT;
            return 0;
		default:
			return 0;
    }
}

const string* ProcessorBase2::getCurMicroCommand(int& len)
{
    len = LenOfArray;
    return CurMicroCommandArray;
}
int ProcessorBase2::available(OP op)
{
    op2=op;
	switch(op2)
    {
        case COM:
        case NEG:
        case INC:
        case DEC:
        case SL:
        case SR:
            return 1;
        default:
            return 0;
    }
}

void ProcessorBase2::execute()
  {
 	cout<<"OP: "<<op2<<endl;
     if(op2 == COM){
        com();
    }
    else if(op2 == NEG){
        neg();
    }
    else if(op2 == INC){
        inc();
    }
    else if(op2 == DEC){
        dec();
    }
    else if(op2 == SL){
        sl();
    }
    else if(op2 ==SR){
        sr();
    }
}

void ProcessorBase2::setCPUCycle(CPU_Cycle cycle)
{
    //设置CurMicroCommandArray和LenOfArray
	cout<<"DAM: "<<dam<<endl;
    if(CurCPUCycle == FT){
        CurMicroCommandArray[0] = "M->IR";
        CurMicroCommandArray[1] = "PC+1->PC";
        LenOfArray=2;
    }
    else if(CurCPUCycle == DT){
        if(dam == R_0){
            LenOfArray=0;
        }
        else if(dam == R_1){
            CurMicroCommandArray[0] = "Rj->MAR";
            CurMicroCommandArray[1] = "M->MDR->D";
            LenOfArray=2;
        }
        else if(dam == R_2){
            CurMicroCommandArray[0] = "Rj-1->Rj、MAR";
            CurMicroCommandArray[1] = "M->MDR->D";
            LenOfArray=2;
        }
        else if(dam == R_3){
            CurMicroCommandArray[0] = "Rj->MAR";
            CurMicroCommandArray[1] = "M->MDR->D";
            CurMicroCommandArray[2] = "Rj+1->Rj";
            LenOfArray=3;
        }
        else if(dam == R_4){
            CurMicroCommandArray[0] = "Rj->MAR";
            CurMicroCommandArray[1] = "M->MDR->D";
            CurMicroCommandArray[2] = "Rj+1->Rj";
            CurMicroCommandArray[3] = "D->MAR";
            CurMicroCommandArray[4] = "M->MDR->D";
            LenOfArray=5;
        }
        else if(dam == R_5){
            CurMicroCommandArray[0] = "PC->MAR";
            CurMicroCommandArray[1] = "M->MDR->D";
            CurMicroCommandArray[2] = "PC+1->PC";
            CurMicroCommandArray[3] = "D+Rj->MAR";
            CurMicroCommandArray[4] = "M->MDR->D";
            LenOfArray=5;
        }
    }
    else if(CurCPUCycle == ET){
        if(DR)
        {
            CurMicroCommandArray[0] = "OP Rj->Rj";
            CurMicroCommandArray[1] = "PC->MAR";
            LenOfArray=2;
        }
        else
        {
            CurMicroCommandArray[0] = "OP D->MDR";
            CurMicroCommandArray[1] = "MDR->M";
            CurMicroCommandArray[2] = "PC->MAR";
            LenOfArray=3;
        }
    }

}

CPU_Cycle ProcessorBase2::getCurCPUCycle()
{
    return CurCPUCycle;
}


void ProcessorBase2::ft()
{
    setCPUCycle(FT);
    //PC + 1 ->PC
    pPC = cpuOpe.Register(PC);
    (*pPC).WORD += 2;
	ProcessorBase* p = static_cast<ProcessorBase*>(this);
    callback(p);
}
void ProcessorBase2::dt()
{
	dam = cpuOpe.getSAM();//获取目的地址寻址方式
    setCPUCycle(DT);
    DR = 0;//标记为非寄存器寻址
    //获取Rj、MAR、D寄存器结构（联合）地址以便修改
    rRj = cpuOpe.getSRegister();
    pRj = cpuOpe.Register(rRj);
    assert(pRj!=NULL);
    pMAR = cpuOpe.Register(MAR);
    pMDR = cpuOpe.Register(MDR);
    pD = cpuOpe.Register(D);


    if(dam == R_0){
        DR = 1;//标记为寄存器寻址
    }
    else if(dam == R_1){
        D_R1();
    }
    else if(dam == R_2){
        D_R2();
    }
    else if(dam == R_3){
        D_R3();
    }
    else if(dam == R_4){
        D_R4();
    }
    else if(dam == R_5){
        D_R5();
    }
	ProcessorBase* p = static_cast<ProcessorBase*>(this);
    callback(p);
}
void ProcessorBase2::et2()
{
    //pMAR->WORD = pPC->WORD;
	ProcessorBase* p = static_cast<ProcessorBase*>(this);
    callback(p);
}
void ProcessorBase2::M_MDR_D()
{
    _WORD *paddress = reinterpret_cast<_WORD*>(pMAR);
	_WORD *value = reinterpret_cast<_WORD*>(pMDR);
	Read(*paddress,value);
    (*pD).WORD = (*pMDR).WORD;
}
void ProcessorBase2::Rj_MAR()
{
    (*pMAR).WORD = (*pRj).WORD;
}

void ProcessorBase2::D_R1()
{
    //ST0   Rj -> MAR
    Rj_MAR();
    //ST1   M -> MDR ->D
    M_MDR_D();
}
void ProcessorBase2::D_R2()
{
    //ST0   Rj-1 -> Rj、MAR
    (*pRj).WORD -= 2;
    Rj_MAR();
    //ST1   M -> MDR ->D
    M_MDR_D();
}
void ProcessorBase2::D_R3()
{
    //ST0   Rj -> MAR
    Rj_MAR();
    //ST1   M -> MDR ->D
    M_MDR_D();
    //ST2   Rj+1 -> Rj
    (*pRj).WORD += 2;
}
void ProcessorBase2::D_R4()
{
    //ST0   Rj -> MAR
    Rj_MAR();
    //ST1   M -> MDR ->D
    M_MDR_D();
    //ST2   Rj+1 -> Rj
    (*pRj).WORD += 2;
    //ST3   D -> MAR
    *pMAR = *pD;
    //ST4   M -> MDR ->D
    M_MDR_D();
}
void ProcessorBase2::D_R5()
{
    MM_INT16* pPC = cpuOpe.Register(PC);
    //ST0   PC -> MAR
    *pMAR = *pPC;
    //ST1   M -> MDR ->D
    M_MDR_D();
    //ST2   PC+1 -> PC
    (*pPC).WORD += 2;
    //ST3   D -> MAR
    *pMAR = *pD;
    //ST4   M -> MDR ->D
    M_MDR_D();
}
void ProcessorBase2::com()
{
     switch(CurCPUCycle)
    {
        case FT:
            ft();
            break;
        case DT:
            dt();
            break;
        case ET:
            setCPUCycle(ET);
            //寄存器寻址
            if(DR){
                //OP Rj -> Rj
                int i=(*pRj).WORD;
               // if( ( i&(1<<16) )==(1<<16) )//若为负数
                //{
                    i ^= (1<<16);//翻转符号位
                    i = ~i;//翻转每一位
                    (*pRj).WORD = i;
                //}
            }
            //非寄存器寻址
            else{
                //OP D -> MDR
                int i=(*pD).WORD;
               // if( ( i&(1<<16) )==(1<<16) )//若为负数
                //{
                    i ^= (1<<16);//翻转符号位
                    i = ~i;//翻转每一位
                    (*pMDR).WORD = i;
                //}
                //MDR -> M
                _WORD *paddress = reinterpret_cast<_WORD*>(pMAR);
				_WORD *value = reinterpret_cast<_WORD*>(pMDR);
                Write(*paddress,value);
            }
            et2();
            break;
    }
}
void ProcessorBase2::neg()
{
     switch(CurCPUCycle)
    {
        case FT:
            ft();
            break;
        case DT:
            dt();
            break;
        case ET:
            setCPUCycle(ET);
            //寄存器寻址
            if(DR){
                //OP Rj -> Rj
                int i=(*pRj).WORD;
                if( ( i&(1<<16) )==(1<<16) )//若为负数
                {
                    i ^= (1<<16);//翻转符号位
                    i = ~i;//翻转每一位
                    i++;//末位加一
                    (*pRj).WORD = i;
                }
            }
            //非寄存器寻址
            else{
                //OP D -> MDR
                int i=(*pD).WORD;
                if( ( i&(1<<16) )==(1<<16) )//若为负数
                {
                    i ^= (1<<16);//翻转符号位
                    i = ~i;//翻转每一位
                    i++;//末位加一
                    (*pMDR).WORD = i;
                }
                //MDR -> M
                _WORD *paddress = reinterpret_cast<_WORD*>(pMAR);
				_WORD *value = reinterpret_cast<_WORD*>(pMDR);
                Write(*paddress,value);
            }
            et2();
            break;
    }
}
void ProcessorBase2::inc()
{
	cout<<"CurCPUCycle: "<<CurCPUCycle<<endl;
     switch(CurCPUCycle)
    {
        case FT:
            ft();
			cout<<"FT\n";
            break;
        case DT:
			cout<<"DT\n";
            dt();
            break;
        case ET:
            setCPUCycle(ET);
            //寄存器寻址
            if(DR){
                //OP Rj -> Rj
                int i=(*pRj).WORD;
                i++;//加一
                (*pRj).WORD = i;
            }
            //非寄存器寻址
            else{
                //OP D -> MDR
                int i=(*pD).WORD;
                i++;//加一
                (*pMDR).WORD = i;
                //MDR -> M
                _WORD *paddress = reinterpret_cast<_WORD*>(pMAR);
				_WORD *value = reinterpret_cast<_WORD*>(pMDR);
                Write(*paddress,value);
            }
            et2();
            break;
    }
}
void ProcessorBase2::dec()
{
    switch(CurCPUCycle)
    {
        case FT:
            ft();
            break;
        case DT:
            dt();
            break;
        case ET:
            setCPUCycle(ET);
            //寄存器寻址
            if(DR){
                //OP Rj -> Rj
                int i=(*pRj).WORD;
                i--;//减一
                (*pRj).WORD = i;
            }
            //非寄存器寻址
            else{
                //OP D -> MDR
                int i=(*pD).WORD;
                i--;//减一
                (*pMDR).WORD = i;
                //MDR -> M
				_WORD *paddress = reinterpret_cast<_WORD*>(pMAR);
				_WORD *value = reinterpret_cast<_WORD*>(pMDR);
                Write(*paddress,value);
            }
            et2();
            break;
    }
}
void ProcessorBase2::sl()
{
    switch(CurCPUCycle)
    {
        case FT:
            ft();
            break;
        case DT:
            dt();
            break;
        case ET:
            setCPUCycle(ET);
            //寄存器寻址
            if(DR){
                //OP Rj -> Rj
                int i=(*pRj).WORD;
                i=i<<1;//左移一位
                (*pRj).WORD = i;
            }
            //非寄存器寻址
            else{
                //OP D -> MDR
                int i=(*pD).WORD;
                i=i<<1;//左移一位
                (*pMDR).WORD = i;
                //MDR -> M
				_WORD *paddress = reinterpret_cast<_WORD*>(pMAR);
				_WORD *value = reinterpret_cast<_WORD*>(pMDR);
                Write(*paddress,value);
            }
            et2();
            break;
    }
}
void ProcessorBase2::sr()
{
    switch(CurCPUCycle)
    {
        case FT:
            ft();
            break;
        case DT:
            dt();
            break;
        case ET:
            setCPUCycle(ET);
            //寄存器寻址
            if(DR){
                //OP Rj -> Rj
                int i=(*pRj).WORD;
                i=i>>1;//右移一位
                (*pRj).WORD = i;
            }
            //非寄存器寻址
            else{
                //OP D -> MDR
                int i=(*pD).WORD;
                i=i>>1;//右移一位
                (*pMDR).WORD = i;
                //MDR -> M
				_WORD *paddress = reinterpret_cast<_WORD*>(pMAR);
				_WORD *value = reinterpret_cast<_WORD*>(pMDR);
                Write(*paddress,value);
            }
            et2();
            break;
    }

}
