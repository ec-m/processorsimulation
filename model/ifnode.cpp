#include "ifnode.h"
#include "model/syntaxtree.h"

// @author: Eva Charlotte Mayer

IfNode::IfNode(int row, const TreeNode::TYPE &type, QStringList lines, QList<TreeNode *> vars) : TreeNode(row, type)
{
    QString line = lines.at(0);
    int klammerauf = line.indexOf("(");
    int klammerzu = line.indexOf(")");
    QString ausdruck = line.mid(klammerauf + 1, klammerzu - klammerauf - 1);
    QRegExp rxAusdruck("^((^[A-Z,a-z,\\d]+)!=0)|(^[A-Z,a-z,\\d]+)");
    if(!rxAusdruck.exactMatch(ausdruck))
    {
        QString msg = "Please test only for unequal to zero or with bool in line: ";
        msg.append(QString::number(row+1));
        throw ToyException(msg);
    }
    else
    {
        if(checkIfDeclaredUnequalZero(ausdruck, vars) || checkIfDeclaredBool(ausdruck, vars))
        {
            QString variable;
            if(checkIfDeclaredUnequalZero(ausdruck, vars))
            {
                int equals = ausdruck.indexOf("!");
                variable = ausdruck.left(equals);
            }
            else
            {
                variable = ausdruck;
            }
            QString label = "IfLabel";
            QString s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            int pos = qrand() % s.length();
            label.append(s.at(pos));
            insertToyCode(variable, label);
            lines.removeAt(0);
            t = new SyntaxTree(lines, row, vars);
            t->makeTree();
            insertToyCode(t);
            label.append(":");
            this->toyCode << label;
        }
        else
        {
            QString msg = "Variable used in if-statement has not been declared. See line: ";
            msg.append(QString::number(row+1));
            throw ToyException(msg);
        }
    }
}


void IfNode::insertToyCode(QString variable, QString label)
{
    QString lda = "LDA ";
    lda.append(variable);
    this->toyCode << lda;
    QString brz = "BRZ ";
    brz.append(label);
    this->toyCode << brz; //label to skip over code in brackets if variable is already equal to zero
}

void IfNode::insertToyCode(SyntaxTree *t)
{
    for(int i = 0; i < t->getNodes().length(); i++)
    {
        this->toyCode << t->getNodes()[i]->getToyCode();
    }
}

bool IfNode::checkIfDeclaredUnequalZero(QString ausdruck, QList<TreeNode* > vars)
{
    bool result = false;
    int equals = ausdruck.indexOf("!");
    QString variable = ausdruck.left(equals);
    for(int i = 0; i < vars.length(); i++)
    {
        TreeNode* n = vars.at(i);
        if(n->getName() == variable)
        {
            result = true;
            break;
        }
    }
    return result;
}

bool IfNode::checkIfDeclaredBool(QString ausdruck, QList<TreeNode* > vars)
{
    bool result = false;
    QString variable = ausdruck;
    for(int i = 0; i < vars.length(); i++)
    {
        TreeNode* n = vars.at(i);
        if(n->getName() == variable)
        {
            result = true;
            break;
        }
    }
    return result;
}
