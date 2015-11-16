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

#include "inifinitlooptest.h"

// @author: Andreas Ris

void Inifinitlooptest::countUp()
{
    count++;
    if(count==TEST_LENGTH){
        count=0;
        enableTesting =true;
    }
}

bool Inifinitlooptest::testIfLoop()
{
   if(enableTesting){
       if(lastOperation[1]==BRZ&&lastOperation[0]==ZRO){
           if(lastAdresses[0]==lastAdresses[2]&&lastOperation[0]==lastOperation[2]){
               return true;
           }
       }
   }
   return false;
}

Inifinitlooptest::Inifinitlooptest()
{
    count=0;
    enableTesting=false;
}

void Inifinitlooptest::insertAdressNOperation(short adress, short operation)
{
    lastAdresses[count]=adress;
    lastOperation[count]=operation;

    countUp();
}

