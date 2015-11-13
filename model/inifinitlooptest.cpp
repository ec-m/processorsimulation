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

