/*
 * This file is part of Processorsimulation.
 * Author: Eva Charlotte Mayer <eva-charlotte.mayer@posteo.de>
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

#ifndef VARIABLE_H
#define VARIABLE_H
#include "model/row.h"

/*
 * The class "Variable" creates objects for lines with
 * a RAM-setting. In the constructor the given RAM-setting
 * string is split into address and value. The value is
 * stored in the "opCode"-field of class "Row", the address
 * in the additional attribute "place".
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
