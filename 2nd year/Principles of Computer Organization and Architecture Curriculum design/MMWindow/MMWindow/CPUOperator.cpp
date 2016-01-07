#include "stdafx.h"


//CPUOperator
OP CPUOperator::getOPCode()
{
	return this->cpu->getOPCode();
}

MM_INT16* CPUOperator::Register(REGISTER Register){
	return this->cpu->Register(Register);
}

REGISTER CPUOperator::getDRegister()
{
	return this->cpu->getDRegister();
}

REGISTER CPUOperator::getSRegister()
{
	return this->cpu->getSRegister();
}

AM CPUOperator::getDAM()
{
	return this->cpu->getDAM();
}

AM CPUOperator::getSAM()
{
	return this->cpu->getSAM();
}
