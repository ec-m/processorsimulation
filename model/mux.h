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

#ifndef MUX_H
#define MUX_H
#include <QDebug>

// @author: Andreas Rist

class MUX
{
public:

    MUX();

    //Makes the choosing by flag Addr=IR
    short decide(short IRValue, short PcValue, bool addrIR);

    //gives the Adress
    short getAdress();

private:

    short Adress; //Adress which has had been decided
};

#endif // MUX_H
