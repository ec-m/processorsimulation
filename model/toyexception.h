#ifndef TOYEXCEPTION_H
#define TOYEXCEPTION_H
#include <exception>
#include <QString>
#include <QDebug>
#include "model/message.h"


/*
 * The class "ToyException" defines exception objects
 * specific for the parsing process.
 * @author: Eva Charlotte Mayer
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
