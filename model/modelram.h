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
