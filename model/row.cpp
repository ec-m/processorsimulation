#include "row.h"

// @author: Eva Charlotte Mayer

Row::Row(QString line, int number, const FORMAT &format, const TYPE &type) : type(type)
{
    this->number = number;
    bool ok = false;
    switch (format)
    {
    case Row::binary :
        this->opcode = line.toUShort(&ok, 2);
        break;
    case Row::hexa :
        this->opcode = line.toUShort(&ok, 16);
        break;
    case Row::mnemonic :
        this->opcode = convertMnemonic(line);
        break;
    }
}

Row::Row(int number, const TYPE &type) : type(type)
{
    this->number = number;
}

int Row::getNumber()
{
    return this->number;
}

short Row::getOpcode()
{
    return this->opcode;
}

Row::TYPE Row::getType()
{
    return this->type;
}

// Converts Mnemonicstring into an unsigned short by
// first translating it into a hexa string and then
// returning the ushort value of that string.
ushort Row::convertMnemonic(QString s)
{
    QString addressHex;
    //For all commands that include RAM address
    if(s.length() > 3)
    {
        QRegExp rx("\\d{1,2}");
        int indexOfAddress = s.indexOf(rx, 0);
        QString address = s.right(s.length() - indexOfAddress);
        bool ok = false;
        addressHex = QString::number(address.toInt(&ok, 10), 16);

        while(addressHex.length() < 3)
        {
            addressHex.insert(0, "0");
        }

    }
    else
    {
        addressHex = "000";
    }

    QString commandHex;
    if(s.startsWith("STO"))
    {
        commandHex = "0";
    }
    if(s.startsWith("LDA"))
    {
        commandHex = "1";
    }
    if(s.startsWith("BRZ"))
    {
        commandHex = "2";
    }
    if(s.startsWith("ADD"))
    {
        commandHex = "3";
    }
    if(s.startsWith("SUB"))
    {
        commandHex = "4";
    }
    if(s.startsWith("OR"))
    {
        commandHex = "5";
    }
    if(s.startsWith("AND"))
    {
        commandHex = "6";
    }
    if(s.startsWith("XOR"))
    {
        commandHex = "7";
    }
    if(s.startsWith("NOT"))
    {
        commandHex = "8";
    }
    if(s.startsWith("INC"))
    {
        commandHex = "9";
    }
    if(s.startsWith("DEC"))
    {
        commandHex = "A";
    }
    if(s.startsWith("ZRO"))
    {
        commandHex = "B";
    }

    s = commandHex.append(addressHex);
    bool ok = false;
    return s.toUShort(&ok, 16);
}


QString Row::showAsBin()
{
    QString res = QString::number(this->opcode, 2);
    while(res.length() < 16)
    {
        res.insert(0, "0");
    }
    if(res.length() > 16)
    {
        res = res.right(16);
    }
    return res;
}

QString Row::showAsHexa()
{
    // Convert to binary and cut into address and command
    QString s = showAsBin();
    QString command = s.left(4);
    QString address = s.right(12);

    // Convert command and address into hexadecimals
    // and combine them into one string
    bool ok = false;
    QString res = QString::number(address.toUShort(&ok,2), 16);
    while(res.length() < 3)
    {
        res.insert(0, "0");
    }
    res.insert(0, QString::number(command.toUShort(&ok, 2), 16));

    return res;
}

QString Row::showAsMnemonic()
{
    // Receive string as hexadecimal
    // and find according command
    QString s = showAsHexa();
    QString command;
    if(s.startsWith("0"))
    {
        command = "STO";
    }
    if(s.startsWith("1"))
    {
        command = "LDA";
    }
    if(s.startsWith("2"))
    {
        command = "BRZ";
    }
    if(s.startsWith("3"))
    {
        command = "ADD";
    }
    if(s.startsWith("4"))
    {
        command = "SUB";
    }
    if(s.startsWith("5"))
    {
        command = "OR";
    }
    if(s.startsWith("6"))
    {
        command = "AND";
    }
    if(s.startsWith("7"))
    {
        command = "XOR";
    }
    if(s.startsWith("8"))
    {
        return "NOT";
    }
    if(s.startsWith("9"))
    {
        return "INC";
    }
    if(s.startsWith("a"))
    {
        return "DEC";
    }
    if(s.startsWith("b"))
    {
        return "ZRO";
    }

    // Convert address and append command and address
    bool ok = false;
    QString address = QString::number(s.right(3).toUShort(&ok, 16), 10);
    QString res = command.append(address);

    return res;
}

int Row::getPlace()
{
    return -1;
}
