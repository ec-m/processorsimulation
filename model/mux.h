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
