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

#ifndef AKKU_H
#define AKKU_H
#include <QDebug>

// @author: Andreas Rist

class Akku
{
private:

    /*Has the value of the accu*/
    unsigned short value;

    /*determines if the accu is empty or not*/
    bool isZero;

public:

    Akku();

    /*returns the value of accu*/
    unsigned short getValue();

    /*sets the value of accu and determines if it is zero*/
    void setValue(unsigned short value);

    /*gives the bool isZero back*/
    bool isEmpty();
};

#endif // AKKU_H
