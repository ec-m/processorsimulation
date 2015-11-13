#include "model/modelram.h"

// @author: Andreas Rist

Modelram::Modelram()
{
    memory = new unsigned short[memLength];
}

void Modelram::setMemory(unsigned short adr, unsigned short value)
{
    this->memory[adr] = value;
}

void Modelram::setMemory(unsigned short value)
{
    this->memory[currentAdress]=value;
}

void Modelram::setCurrentAdress(unsigned short Adress)
{
    this->currentAdress=Adress;
}

unsigned short Modelram::getValue()
{
    return this->memory[currentAdress];
}

void Modelram::wirteRamTo(short adr)
{
    for (int i = 0; i <=adr ; ++i) {
        short adress=this->memory[i]& 0b111111111111;
        short opCode=this->memory[i]>> 12;
        qDebug()<< i <<": "<<"opcode: "<<opCode << "adress: " << adress;
    }
}

unsigned short* Modelram::copyRam()
{
    unsigned short* ramValue= new unsigned short[memLength];
    for (int i = 0; i < memLength; ++i) {
        ramValue[i]=this->getValue(i);

    }
    return  ramValue;
}

unsigned short Modelram::getValue(short adr)
{
    return this->memory[adr];
}

