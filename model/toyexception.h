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

#ifndef TOYEXCEPTION_H
#define TOYEXCEPTION_H
#include <exception>
#include <QString>
#include <QDebug>
#include "model/message.h"


/*
 * The class "ToyException" defines exception objects
 * specific for the parsing process.
 */

class ToyException : public std::exception
{
protected:
    // Attribute
    QString msg;

public:
    ToyException(QString msg);
    ~ToyException() throw() {};
    virtual const char *what() const throw()
    {
        return this->msg.toStdString().c_str();
    }
};

#endif // TOYEXCEPTION_H
