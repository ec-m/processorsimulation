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

#ifndef PC_H
#define PC_H
#include <QDebug>

// @author: Andreas Rist

class PC
{
public:

   PC();

   // sets Adress++
   // if Adress>4096 ==> 0
   void nextAdress();

   //sets the this->Adress to Adress necessary for View messegages
   //visit model->notify()for more information
   void setAdress(unsigned short Adress);
   unsigned short getAdress();

private:

    unsigned short Adress;
};

#endif // PC_H
