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

#ifndef PREPARSER_H
#define PREPARSER_H
#include <QDebug>
#include <QStringList>
#include <model/toyexception.h>
#include "model/row.h"

/*
 * The class "Preparser" checks if the file and all the
 * contained lines that are parsed by the "Parser" are
 * formatted correctly. The "Preparser" removes all for
 * the ToyProcessor irrelevant content from the lines,
 * such as comments, spaces, empty lines. Also, if the code
 * contained labels or variables, the "Preparser" replaces
 * them by integers matching the RAM-address they should
 * be stored in. Finally, an infinite loop check is
 * implemented in the "Preparser".
 */

class Preparser
{
private:
    // Attribute
    QStringList lines;
    int numberOfOpCodes;

    // Removes spaces in strings, comments and empty lines
    bool removeSpacesCommentsEmptyLines(QStringList list);

    // Edits file so that variables are replaced by ":address:value" and
    // OpCodes like "LDA variable" are replaced by "LDA valueOfVariable"
    QStringList replaceVariables(QStringList list, int numberOfOpCodes);

    // Edits file so that lables in OpCodes like "BRZ label"
    // are replaced by "BRZ addressOfFirstOpCodeAfterLabel"
    QStringList replaceLables(QStringList list);

    //Checks if there is a variable used in an OpCode that was not declared
    bool checkForUndeclaredVariable(QStringList list);

    //Checks if there is a variable used in a "BRZ label" that was not declared
    bool checkForUndeclaredLabel(QStringList list);

    // Counts all Opcodes from given position to beginning of file
    int countOpCodes(QStringList list, int position);
public:
    //Constructor
    Preparser();

    //Getter
    QStringList getLines();
    int getNumberOfOpCodes();

    // Checks if filename matches *.toy
    bool checkFileName(QString filename);

    // Controls formatting of lines into parseable lines
    bool format(QStringList list);

    // Checks if last opcodes are "ZRO" and "BRZ <address of ZRO>"
    bool checkInfiniteLoop(short *opcodes, QList<Row *> rows);

    void clearLines();

};

#endif // PREPARSER_H
