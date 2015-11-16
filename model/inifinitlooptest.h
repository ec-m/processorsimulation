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

#ifndef INIFINITLOOPTEST_H
#define INIFINITLOOPTEST_H
#include <qdebug.h>

// @author: Andreas Rist

#define TEST_LENGTH 3
class Inifinitlooptest
{
private:

    //to insert in new file
    enum oCodes {STO=0,
                LDA=1,
                BRZ=2,
                ADD=3,
                SUB=4,
                OR=5,
                AND=6,
                XOR=7,
                NOT=8,
                INC=9,
                DEC=10,
                ZRO=11,
                NOP0=12,
                NOP1=13,
                NOP2=14,
                NOP3=15};

    /*
     * Here are saved the lastAdresses and lastOperations
     * of the Programm Simulated
     */
    unsigned short lastAdresses[TEST_LENGTH];
    unsigned short lastOperation[TEST_LENGTH];

    //Helps to insert the new ones
    unsigned short count;

    void countUp();

    //tests for infinie loop;
    bool enableTesting;

public:

    Inifinitlooptest();
    void insertAdressNOperation(short adress, short operation);
    bool testIfLoop();
};

#endif // INIFINITLOOPTEST_H
