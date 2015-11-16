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

#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
#include <QStringList>
#include <QList>
#include "model/treenode.h"
#include "model/variabledeclarationnode.h"
#include "model/toyexception.h"
#include "model/operationnode.h"
#include "model/ifnode.h"
#include "model/loopnode.h"

/*
 * The class "SyntaxTree" receives lines from the
 * "PseudoCPreProcessor" and builds a Tree of
 * TreeNode-Objects according to the Pseudo-C-Code
 * that is given. Once the tree is fully built, the
 * method "checkTree" checks if all variables used
 * have been declared, if all type conversions are
 * correct and if all values are in the bounds of
 * the declared variables' datatypes.
 * If successfull, the PseudoCPreCompiler
 * can get the ToyCode of all TreeNode-Objects.
 */

class SyntaxTree
{
private:
    // Attributes
    QList<TreeNode*> nodes;
    QStringList lines;
    // Variabledeclarations are needed to be able to check not only
    // local variables for declaration in while/if but also global ones.
    QList<TreeNode*> variabledeclarations;
    // RowCount is needed, if new SyntaxTree is declared in for
    // example an if-Condition. Now row-Numbers for the nodes in
    // this new SyntaxTree cannot start at zero.
    int rowCount;

    // Check if a used variable has been declared
    bool checkIfDeclared(QString name, int row);

    // Check if in an arithmetic statement the operands
    // have types that can be converted into each other
    bool checkIfTypeConversionCorrect(QString left, QString right);

    // Returns body of while/for-loop
    QStringList getLinesInBrackets(int position);

    // Counts lines in body of while/for-loop
    int countLinesInBrackets(QStringList list, int position);

public:
    // Constructor
    SyntaxTree(QStringList lines, int rowCount, QList<TreeNode*> variabledeclarations);

    // Build SyntaxTree out of Pseudo-C-Code
    bool makeTree();

    // Checks if all statements are syntacticly correct
    // - have all variables been declared?
    // - are all type conversions correct?
    // - are all values assigned to a variable in the bounds of the given datatype?
    void checkTree();

    // Getter
    QList<TreeNode*> getNodes();

    // Appends Nodes with given list of nodes
    void appendNodes(QList<TreeNode*> nodes);
};

#endif // SYNTAXTREE_H
