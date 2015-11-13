#include "mux.h"

// @author: Andreas Rist

MUX::MUX()
{
    this->Adress=0;
}

short MUX::getAdress()
{
    return this->Adress;
}

short MUX::decide(short IRValue, short PcValue, bool addrIR)
{
  if(addrIR){
    this->Adress =IRValue;
  }else{
      this->Adress=PcValue;
  }
  return this->Adress;
}

