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

#ifndef ROW_H
#define ROW_H
#include <QDebug>

/*
 * The class "Row" receives lines from the "Parser"
 * and by them defines objects containing the opcode
 * of the command in the given line, the row-number
 * and also the information, if the line contained
 * an instruction or a variable declaration. The methods
 * "showAs*" return a string matching the opcode of a
 * row in either binary, hexadecimal or mnemonic format.
 */

class Row
{
public:
    enum FORMAT {
        binary,
        hexa,
        mnemonic
    };

    enum TYPE {
        variable,
        instruction
    };

    // Constructor for Row-Objects with type instruction
    Row(QString line, int number, const FORMAT &format, const TYPE &type);

    // Constructor for Row-Objects with type variable
    Row(int number, const TYPE &type);

    // Getter
    int getNumber();
    short getOpcode();
    TYPE getType();
    virtual int getPlace();

    // Converts Mnemonicstring into UShort
    ushort convertMnemonic(QString s);

    // Converts OpCode into Binarystring
    QString showAsBin();

    // Converts OpCode into Hexadecimalstring
    QString showAsHexa();

    // Converts OpCode into Mnemonicstring
    QString showAsMnemonic();

protected:
    // Attributes
    int number;
    short opcode;
    const TYPE type;
};

#endif // ROW_H
