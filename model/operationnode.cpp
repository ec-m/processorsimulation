#include "operationnode.h"

// @author: Eva Charlotte Mayer

QString OperationNode::getResult()
{
    return this->result;
}

QString OperationNode::getOperand1()
{
    return this->operand1;
}

QString OperationNode::getOperand2()
{
    return this->operand2;
}

TreeNode::OPERATION OperationNode::getOperation()
{
    return this->op;
}

OperationNode::OperationNode(int row, const TYPE &type, const OPERATION &op, QString line) : TreeNode(row, type), op(op)
{
    switch (op)
    {
    case Plus :
        this->toyCode = parseC_ADDandINC(line);
        break;
    case Minus:
        this->toyCode = parseC_SUBandDEC(line);
        break;
    case And :
        this->toyCode = parseC_AND(line);
        break;
    case Or :
        this->toyCode = parseC_OR(line);
        break;
    case Xor :
        this->toyCode = parseC_XOR(line);
        break;
    case Not :
        this->toyCode = parseC_NOT(line);
        break;
    }
}

QStringList OperationNode::parseC_ADDandINC(QString line)
{
    QStringList newList;
    int place = line.indexOf("+");
    QString left = line.left(place);
    QString plusVar2 = line.right(line.length() - place - 1);
    //if plusVar2 == + then the expression is var++, so its an increment operation
    if(plusVar2.startsWith("+"))
    {
        //write mnemonic code to increment variable
        QString lda = "LDA ";
        lda.append(left);
        newList << lda;
        newList << "INC";
        QString sto = "STO ";
        sto.append(left);
        newList << sto;
        this->result = left;
        this->op = TreeNode::Inc;
    }
    else
    {
        //write mnemonic code to add the two variables
        if(left.contains("="))
        {
            int place = line.indexOf("=");
            QString plusVar1 = left.right(left.length() - 1 - place);
            QString resultVar = left.left(place);
            QString lda = "LDA ";
            lda.append(plusVar1);
            newList << lda;
            QString add = "ADD ";
            add.append(plusVar2);
            newList << add;
            QString sto = "STO ";
            sto.append(resultVar);
            newList << sto;

            this->result = resultVar;
            this->operand1 = plusVar1;
            this->operand2 = plusVar2;
        }
        else
        {
            QString msg = "Please assign plus operation to a result variable in line: ";
            msg.append(QString::number(this->row+1));
            throw ToyException(msg);
        }
    }
    return newList;
}

QStringList OperationNode::parseC_SUBandDEC(QString line)
{
    QStringList newList;
    int place = line.indexOf("-");
    QString left = line.left(place);
    QString minusVar2 = line.right(line.length() - place - 1);
    //if minusVar2 == - then the expression is var--, so its an increment operation
    if(minusVar2.startsWith("-"))
    {
        //write mnemonic code to decrement variable
        QString lda = "LDA ";
        lda.append(left);
        newList << lda;
        newList << "DEC";
        QString sto = "STO ";
        sto.append(left);
        newList << sto;
        this->result = left;
        this->op = TreeNode::Dec;
    }
    else
    {
        //write mnemonic code to subtract the two variables
        if(left.contains("="))
        {
            int place = line.indexOf("=");
            QString minusVar1 = left.right(left.length() - 1 - place);
            QString resultVar = left.left(place);
            QString lda = "LDA ";
            lda.append(minusVar1);
            newList << lda;
            QString sub = "SUB ";
            sub.append(minusVar2);
            newList << sub;
            QString sto = "STO ";
            sto.append(resultVar);
            newList << sto;

            this->result = resultVar;
            this->operand1 = minusVar1;
            this->operand2 = minusVar2;
        }
        else
        {
            QString msg = "Please assign minus operation to a result variable in line: ";
            msg.append(QString::number(this->row+1));
            throw ToyException(msg);
        }
    }
    return newList;
}

QStringList OperationNode::parseC_OR(QString line)
{
    QStringList newList;
    int place = line.indexOf("|");
    QString left = line.left(place);
    QString orVar2 = line.right(line.length() - place - 1);

    //write mnemonic code to "or" the two variables
    if(left.contains("="))
    {
        int place = line.indexOf("=");
        QString orVar1 = left.right(left.length() - 1 - place);
        QString resultVar = left.left(place);
        QString lda = "LDA ";
        lda.append(orVar1);
        newList << lda;
        QString theOr = "OR ";
        theOr.append(orVar2);
        newList << theOr;
        QString sto = "STO ";
        sto.append(resultVar);
        newList << sto;

        this->result = resultVar;
        this->operand1 = orVar1;
        this->operand2 = orVar2;
    }
    else
    {
        QString msg = "Please assign or operation to a result variable in line: ";
        msg.append(QString::number(this->row+1));
        throw ToyException(msg);
    }
    return newList;
}

QStringList OperationNode::parseC_AND(QString line)
{
    QStringList newList;
    int place = line.indexOf("&");
    QString left = line.left(place);
    QString andVar2 = line.right(line.length() - place - 1);

    //write mnemonic code to "and" the two variables
    if(left.contains("="))
    {
        int place = line.indexOf("=");
        QString andVar1 = left.right(left.length() - 1 - place);
        QString resultVar = left.left(place);
        QString lda = "LDA ";
        lda.append(andVar1);
        newList << lda;
        QString theAnd = "AND ";
        theAnd.append(andVar2);
        newList << theAnd;
        QString sto = "STO ";
        sto.append(resultVar);
        newList << sto;

        this->result = resultVar;
        this->operand1 = andVar1;
        this->operand2 = andVar2;
    }
    else
    {
        QString msg = "Please assign and operation to a result variable in line: ";
        msg.append(QString::number(this->row+1));
        throw ToyException(msg);
    }
    return newList;
}

QStringList OperationNode::parseC_XOR(QString line)
{
    QStringList newList;
    int place = line.indexOf("^");
    QString left = line.left(place);
    QString xorVar2 = line.right(line.length() - place - 1);

    //write mnemonic code to "xor" the two variables
    if(left.contains("="))
    {
        int place = line.indexOf("=");
        QString xorVar1 = left.right(left.length() - 1 - place);
        QString resultVar = left.left(place);
        QString lda = "LDA ";
        lda.append(xorVar1);
        newList << lda;
        QString theXOr = "XOR ";
        theXOr.append(xorVar2);
        newList << theXOr;
        QString sto = "STO ";
        sto.append(resultVar);
        newList << sto;

        this->result = resultVar;
        this->operand1 = xorVar1;
        this->operand2 = xorVar2;
    }
    else
    {
        QString msg = "Please assign xor operation to a result variable in line: ";
        msg.append(QString::number(this->row+1));
        throw ToyException(msg);
    }
    return newList;
}

QStringList OperationNode::parseC_NOT(QString line)
{
    QStringList newList;
    int place = line.indexOf("!");
    QString notVar = line.right(line.length() - 1 - place);
    QString equals = line.at(place - 1);
    if(equals != "=")
    {
        QString msg = "Please assign not operation to a result variable in line: ";
        msg.append(QString::number(this->row+1));
        throw ToyException(msg);
    }
    else
    {
        QString resultVar = line.left(place - 1);
        QString lda = "LDA ";
        lda.append(notVar);
        newList << lda;
        newList << "NOT";
        QString sto = "STO ";
        sto.append(resultVar);
        newList << sto;

        this->result = resultVar;
        this->operand1 = notVar;
    }
    return newList;
}


