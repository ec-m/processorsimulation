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
