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

#ifndef VARIABLEDECLARATIONNODE_H
#define VARIABLEDECLARATIONNODE_H
#include <QRegExp>
#include "model/treenode.h"
#include "model/toyexception.h"

/*
 * The class "VariableDeclarationNode" parses statements that
 * declare variables in Pseudo-C-Code. The allowed data types
 * are "short int", "bool" and "char".
 */

class VariableDeclarationNode : public TreeNode
{
public:
    // Constructor
    VariableDeclarationNode(int row, const TreeNode::TYPE &type, QString line);

    // Getters
    DATATYPE getDatatype();
    short getValue();
    QString getName();

private:
    // Parses the data type "short int" in pseudo c code
    bool parseShortInts(QString line);

    // Parses the data type "char" in pseudo c code
    bool parseChars(QString line);

    // Parses the data type "bool" in pseudo c code
    bool parseBools(QString line);

    // Produces the toy-Code for the variable declaration and
    // saves it in the TreeNode-Attribute "QStringList toyCode"
    void makeToyCode();

    // Attributes
    DATATYPE datatype;
    short value;
    QString name;

};

#endif // VARIABLEDECLARATIONNODE_H
