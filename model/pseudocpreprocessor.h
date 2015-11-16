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

#ifndef PSEUDOCPREPROCESSOR_H
#define PSEUDOCPREPROCESSOR_H
#include <QStringList>
#include "model/toyexception.h"
#include "model/syntaxtree.h"

/*
 * The class "PseudoCPreprocessor" checks if the file and all the
 * contained lines that are parsed by the "PseudoCCompiler" are
 * formatted correctly. The "PseudoCPreprocessor" removes all for
 * the ToyProcessor irrelevant content from the lines, such as
 * comments, spaces, empty lines, semicolons. Once this is finished
 * a SyntaxTree is build from all the given statements.
 */

class PseudoCPreprocessor
{
private:
    // Attribute
    QStringList lines;

    // Removes spaces in strings, comments and empty lines
    void removeSpacesCommentsEmptyLines();

    // Removes all ";" at the end of a statements
    bool removeSemicolons();

    // Receives and appends all the ToyCode-lines from
    // the objects in the SyntaxTree and finally inserts
    // the necessary infinite loop in the end
    void getLinesFromSyntaxTree(SyntaxTree* t);

public:
    // Constructor
    PseudoCPreprocessor(QStringList lines);

    // Getter
    QStringList getLines();

    // Controls formatting process
    bool format();

};

#endif // PSEUDOCPREPROCESSOR_H
