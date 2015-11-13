#include "variable.h"

// @author: Eva Charlotte Mayer

Variable::Variable(QString line, int number, const FORMAT &format, const TYPE &type) : Row(number, type)
{
    if (format == Row::binary)
    {
        QString address = line.mid(1,16);
        QString value = line.mid(18, 16);
        bool ok = false;
        this->place = address.toUShort(&ok, 2);
        this->opcode = value.toUShort(&ok, 2);
    }
    else if (format == Row::hexa)
    {
        QString address = line.mid(2, 4);
        QString value = line.mid(8, 4);
        bool ok = false;
        this->place = address.toUShort(&ok, 16);
        this->opcode = value.toUShort(&ok, 16);
    }
    else if (format == Row::mnemonic)
    {
        int indexOfSeparationPoint = line.indexOf((":"), 1);
        QString address = line.mid(1, indexOfSeparationPoint - 1);
        QString value = line.mid(indexOfSeparationPoint + 1, line.length());
        bool ok = false;
        this->place = address.toUShort(&ok, 10);
        this->opcode = value.toUShort(&ok, 10);
    }
}

int Variable::getPlace()
{
    return this->place;
}

