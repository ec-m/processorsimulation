#include "loopnode.h"
#include "model/syntaxtree.h"
#include "model/variabledeclarationnode.h"

// @author: Eva Charlotte Mayer

LoopNode::LoopNode(int row, const TreeNode::TYPE &type, QStringList lines, QList<TreeNode *> vars) : TreeNode(row, type)
{
    if(type == TreeNode::forloop)
    {
        lines = convertForIntoWhileLoop(row, lines);
    }
    QString line = lines.at(0);
    int klammerauf = line.indexOf("(");
    int klammerzu = line.indexOf(")");
    QString ausdruck = line.mid(klammerauf + 1, klammerzu - klammerauf - 1);
    QRegExp rxAusdruck("^(^[A-Z,a-z,\\d]+)!=0");
    if(!rxAusdruck.exactMatch(ausdruck))
    {
        QString msg = "Please test only for unequal to zero in line: ";
        msg.append(QString::number(row+1));
        throw ToyException(msg);
    }
    else
    {
        if(checkIfDeclared(ausdruck, vars))
        {
            QString label1 = "LoopLabel";
            QString label2 = "AfterLoop";
            QString s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            int pos = qrand() % s.length();
            label1.append(s.at(pos));
            label2.append(s.at(pos));
            insertToyCode(ausdruck, label1, label2);
            lines.removeAt(0);
            t = new SyntaxTree(lines, row, vars);
            t->makeTree();
            insertToyCode(t, label1, label2);
        }
        else
        {
            QString msg = "Variable used in loop-statement has not been declared. See line: ";
            msg.append(QString::number(row+1));
            throw ToyException(msg);
        }
    }
}

void LoopNode::insertToyCode(QString ausdruck, QString label1, QString label2)
{
    //inserts label for beginning of Loop loop
    label1.append(":");
    this->toyCode << label1;

    //code to load variables for check if equal to zero
    int equals = ausdruck.indexOf("!");
    QString variable = ausdruck.left(equals);
    QString lda = "LDA ";
    lda.append(variable);
    this->toyCode << lda;
    QString brz1 = "BRZ ";
    brz1.append(label2);
    this->toyCode << brz1; //label to skip over code in brackets if variable is already equal to zero
}

void LoopNode::insertToyCode(SyntaxTree *t, QString label1, QString label2)
{
    for(int i = 0; i < t->getNodes().length(); i++)
    {
        this->toyCode << t->getNodes()[i]->getToyCode();
    }

    //inserts label to jump back to beginning of Loop-loop
    this->toyCode << "ZRO";
    QString brz1 = "BRZ ";
    brz1.append(label1);
    this->toyCode << brz1;

    //inserts label for code after Loop-loop
    label2.append(":");
    this->toyCode << label2;
}

QStringList LoopNode::convertForIntoWhileLoop(int i, QStringList lines)
{
    QStringList newList;
    QString line = lines.at(0);
    int klammerauf = line.indexOf("(");
    int klammerzu = line.indexOf(")");
    QString ausdruck = line.mid(klammerauf + 1, klammerzu - klammerauf - 1);
    QStringList splits = ausdruck.split(";");
    QRegExp rx1("^(^shortint((\\s)*)[A-Z,a-z,\\d]+)((\\s)*)=((\\s)*)(0|\\d+)((\\s)*)");
    QRegExp rx2("((\\s)*)[A-Z,a-z,\\d]+((\\s)*)(<|>)((\\s)*)(0|\\d+)(\\s)*");
    QRegExp rx3("((\\s)*)[A-Z,a-z,\\d]+(\\+\\+|--)");
    if(!rx1.exactMatch(splits.at(0)) | !rx2.exactMatch(splits.at(1)) | !rx3.exactMatch(splits.at(2)))
    {
        QString msg = "Your for-loop in line: ";
        msg.append(QString::number(i+1));
        msg.append(" does not equal the standart definition: for(short int i = 0/a; i </> b/0; i++/i--).");
        throw ToyException(msg);
    }
    else
    {
        if(splits.at(1).contains(">"))
        {
            //Parsing for(i = b; i > c; i++)
            if(splits.at(2).contains("+"))
            {
                QString var = splits.at(0).left(splits.at(0).indexOf("=")).simplified().replace( " ", "" );
                var.remove("shortint");
                QString var1 = splits.at(1).left(splits.at(1).indexOf(">")).simplified().replace( " ", "" );
                QString var2 = splits.at(2).left(splits.at(2).indexOf("+")).simplified().replace( " ", "" );
                if((var !=  var1)| (var != var2))
                {
                    QString msg = "Your for-loop in line: ";
                    msg.append(QString::number(i+1));
                    msg.append(" contains different variables for counting. This is not allowed - Please rewrite your code.");
                    throw ToyException(msg);
                }
                else
                {
                    //insert variable declaration for for-loop-variable
                    QString firstBound = splits.at(0).right(splits.at(0).length() - splits.at(0).indexOf("=") - 1);
                    QString secondBound = splits.at(1).right(splits.at(1).length() - splits.at(1).indexOf(">") - 1);
                    bool ok = false;
                    QString value = QString::number(abs(firstBound.toInt(&ok, 10) - secondBound.toInt(&ok, 10)));
                    var.append("=").append(value);
                    var.insert(0, "shortint");
                    TreeNode* varNode = new VariableDeclarationNode(-1, TreeNode::variabledeclaration, var);
                    this->toyCode << varNode->getToyCode();
                    var.remove("shortint");

                    //copy all lines from inside for-loop and i++ statement into the list "whileList" and parse it as a while-loop
                    QStringList insideBrackets;
                    QString whileStatement = "while(";
                    var.remove("=");
                    var.remove(value);
                    whileStatement.append(var);
                    whileStatement.append("!=0) {");
                    insideBrackets << whileStatement;
                    lines.removeAt(0); //remove first line (for-loop-statement)
                    lines.removeAt(lines.length()-1); //remove closing bracket
                    insideBrackets.append(lines);

                    insideBrackets << splits.at(2); //insert i++ into body of while-loop
                    insideBrackets << "}";
                    newList.append(insideBrackets);
                }
            }
            //Parsing for(i = b; i > c; i--)
            else
            {
                QString var = splits.at(0).left(splits.at(0).indexOf("=")).simplified().replace( " ", "" );
                var.remove("shortint");
                QString var1 = splits.at(1).left(splits.at(1).indexOf(">")).simplified().replace( " ", "" );
                QString var2 = splits.at(2).left(splits.at(2).indexOf("-")).simplified().replace( " ", "" );
                if((var !=  var1)| (var != var2))
                {
                    QString msg = "Your for-loop in line: ";
                    msg.append(QString::number(i+1));
                    msg.append(" contains different variables for counting. This is not allowed - Please rewrite your code.");
                    throw ToyException(msg);
                }
                else
                {
                    //insert variable declaration for for-loop-variable
                    QString firstBound = splits.at(0).right(splits.at(0).length() - splits.at(0).indexOf("=") - 1);
                    QString secondBound = splits.at(1).right(splits.at(1).length() - splits.at(1).indexOf(">") - 1);
                    bool ok = false;
                    QString value = QString::number(abs(firstBound.toInt(&ok, 10) - secondBound.toInt(&ok, 10)));
                    var.append("=").append(value);
                    var.insert(0, "shortint");
                    TreeNode* varNode = new VariableDeclarationNode(-1, TreeNode::variabledeclaration, var);
                    this->toyCode << varNode->getToyCode();
                    var.remove("shortint");

                    //copy all lines from inside for-loop and i-- statement into the list "whileList" and parse it as a while-loop
                    QStringList insideBrackets;
                    QString whileStatement = "while(";
                    var.remove("=");
                    var.remove(value);
                    whileStatement.append(var);
                    whileStatement.append("!=0) {");
                    insideBrackets << whileStatement;
                    lines.removeAt(0); //remove first line (for-loop-statement)
                    lines.removeAt(lines.length()-1); //remove closing bracket
                    insideBrackets.append(lines);

                    insideBrackets << splits.at(2); //insert i-- into body of while-loop
                    insideBrackets << "}";
                    newList.append(insideBrackets);
                }
            }
        }
        else
        {
            //Parsing for(i = b; i < c; i++)
            if(splits.at(2).contains("+"))
            {
                QString var = splits.at(0).left(splits.at(0).indexOf("=")).simplified().replace( " ", "" );
                var.remove("shortint");
                QString var1 = splits.at(1).left(splits.at(1).indexOf("<")).simplified().replace( " ", "" );
                QString var2 = splits.at(2).left(splits.at(2).indexOf("+")).simplified().replace( " ", "" );
                if((var !=  var1)| (var != var2))
                {
                    QString msg = "Your for-loop in line: ";
                    msg.append(QString::number(i+1));
                    msg.append(" contains different variables for counting. This is not allowed - Please rewrite your code.");
                    throw ToyException(msg);
                }
                else
                {
                    //insert variable declaration for for-loop-variable
                    QString firstBound = splits.at(0).right(splits.at(0).length() - splits.at(0).indexOf("=") - 1);
                    QString secondBound = splits.at(1).right(splits.at(1).length() - splits.at(1).indexOf("<") - 1);
                    bool ok = false;
                    QString value = QString::number(abs(firstBound.toInt(&ok, 10) - secondBound.toInt(&ok, 10)));
                    var.append("=").append(value);
                    var.insert(0, "shortint");
                    TreeNode* varNode = new VariableDeclarationNode(-1, TreeNode::variabledeclaration, var);
                    this->toyCode << varNode->getToyCode();
                    var.remove("shortint");

                    //copy all lines from inside for-loop and i-- statement into the list "whileList" and parse it as a while-loop
                    QStringList insideBrackets;
                    QString whileStatement = "while(";
                    var.remove("=");
                    var.remove(value);
                    whileStatement.append(var);
                    whileStatement.append("!=0) {");
                    insideBrackets << whileStatement;
                    lines.removeAt(0); //remove first line (for-loop-statement)
                    lines.removeAt(lines.length()-1); //remove closing bracket
                    insideBrackets.append(lines);

                    QString iminusminus = var.append("--");
                    insideBrackets << iminusminus; //insert i-- into body of while-loop
                    insideBrackets << "}";
                    newList.append(insideBrackets);
                }
            }
            //Parsing for(i = b; i < c; i--)
            else
            {
                QString var = splits.at(0).left(splits.at(0).indexOf("=")).simplified().replace( " ", "" );
                var.remove("shortint");
                QString var1 = splits.at(1).left(splits.at(1).indexOf("<")).simplified().replace( " ", "" );
                QString var2 = splits.at(2).left(splits.at(2).indexOf("-")).simplified().replace( " ", "" );
                if((var !=  var1)| (var != var2))
                {
                    QString msg = "Your for-loop in line: ";
                    msg.append(QString::number(i+1));
                    msg.append(" contains different variables for counting. This is not allowed - Please rewrite your code.");
                    throw ToyException(msg);
                }
                else
                {
                    //insert variable declaration for for-loop-variable
                    QString firstBound = splits.at(0).right(splits.at(0).length() - splits.at(0).indexOf("=") - 1);
                    QString secondBound = splits.at(1).right(splits.at(1).length() - splits.at(1).indexOf("<") - 1);
                    bool ok = false;
                    QString value = QString::number(abs(firstBound.toInt(&ok, 10) - secondBound.toInt(&ok, 10)));
                    var.append("=").append(value);
                    var.insert(0, "shortint");
                    TreeNode* varNode = new VariableDeclarationNode(-1, TreeNode::variabledeclaration, var);
                    this->toyCode << varNode->getToyCode();
                    var.remove("shortint");

                    //copy all lines from inside for-loop and i-- statement into the list "whileList" and parse it as a while-list
                    QStringList insideBrackets;
                    QString whileStatement = "while(";
                    var.remove("=");
                    var.remove(value);
                    whileStatement.append(var);
                    whileStatement.append("!=0) {");
                    insideBrackets << whileStatement;
                    lines.removeAt(0); //remove first line (for-loop-statement)
                    lines.removeAt(lines.length()-1); //remove closing bracket
                    insideBrackets.append(lines);

                    QString iplusplus = var.append("++");
                    insideBrackets << iplusplus; //insert i++ into body of while-loop
                    insideBrackets << "}";
                    newList.append(insideBrackets);
                }
            }
        }
    }
    return newList;
}

bool LoopNode::checkIfDeclared(QString ausdruck, QList<TreeNode* > vars)
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

    // If a forloop got parsed, the variable declaration is already in the toyCode
    if(!this->toyCode.isEmpty() && this->toyCode.at(0).startsWith(variable))
    {
        result = true;
    }

    return result;
}
