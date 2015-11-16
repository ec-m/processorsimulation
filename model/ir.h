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

#ifndef IR_H
#define IR_H
#include <QDebug>

// @author: Andreas Rist

class IR
{
public:

    IR();

    // Takes the Ram entry and speparates Opcode from Adress
    void runAndSet( unsigned short RamEntry);
    unsigned short getOpCode();
    unsigned short getAdress();

    //setOpcode and setAdress to change Values with Message
    //for more information visit model->notify()
    unsigned short setOpCode(unsigned short opCode);
    unsigned short setAdress(unsigned short adress);

private:

    unsigned short opCode;
    unsigned short adress;
};

#endif // IR_H
