/*
 * This file is part of Processorsimulation.
 *
 * The Processorsimulation is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the Free
 * Software Foundation, Version 3.
 *
 * The Processorsimulation is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

