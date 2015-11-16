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

#ifndef LOOPNODE_H
#define LOOPNODE_H
#include "model/treenode.h"
#include "model/toyexception.h"

class SyntaxTree;

/*
 * The class LoopNode parses both while- and for-loops.
 * Parsing a while-loop:
 *      The while(...) statement is converted
 *      into according ToyProcessor-Code. Then
 *      a new SyntaxTree is established for the
 *      code in the body of the while-loop
 * Parsing a for-loop:
 *      The for(...) statement gets translated
 *      into an equivalent while-statement, which
 *      is then parsed as a while-loop.
 */


class LoopNode : public TreeNode
{
public:
    // Constructor
    LoopNode(int row, const TreeNode::TYPE &type, QStringList lines, QList<TreeNode *> vars);

private:
    // Attributes
    SyntaxTree* t;

    // Inserts the beginning of the ToyCode for a while loop
    // aka LDA var, BRZ to end of loop
    void insertToyCode(QString ausdruck, QString label1, QString label2);

    // Inserts body of while-loop and finally the end of
    // a while-loop into the ToyCode-List
    void insertToyCode(SyntaxTree *t, QString label1, QString label2);

    // Converts a for-loop into a while-loop, so it can be parsed as such
    QStringList convertForIntoWhileLoop(int i, QStringList lines);

    // Checks if variable used in loop-Statement has been declared
    bool checkIfDeclared(QString ausdruck, QList<TreeNode* > vars);
};

#endif // LOOPNODE_H
