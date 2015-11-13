#ifndef CONTROLLUNIT_H
#define CONTROLLUNIT_H
#include <QBitArray>
#include <QDebug>

// @author: Andreas Rist

/*
 * With these defines the programm determines the flags
 *of the Controllunit (Steuerwerk)
 */
#define FLAGS_STO_0 0b100100011111
#define FLAGS_STO_1 0b010010000000
#define FLAGS_LDA_0 0b000101011010
#define FLAGS_LDA_1 0b010010000000
#define FLAGS_BRZ_0 0b001100000000
#define FLAGS_BRZ_1 0b010010000000
#define FLAGS_ADD_0 0b000101001001
#define FLAGS_ADD_1 0b010010000000
#define FLAGS_SUB_0 0b000101100110
#define FLAGS_SUB_1 0b010010000000
#define FLAGS_OR_0  0b000101011110
#define FLAGS_OR_1  0b010010000000
#define FLAGS_AND_0 0b000101011011
#define FLAGS_AND_1 0b010010000000
#define FLAGS_XOR_0 0b000101010110
#define FLAGS_XOR_1 0b010010000000
#define FLAGS_NOT_0 0b010011010000
#define FLAGS_NOT_1 0b010010000000
#define FLAGS_INC_0 0b010011100000
#define FLAGS_INC_1 0b010010000000
#define FLAGS_DEC_0 0b010011001111
#define FLAGS_DEC_1 0b010010000000
#define FLAGS_ZRO_0 0b010011010011
#define FLAGS_ZRO_1 0b010010000000
#define FLAGS_NOP_0 0b010010000000
#define FLAGS_NOP_1 0b000000000000
#define FLAG_LENGTH 12 //defines the Flagarray length

class ControllUnit
{
public:
    ControllUnit();

    /* setter for opCode */
    void setOpCode(unsigned short opCode);

    /*
     * chooes from opCode and phase the korrekt flag and calls refresh(short IntFlagList)
     */
    void refreshFlags(short phase);

    /* sets all flags to false */
    void defaultFalgs();

    /*
     *makes from the 4 Flags alu3, alu2, alu1 and alu0
     *and makes an unsigned short number from it
     */
    unsigned short getALU3210();

    /*
     * gets the Flag for the  model.* realy necessary
     */
    bool getFlag(short Flag);


private:

    //Boolean array for the flags
    bool flag[FLAG_LENGTH];

    unsigned short opCode;

    //Enum for Flagarray numbers are in Korrekt Order for View
    enum falgs {writeRam=0,
                incPC=1,
                setPC=2,
                addrIR=3,
                setIR=4,
                setAccu=5,
                aluCIn=6,
                aluMode=7,
                alu3=8,
                alu2=9,
                alu1=10,
                alu0=11};

    //operation code enumeration to make your an my life easier :) :*
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

    //Takes a definition from above and refreshes the array
    void refresh(short IntFlagList);

};

#endif // CONTROLLUNIT_H
