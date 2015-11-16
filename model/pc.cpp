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

#include "pc.h"

// @author: Andreas Rist

PC::PC()
{
    this->Adress=0;
}

void PC::nextAdress()
{
    Adress++;
    if((Adress & 0b1111000000000000)>0){
        Adress=0;

    }
}

void PC::setAdress(unsigned short Adress)
{
    this->Adress=Adress;
}

unsigned short PC::getAdress()
{
    return this->Adress;
}

