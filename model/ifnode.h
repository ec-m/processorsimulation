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

#ifndef IFNODE_H
#define IFNODE_H
#include "model/treenode.h"
#include "model/toyexception.h"

class SyntaxTree;

/*
 * The class IfNode parses an if-statement in
 * Pseudo-C-Code. First, the if(...) statement
 * is converted into according ToyProcessor-Code.
 * Then a new SyntaxTree is established for the
 * code in the body of the if-statement.
 */

class IfNode : public TreeNode
{
public:
    // Constructor
    IfNode(int row, const TreeNode::TYPE &type, QStringList lines, QList<TreeNode*> vars);

private:
    // Attributes
    SyntaxTree* t;

    // Inserts the beginning of the ToyCode for an
    // if-condition aka LDA var, BRZ to end of statement
    void insertToyCode(QString variable, QString label);

    // Inserts body of if-statement and finally the end of
    // a if-statement into the ToyCode-List
    void insertToyCode(SyntaxTree* t);

    // Checks if variable used in if-Statement with (var != 0) has been declared
    bool checkIfDeclaredUnequalZero(QString ausdruck, QList<TreeNode* > vars);

    // Checks if variable used in if-Statement with (var) has been declared
    bool checkIfDeclaredBool(QString ausdruck, QList<TreeNode* > vars);

};

#endif // IFNODE_H
