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

#include "akku.h"

// @author: Andreas Rist

Akku::Akku()
{
    this->value=0;
    this->isZero=true;

}

/**
 * @brief Akku::getValue
 * @return value of Akku
 */
unsigned short Akku::getValue()
{
    return this->value;
}

/**
 * @brief Akku::setValue
 * @param value short, is setted by this funktion
 * tests if value is 0 and sets flags
 */
void Akku::setValue(unsigned short value)
{
    if(value==0){
        isZero=true;
    }else{
        isZero=false;
    }
    this->value=value;
}

/**
 * @brief Akku::isEmpty
 * true =>  0
 * false => not 0
 */
bool Akku::isEmpty()
{
    return isZero;
}
