#include "ir.h"

// @author: Andreas Rist

IR::IR()
{
}

void IR::runAndSet( unsigned short RamEntry)
{
    this->adress=RamEntry & 0b111111111111;
    this->opCode=RamEntry >> 12;
}

unsigned short IR::getOpCode()
{
    return opCode;
}

unsigned short IR::getAdress()
{
    return adress;
}

unsigned short IR::setOpCode(unsigned short opCode)
{
    this->opCode=opCode;
}

unsigned short IR::setAdress(unsigned short adress)
{
    this->adress=adress;
}

