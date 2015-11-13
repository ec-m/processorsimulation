#include "variabledeclarationnode.h"

// @author: Eva Charlotte Mayer

VariableDeclarationNode::VariableDeclarationNode(int row, const TYPE &type, QString line) : TreeNode(row, type), datatype(datatype)
{
    QRegExp rxShortInt("^(^shortint)([A-Z,a-z,\\d]+)=((\\d)+|(\\$(\\d|[A-F,a-f])+))"); //Regex for variable declaration
    QRegExp rxChar("^(^char)([A-Z,a-z,\\d]+)=((\\d)+|(\\$(\\d|[A-F,a-f])+))"); //Regex for variable declaration
    QRegExp rxBool("^(^bool)([A-Z,a-z,\\d]+)=((\\d)+|(\\$(\\d|[A-F,a-f])+))"); //Regex for variable declaration

    if(rxShortInt.indexIn(line) != -1)
    {
        QRegExp rx("^short((\\s)*)int((\\s)*)");
        line.remove(rx);
        if(parseShortInts(line))
        {
            this->datatype = VariableDeclarationNode::shortinttype;
        }
        else
        {
            QString msg = "short-int-Variable is out of range in line: ";
            msg.append(QString::number(row+1));
            throw ToyException(msg);
        }
    }
    else
    {
        if(rxChar.indexIn(line) != -1)
        {
            QRegExp rx("^char((\\s)*)");
            line.remove(rx);
            if(parseChars(line))
            {
                this->datatype = VariableDeclarationNode::chartype;
            }
            else
            {
                QString msg = "char-Variable is out of range in line: ";
                msg.append(QString::number(row+1));
                throw ToyException(msg);
            }
        }
        else
        {
            if(rxBool.indexIn(line) != -1)
            {
                QRegExp rx("^bool((\\s)*)");
                line.remove(rx);
                if(parseBools(line))
                {
                    this->datatype = VariableDeclarationNode::booltype;
                }
                else
                {
                    QString msg = "bool-Variable can only equal 0 or 1 in line: ";
                    msg.append(QString::number(row+1));
                    throw ToyException(msg);
                }
            }
            else
            {
                QString msg = "No valid data type used in line: ";
                msg.append(QString::number(row+1));
                throw ToyException(msg);
            }
        }
    }

    makeToyCode();
}


//parses the data type "short int" in pseudo c code
bool VariableDeclarationNode::parseShortInts(QString line)
{
    bool result = true;
    QRegExp rxVar("^(^[A-Z,a-z,\\d]+)=((\\d)+|(\\$(\\d|[A-F,a-f])+))"); //Regex for variable declaration
    //Get name and value of variable
    QString value;
    if (rxVar.indexIn(line) != -1)
    {
        value = rxVar.cap(2);
    }
    int val;
    bool ok = false;
    if(value.startsWith("$"))
    {
        value.remove("$");
        val = value.toInt(&ok, 16); //converts potential hex value of variable into short
    }
    else
    {
        val = value.toInt(&ok, 10);
    }

    //Check if value is in allowed range
    if( !(val >= 0 && val <= 65535) )
    {
        result = false;
    }
    else
    {
        this->name = rxVar.cap(1);
        this->value = val;
    }
    return result;
}

//parses the data type "char" in pseudo c code
bool VariableDeclarationNode::parseChars(QString line)
{
    bool result = true;
    QRegExp rxVar("^(^[A-Z,a-z,\\d]+)=((\\d)+|(\\$(\\d|[A-F,a-f])+))"); //Regex for variable declaration
    //Get name and value of variable
    QString value;
    if (rxVar.indexIn(line) != -1)
    {
        value = rxVar.cap(2);
    }
    int val;
    bool ok = false;
    if(value.startsWith("$"))
    {
        value.remove("$");
        val = value.toInt(&ok, 16); //converts potential hex value of variable into short
    }
    else
    {
        val = value.toInt(&ok, 10);
    }

    //Check if value is in allowed range
    if( !(val >= 0 && val <= 255) )
    {
        result = false;
    }
    else
    {
        this->name = rxVar.cap(1);
        this->value = val;
    }
    return result;
}

//parses the data type "bool" in pseudo c code
bool VariableDeclarationNode::parseBools(QString line)
{
    bool result = true;
    QRegExp rxVar("^(^[A-Z,a-z,\\d]+)=((\\d)+|(\\$(\\d|[A-F,a-f])+))"); //Regex for variable declaration
    //Get name and value of variable
    QString value;
    if (rxVar.indexIn(line) != -1)
    {
        value = rxVar.cap(2);
    }
    int val;
    bool ok = false;
    if(value.startsWith("$"))
    {
        value.remove("$");
        val = value.toInt(&ok, 16); //converts potential hex value of variable into short
    }
    else
    {
        val = value.toInt(&ok, 10);
    }

    //Check if value is in allowed range
    if( !(val == 0 || val == 1) )
    {
        result = false;
    }
    else
    {
        this->name = rxVar.cap(1);
        this->value = val;
    }
    return result;
}

TreeNode::DATATYPE VariableDeclarationNode::getDatatype()
{
    return this->datatype;
}

short VariableDeclarationNode::getValue()
{
    return this->value;
}

QString VariableDeclarationNode::getName()
{
    return this->name;
}

void VariableDeclarationNode::makeToyCode()
{
    QStringList l;
    QString s = this->name;
    s.append("=");
    s.append(QString::number(this->value));
    l << s;
    this->toyCode = l;
}
