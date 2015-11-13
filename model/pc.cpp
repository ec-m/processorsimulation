#include "pc.h"

// @author: Andreas Rist

PC::PC()
{
    this->Adress=0;
}

void PC::nextAdress()
{
    Adress++;
    if((Adress & 0b1111000000000000)>0){
        Adress=0;

    }
}

void PC::setAdress(unsigned short Adress)
{
    this->Adress=Adress;
}

unsigned short PC::getAdress()
{
    return this->Adress;
}

