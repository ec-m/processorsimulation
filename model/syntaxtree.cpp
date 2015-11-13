#include "syntaxtree.h"

// @author: Eva Charlotte Mayer

SyntaxTree::SyntaxTree(QStringList lines, int rowCount, QList<TreeNode *> variabledeclarations)
{
    this->lines = lines;
    this->rowCount = rowCount;
    this->variabledeclarations = variabledeclarations;
}

QList<TreeNode*> SyntaxTree::getNodes()
{
    return this->nodes;
}

bool SyntaxTree::makeTree()
{
    QRegExp rxVarWithDataType("^(^[a-z])((\\s)*)([A-Z,a-z,\\d]+)((\\s)*)=((\\s)*)((\\d)+|(\\$(\\d|[A-F,a-f])+))((\\s)*)"); //Regex for correct variable declaration
    QRegExp rxVarWithoutDataType("^(^[A-Z,a-z,\\d]+)((\\s)*)=((\\s)*)((\\d)+|(\\$(\\d|[A-F,a-f])+))((\\s)*)"); //Regex for variable declaration without a data type

    for(int i = 0; i < this->lines.length(); i++)
    {
        QString line = this->lines.at(i);

        if(line.isEmpty())
        {
            continue;
        }
        else if (rxVarWithDataType.indexIn(line) != -1)
        {
            TreeNode* n = new VariableDeclarationNode(i + this->rowCount, TreeNode::variabledeclaration, line);
            this->nodes << n;
            this->variabledeclarations << n;
        }
        else if (rxVarWithoutDataType.indexIn(line) != -1)
        {
            QString msg = "There is a data type for the variable declaration missing in line: ";
            msg.append(QString::number(i + this->rowCount + 1));
            throw ToyException(msg);
        }
        else if(line.contains("if"))
        {
            QStringList linesInBrackets = getLinesInBrackets(i);
            i += linesInBrackets.length() - 1;
            TreeNode* n = new IfNode(i + this->rowCount, TreeNode::ifstatement, linesInBrackets, this->variabledeclarations);
            this->nodes << n;
        }
        else if(line.contains("while"))
        {
            QStringList linesInBrackets = getLinesInBrackets(i);
            i += linesInBrackets.length() - 1;
            TreeNode* n = new LoopNode(i + this->rowCount, TreeNode::whileloop, linesInBrackets, this->variabledeclarations);
            this->nodes << n;
        }
        else if(line.contains("for"))
        {
            QStringList linesInBrackets = getLinesInBrackets(i);
            i += linesInBrackets.length() - 1;
            TreeNode* n = new LoopNode(i + this->rowCount, TreeNode::forloop, linesInBrackets, this->variabledeclarations);
            this->nodes << n;
        }
        else if(line.contains("+"))
        {
            TreeNode* n = new OperationNode(i + this->rowCount, TreeNode::operation, OperationNode::Plus, line);
            this->nodes << n;
        }
        else if(line.contains("-"))
        {
            TreeNode* n = new OperationNode(i + this->rowCount, TreeNode::operation, OperationNode::Minus, line);
            this->nodes << n;
        }
        else if(line.contains("|"))
        {
            TreeNode* n = new OperationNode(i + this->rowCount, TreeNode::operation, OperationNode::Or, line);
            this->nodes << n;
        }
        else if(line.contains("&"))
        {
            TreeNode* n = new OperationNode(i + this->rowCount, TreeNode::operation, OperationNode::And, line);
            this->nodes << n;
        }
        else if(line.contains("^"))
        {
            TreeNode* n = new OperationNode(i + this->rowCount, TreeNode::operation, OperationNode::Xor, line);
            this->nodes << n;
        }
        else if(line.contains("!"))
        {
            TreeNode* n = new OperationNode(i + this->rowCount, TreeNode::operation, OperationNode::Not, line);
            this->nodes << n;
        }
    }
}

void SyntaxTree::checkTree()
{
    for(int i = 0; i < this->nodes.length(); i++)
    {
        TreeNode* n = this->nodes.at(i);
        if(n->getType() == TreeNode::operation)
        {
            // Increment or decrement operations don't have to be checked because they only contain one variable
            if(n->getOperation() == TreeNode::Inc || n->getOperation() == TreeNode::Dec)
            {
                continue;
            }

            // Checks not-operations (that only have one operand-variable)
            else if(n->getOperation() == TreeNode::Not)
            {
                if(checkIfDeclared(n->getResult(), n->getRow()) && checkIfDeclared(n->getOperand1(), n->getRow()))
                {
                    if(! (checkIfTypeConversionCorrect(n->getResult(), n->getOperand1())))
                    {
                        QString msg = "Wrong type conversion in line: ";
                        msg.append(QString::number(n->getRow()+1+ this->rowCount));
                        throw ToyException(msg);
                        break;
                    }

                }
                else
                {
                    QString msg = "Non declared variable used in line: ";
                    msg.append(QString::number(n->getRow()+1+ this->rowCount));
                    throw ToyException(msg);
                    break;
                }
            }

            // Checks if all variables used in operation other than dec and inc have been declared above
            else if(checkIfDeclared(n->getResult(), n->getRow()) && checkIfDeclared(n->getOperand1(), n->getRow()) && checkIfDeclared(n->getOperand2(), n->getRow()))
            {
                if(! (checkIfTypeConversionCorrect(n->getResult(), n->getOperand1()) || checkIfTypeConversionCorrect(n->getResult(), n->getOperand2())))
                {
                    QString msg = "Wrong type conversion in line: ";
                    msg.append(QString::number(n->getRow()+1+ this->rowCount));
                    throw ToyException(msg);
                    break;
                }
            }
            else
            {
                QString msg = "Non declared variable used in line: ";
                msg.append(QString::number(n->getRow()+1+ this->rowCount));
                throw ToyException(msg);
                break;
            }
        }
    }
}

bool SyntaxTree::checkIfDeclared(QString name, int row)
{
    bool b = false;
    for(int i = 0; i < this->nodes.length(); i++)
    {
        TreeNode* n = this->nodes.at(i);
        if(n->getType() == TreeNode::variabledeclaration
                && n->getName() == name
                && n->getRow() < row)
        {
            b = true;
            break;
        }
    }
    return b;
}

bool SyntaxTree::checkIfTypeConversionCorrect(QString left, QString right)
{
    TreeNode::DATATYPE t_left;
    TreeNode::DATATYPE t_right;
    for(int i = 0; i < this->nodes.length(); i++)
    {
        TreeNode* n = this->nodes.at(i);
        if(n->getType() == TreeNode::variabledeclaration)
        {
            if(n->getName() == left)
            {
                t_left = n->getDatatype();
                continue;
            }
            else if(n->getName() == right)
            {
                t_right = n->getDatatype();
                continue;
            }
        }
    }

    // Assigning a short int a char or bool is always allowed
    if (t_left == TreeNode::shortinttype)
    {
        return true;
    }
    else if (t_left == TreeNode::chartype)
    {
        // Assigning a char a short int is not allowed
        if (t_right == TreeNode::shortinttype)
        {
            return false;
        }
        // Assigning a char another char or a bool is allowed
        else
        {
            return true;
        }
    }
    else if (t_left == TreeNode::booltype)
    {
        // Assigning a bool a short int or a char is not allowed
        if (t_right == TreeNode::shortinttype || t_right == TreeNode::chartype)
        {
            return false;
        }
        // Assigning a bool another bool is allowed
        else
        {
            return true;
        }
    }
}

int SyntaxTree::countLinesInBrackets(QStringList list, int position)
{
    int count = 0;
    while(!list.at(position + count).contains("}"))
    {
        if(list.at(position + count).contains("if") || list.at(position + count).contains("while") || list.at(position + count).contains("for"))
        {
            count += countLinesInBrackets(list, position + count + 1) + 2;
        }
        else
        {
            count++;
        }
    }
    return count;
}

QStringList SyntaxTree::getLinesInBrackets(int position)
{
    QStringList result;
    int count = this->countLinesInBrackets(this->lines, position + 1);
    for(int i = position; i <= position + count + 1; i++)
    {
        result << this->lines.at(i);
    }
    return result;
}

void SyntaxTree::appendNodes(QList<TreeNode*> nodes)
{
    this->nodes.append(nodes);
}
