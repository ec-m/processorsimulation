#ifndef VARIABLE_H
#define VARIABLE_H
#include "model/row.h"

/*
 * The class "Variable" creates objects for lines with
 * a RAM-setting. In the constructor the given RAM-setting
 * string is split into address and value. The value is
 * stored in the "opCode"-field of class "Row", the address
 * in the additional attribute "place".
 * @author: Eva Charlotte Mayer
 */

class Variable : public Row
{
protected:
    // Attributes
    int place;

public:
    // Constructor
    Variable(QString line, int number, const FORMAT &format, const TYPE &type);

    // Getter
    int getPlace();
};

#endif // VARIABLE_H
