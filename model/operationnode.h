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

#ifndef OPERATIONNODE_H
#define OPERATIONNODE_H
#include "model/treenode.h"
#include "model/toyexception.h"

/*
 * Objects of this class will be part in the
 * SyntaxTree of the PseudoCCompiler. They contain
 * information on arithmetic operations such as
 * +, -, !, &, |, ...
 */


class OperationNode : public TreeNode
{
public:
    // Constructor
    OperationNode(int row, const TYPE &type, const OPERATION &op, QString line);

    // Getters
    QString getResult();
    QString getOperand1();
    QString getOperand2();
    TreeNode::OPERATION getOperation();

private:
    // Attributes
    QString result;
    QString operand1;
    QString operand2;
    OPERATION op;

    // Methods to parse single arithmetic operations:
    // - Splitting of line into result- and operandsvariables
    // - Saving these strings in the matching attributes
    // - Writing toyCode for operation and saving it
    //   in TreeNode Attribute "QString toyCode"
    QStringList parseC_ADDandINC(QString line);
    QStringList parseC_SUBandDEC(QString line);
    QStringList parseC_OR(QString line);
    QStringList parseC_AND(QString line);
    QStringList parseC_XOR(QString line);
    QStringList parseC_NOT(QString line);
};

#endif // OPERATIONNODE_H
