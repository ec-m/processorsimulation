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

