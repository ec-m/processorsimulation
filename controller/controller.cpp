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

#include "controller.h"
#include <QDebug>

/*
 * Important:
 * When updating the PC value, the opcode and address of the IR,
 * such as accu and RAM values, the GUI sends the current modus
 * with the message. The modus is the way, in which the numbers
 * are portrayed currently - decimal, binary, hexadecimal or as
 * assembly. It is important to remember this modus when checking
 * the values the user inserted.
 *
 * Modus:
 * 0 = decimal
 * 1 = binary
 * 2 = hexadecimal
 * 3 = mnemonic
 */

Controller::Controller(QObject *parent) : QObject(parent)
{
    this->ok = false;
}

void Controller::notify(Message &msg)
{
    switch(msg.type)
    {
    // From GUI to Model: msg.content is set to path from file that user opens
    case Message::FileOpen :
    {
        checkFileOpen(msg);
        break;
    }
        // From GUI to Model: msg.content contains the user input for a new PC value
    case Message::UserInputPC :
    {
        checkUserInputPC(msg);
        break;
    }
        // From GUI to Model: msg.content contains the user input for a new OpCode value in the IR
    case Message::UserInputOpCode :
    {
        checkUserInputOpCode(msg);
        break;
    }
        // From GUI to Model: msg.content contains the user input for a new address value in the IR
    case Message::UserInputAddress :
    {
        checkUserInputAddress(msg);
        break;
    }
        // From GUI to Model: msg.content contains the user input for a new Accu value
    case Message::UserInputAccu :
    {
        checkUserInputAccu(msg);
        break;
    }
        // From GUI to Model: msg.content contains the user input for a new RAM value and RAM cell number
    case Message::UserInputRAM :
    {
        checkUserInputRAM(msg);
        break;
    }
        // no content - simply calls method "step"
    case Message::SingleStep :
    {
        emit(sendMessage(msg));
        break;
    }
    case Message::HalfCycle :
    {
        emit(sendMessage(msg));
        break;
    }
    case Message::Cycle :
    {
        emit(sendMessage(msg));
        break;
    }
    case Message::Automatic :
    {
        emit(sendMessage(msg));
        break;
    }
        // no content - model resets itself with old parser array
    case Message::Reset :
    {
        emit(sendMessage(msg));
        break;
    }
        //no content - model stops automode and all other modes
    case Message::Stop :
    {
        emit(sendMessage(msg));
        break;
    }
    case Message::Speed :
    {
        emit(sendMessage(msg));
        break;
    }
        // all other messages get sent directly from the Model to the GUI
    default:
        break;
    }
    this->ok = false;
}

void Controller::checkFileOpen(Message &msg)
{
    QString* content = (QString*) msg.content;
    // Checks if content contains valid path to a file and not a directory
    QFileInfo checkFile((QString) *content);
    if (checkFile.exists() && checkFile.isFile()) {
        emit(sendMessage(msg));
    }
}

void Controller::checkUserInputPC(Message &msg)
{
    ushort value = convertMsgContent(msg);

    // If conversion error occures, value is set to -1, if conversion succeeds, convertMsgContent returns new value
    if(this->ok && value < 4096)
    {
        // Forward msg to Model
        Message msg(Message::UserInputPC);
        msg.content= &value;
        emit(sendMessage(msg));
    }
    else
    {
        // From Controller to GUI: if user input was wrong
        Message msg(Message::WrongInputPC);
        emit(sendMessage(msg));
    }


}

void Controller::checkUserInputOpCode(Message &msg)
{
    ushort value = convertMsgContent(msg);

    // If conversion error occures, value is set to -1, if conversion succeeds, convertMsgContent returns new value
    if(this->ok && value < 16)
    {
        // Forward msg to Model
        Message msg(Message::UserInputOpCode);
        msg.content = &value;
        emit(sendMessage(msg));
    }
    else
    {
        // From Controller to GUI: if user input was wrong
        Message msg(Message::WrongInputOpCode);
        emit(sendMessage(msg));
    }
}

void Controller::checkUserInputAddress(Message &msg)
{
    ushort value = convertMsgContent(msg);

    // If conversion error occures, value is set to -1, if conversion succeeds, convertMsgContent returns new value
    if(this->ok && value < 4096)
    {
        // Forward msg to Model
        Message msg(Message::UserInputAddress);
        msg.content= &value;
        emit(sendMessage(msg));
    }
    else
    {
        // From Controller to GUI: if user input was wrong
        Message msg(Message::WrongInputAddress);
        emit(sendMessage(msg));
    }
}

void Controller::checkUserInputAccu(Message &msg)
{
    ushort value = convertMsgContent(msg);

    // If conversion error occures, value is set to -1, if conversion succeeds, convertMsgContent returns new value
    if(this->ok)
    {
        Message msg(Message::UserInputAccu);
        msg.content= &value;
        emit(sendMessage(msg));
    }
    else
    {
        // From Controller to GUI: if user input was wrong
        Message msg(Message::WrongInputAccu);
        emit(sendMessage(msg));
    }
}

void Controller::checkUserInputRAM(Message &msg)
{
    // Msg consists of array with four entries: first one is new value,
    // second one is mode, third is old entry of cell and fourth is cell number
    QString* content = (QString*) msg.content;

    ushort value = convertMsgContent(msg);

    // If conversion error occures, value is set to -1, if conversion succeeds, convertMsgContent returns new value
    if(this->ok)
    {
        this->ok = false;
        unsigned short address = content[3].toUShort(&ok, 10);
        unsigned short* newRamCell = new unsigned short[2];
        newRamCell[0] = address;
        newRamCell[1] = value;
        Message msg(Message::UserInputRAM); //sends short array with address + value to Model
        msg.content= newRamCell;
        emit(sendMessage(msg));
    }
    else
    {
        // From Controller to GUI: if user input was wrong
        QString* newContent = new QString[2];
        newContent[0] = content[3]; // Cell number
        newContent[1] = content[2]; // Old value
        Message msg(Message::WrongInputRAM);
        msg.content = newContent;
        emit(sendMessage(msg));
    }
}


ushort Controller::convertToMnemonic_UserInputRAM(QString s)
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
    else if(s.startsWith("LDA"))
    {
        commandHex = "1";
    }
    else if(s.startsWith("BRZ"))
    {
        commandHex = "2";
    }
    else if(s.startsWith("ADD"))
    {
        commandHex = "3";
    }
    else if(s.startsWith("SUB"))
    {
        commandHex = "4";
    }
    else if(s.startsWith("OR"))
    {
        commandHex = "5";
    }
    else if(s.startsWith("AND"))
    {
        commandHex = "6";
    }
    else if(s.startsWith("XOR"))
    {
        commandHex = "7";
    }
    else if(s.startsWith("NOT"))
    {
        commandHex = "8";
    }
    else if(s.startsWith("INC"))
    {
        commandHex = "9";
    }
    else if(s.startsWith("DEC"))
    {
        commandHex = "A";
    }
    else if(s.startsWith("ZRO"))
    {
        commandHex = "B";
    }
    else
    {
        this->ok = false;
        return -1;
    }

    s = commandHex.append(addressHex);
    return s.toUShort(&ok, 16);
}

ushort Controller::convertToMnemonic_UserInputOpCode(QString s)
{
    if(s.startsWith("STO"))
    {
        return 0;
    }
    else if(s.startsWith("LDA"))
    {
        return 1;
    }
    else if(s.startsWith("BRZ"))
    {
        return 2;
    }
    else if(s.startsWith("ADD"))
    {
        return 3;
    }
    else if(s.startsWith("SUB"))
    {
        return 4;
    }
    else if(s.startsWith("OR"))
    {
        return 5;
    }
    else if(s.startsWith("AND"))
    {
        return 6;
    }
    else if(s.startsWith("XOR"))
    {
        return 7;
    }
    else if(s.startsWith("NOT"))
    {
        return 8;
    }
    else if(s.startsWith("INC"))
    {
        return 9;
    }
    else if(s.startsWith("DEC"))
    {
        return 10;
    }
    else if(s.startsWith("ZRO"))
    {
        return 11;
    }
    else if(s.startsWith("NOP"))
    {
        return 12;
    }
    else
    {
        this->ok = false;
        return -1;
    }
}

ushort Controller::convertMsgContent(Message &msg)
{
    QString* content = (QString*) msg.content; //Array: first cell - new value, second cell - Modus (hexa,dec,bin...)
    QString theContent = content[0];
    int mode = content[1].toInt(&ok, 10);

    unsigned short value;
    switch (mode)
    {
    case 0 : //decimal
    {
        value = theContent.toUShort(&ok, 10);
        break;
    }
    case 1 : //binary
    {
        value = theContent.toUShort(&ok, 2);
        break;
    }
    case 2 : //hexadecimal
    {
        if(theContent.startsWith("$"))
        {
            value = theContent.remove(0,1).toUShort(&ok, 16);
        }
        else
        {
            this->ok = false;
        }
        break;
    }
    case 3 : //mnemonic
    {
        if(msg.type == Message::UserInputRAM)
        {
            value = convertToMnemonic_UserInputRAM(theContent);
        }
        else if(msg.type == Message::UserInputOpCode)
        {
            value = convertToMnemonic_UserInputOpCode(theContent);
            if(value != -1)
            {
                this->ok = true;
            }
        }
        else
        {
            value = theContent.toUShort(&ok, 10);
        }
        break;
    }
    }

    if(ok)
    {
        return value;
    }
    else
    {
        return -1;
    }
}
