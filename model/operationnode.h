#ifndef OPERATIONNODE_H
#define OPERATIONNODE_H
#include "model/treenode.h"
#include "model/toyexception.h"

/*
 * Objects of this class will be part in the
 * SyntaxTree of the PseudoCCompiler. They contain
 * information on arithmetic operations such as
 * +, -, !, &, |, ...
 * @author: Eva Charlotte Mayer
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
