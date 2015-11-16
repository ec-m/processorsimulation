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

