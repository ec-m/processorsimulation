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

#ifndef MODELRAM_H
#define MODELRAM_H
#include <QDebug>

// @author: Andreas Rist

class Modelram
{
public:
    Modelram();

    /*
     * Sets Special Memory point at Adr with Value
     * void setMemory(unsigned short adr, unsigned short value);
     * Sets Value at currentAdress
     */
    void setMemory(unsigned short value);
    void setMemory(unsigned short adr, unsigned short value);
    void setCurrentAdress(unsigned short Adress);

    //sets special Adr
    unsigned short getValue(short adr);

    //gets memory[currentAdress]
    unsigned short getValue();

    //determines the memLength
    static const short memLength = 4096;

    //for debug reasons can print Ram to console memory[0]->memory[adr]
    void wirteRamTo(short adr);

    //gives a Copy from the Ram as Pointer
    unsigned short *copyRam();

private:

    //if you have to read this you have not understand nothing
    unsigned short currentAdress;
    unsigned short* memory;
};

#endif // MODELRAM_H
