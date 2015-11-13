#include "model/toyexception.h"

// @author: Eva Charlotte Mayer

ToyException::ToyException(QString msg)
{
    this->msg = msg;
    this->msg.append(".\n The programm will reset to the last valid state.");
}
