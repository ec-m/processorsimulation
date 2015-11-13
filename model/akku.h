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
