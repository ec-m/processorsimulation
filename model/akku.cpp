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
