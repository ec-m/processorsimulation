#include "preparser.h"

// @author: Eva Charlotte Mayer

Preparser::Preparser()
{
}

QStringList Preparser::getLines()
{
    return this->lines;
}

int Preparser::getNumberOfOpCodes()
{
    return this->numberOfOpCodes;
}


bool Preparser::checkFileName(QString filename)
{
    QRegExp rx("*.toy");
    QRegExp rxC("*.toyc");
    rx.setPatternSyntax(QRegExp::Wildcard);
    rxC.setPatternSyntax(QRegExp::Wildcard);
    if(!(rx.exactMatch(filename) || rxC.exactMatch(filename)))
    {
        QString msg = "Wrong file format.";
        throw ToyException(msg);
        return false;
    }
    return true;
}

bool Preparser::format(QStringList list)
{
    bool b = removeSpacesCommentsEmptyLines(list);
    if (b)
    {
        this->lines = replaceVariables(this->lines, countOpCodes(this->lines, this->lines.length()));
        this->lines = replaceLables(this->lines);
        if(!checkForUndeclaredLabel(this->lines) || !checkForUndeclaredVariable(this->lines))
        {
            return false;
        }
    }
    return true;
}

bool Preparser::removeSpacesCommentsEmptyLines(QStringList list)
{
    for(int i = 0; i < list.length(); i++)
    {
        QString line = list.at(i);

        //remove spaces in lines
        line.simplified();
        line.trimmed();
        line.replace(QRegExp("((\\t)*)"), "");
        line.replace(QRegExp("((\\s)*)"), "");

        //ignores empty lines
        if(line.isEmpty())
        {
            continue;
        }

        //ignores comments
        QString comment = "#";
        if(line.contains(comment))
        {
            if(line.startsWith(comment))
            {
                //lines that only contain comments are also ignored
                continue;
            }
            else
            {
                int place = line.indexOf(comment);
                line.remove(place, line.length()); //comments are cut from lines
            }

        }

        QRegExp rxBin("^(^[0-1]{16,16})$");
        QRegExp rxBinRAM("^(^:[0-1]{16,16}:[0-1]{16,16})$");
        QRegExp rxHex("^(^\\$((\\d|[A-F,a-f]){4,4}))$");
        QRegExp rxHexRAM("^(^:\\$((\\d|[A-F,a-f]){4,4}):\\$((\\d|[A-F]){4,4}))$");
        QRegExp rxMnemonic("^(^(STO(\\d{1,2}|[A-Z,a-z]+)|LDA(\\d{1,2}|[A-Z,a-z]+)|BRZ(\\d{1,2}|[A-Z,a-z]+)|ADD(\\d{1,2}|[A-Z,a-z]+)|SUB(\\d{1,2}|[A-Z,a-z]+)|OR(\\d{1,2}|[A-Z,a-z]+)|AND(\\d{1,2}|[A-Z,a-z]+)|XOR(\\d{1,2}|[A-Z,a-z]+)|NOT|INC|DEC|ZRO))$");
        QRegExp rxMnemonicRAM("^(^:\\d+:\\d+)$");
        QRegExp rxVar("^(^[A-Z,a-z,\\d]+)=((\\d)+|(\\$(\\d|[A-F,a-f])+))");
        QRegExp rxLabel("^(^[A-Z,a-z]+:)");
        if (!(rxBin.exactMatch(line) || rxHex.exactMatch(line) || rxMnemonic.exactMatch(line)
              || rxBinRAM.exactMatch(line) || rxHexRAM.exactMatch(line) || rxMnemonicRAM.exactMatch(line)
              || rxVar.exactMatch(line) || rxLabel.exactMatch(line)))
        {
            QString msg = QString("There was something misspelled in line: ").append(QString::number(i+1));
            throw ToyException(msg);
            return false;
        }
        else
        {
            //store in list of formatted Lines
            this->lines << line;
        }
    }
    return true;
}

QStringList Preparser::replaceVariables(QStringList list, int numberOfOpCodes)
{
    for(int i = 0; i < list.length(); i++)
    {
        QString line1 = list.at(i);

        //Regex for variable declaration
        QRegExp rxVar("^(^[A-Z,a-z,\\d]+)=((\\d)+|(\\$(\\d|[A-F,a-f])+))");
        if (rxVar.indexIn(line1) != -1)
        {
            //Get name and value of variable
            QString name = rxVar.cap(1);
            QString value = rxVar.cap(2);
            if(value.startsWith("$"))
            {
                value.remove("$");
                bool ok = false;
                //converts potential hex value of variable into short
                value = QString::number(value.toUShort(&ok, 16),10);
            }

            //Replace all accounters of variable in other lines with an address behind all the Opcodes in final array of shorts
            QString rxOpCodeWithVarString = "^(^(STO|LDA|ADD|SUB|OR|AND|XOR))";
            rxOpCodeWithVarString.append(name);
            QRegExp rxOpCodeWithVar(rxOpCodeWithVarString);
            for(int j = 0; j < list.length(); j++)
            {
                QString line2 = list.at(j);
                if(rxOpCodeWithVar.indexIn(line2) != -1)
                {
                    QRegExp rxName(name);
                    //address is supposed to be behind all Opcodes in final array of shorts
                    line2.replace(rxName, QString::number(numberOfOpCodes));
                    list.replace(j, line2);
                }
            }
            QString ramSetting = ":";
            ramSetting.append(QString::number(numberOfOpCodes));
            ramSetting.append(":");
            ramSetting.append(value);
            //Declaration of variables gets overwritten by RAM-Setting ":addressBehindOpCodes:value"
            list.replace(i, ramSetting);
            numberOfOpCodes++;
        }
    }
    return list;
}


QStringList Preparser::replaceLables(QStringList list)
{
    for(int i = 0; i < list.length(); i++)
    {
        QRegExp rxLabel("^(^[A-Z,a-z]+:)");
        QString line1 = list.at(i);
        if (rxLabel.indexIn(line1) != -1)
        {
            QString labelName = rxLabel.cap(1);
            labelName.remove(":");
            //gets position of OpCode after label in final array of shorts
            int labelAddress = countOpCodes(list, i);
            QString rxBRZ = "^BRZ";
            rxBRZ.append(labelName);
            rxBRZ.append("$");
            QRegExp rxOpCodeWithLabel(rxBRZ);
            for(int j = 0; j < list.length(); j++)
            {
                QString line2 = list.at(j);
                if (rxOpCodeWithLabel.indexIn(line2) != -1)
                {
                    //Replaces label in OpCode "BRZ label" with RAM-Address of OpCode from the position of the label
                    QRegExp rxName(labelName);
                    line2.replace(rxName, QString::number(labelAddress));
                    list.replace(j, line2);
                }
            }
            list.removeAt(i);
            i--;
        }
    }
    return list;
}

bool Preparser::checkForUndeclaredVariable(QStringList list)
{
    for(int k = 0; k < list.length(); k++)
    {
        QString line = list.at(k);
        QRegExp rxOpCodeWithUnusedVariable("^(^(STO|LDA|ADD|SUB|OR|AND|XOR))([A-Z,a-z]+)");
        if (rxOpCodeWithUnusedVariable.indexIn(line) != -1)
        {
            QString msg = rxOpCodeWithUnusedVariable.cap(3);
            msg.insert(0, "Undeclared variable: ");
            throw ToyException(msg);
            return false;
        }
    }
    return true;
}

bool Preparser::checkForUndeclaredLabel(QStringList list)
{
    for(int k = 0; k < list.length(); k++)
    {
        QString line = list.at(k);
        QRegExp rxOpCodeWithUnusedLabel("^(BRZ)([A-Z,a-z]+)");
        if (rxOpCodeWithUnusedLabel.indexIn(line) != -1)
        {
            QString msg = rxOpCodeWithUnusedLabel.cap(2);
            msg.insert(0, "Undeclared label: ");
            throw ToyException(msg);
            return false;
        }
    }
    return true;
}


int Preparser::countOpCodes(QStringList list, int position)
{
    int count = 0;
    QRegExp rxOpCode("^(^(STO|LDA|BRZ|ADD|SUB|OR|AND|XOR|NOT|INC|DEC|ZRO))");
    for(int i = position - 1; i >= 0; i--)
    {
        if (rxOpCode.indexIn(list.at(i)) != -1)
        {
            count++;
        }
    }
    this->numberOfOpCodes = count;
    return count;
}


/*
 * Idee:
 * opcodes[#Anzahl_opcodes - 1] == BRZ <address>
 * <address> == #Anzahl_opcodes - 2
 * opcodes[#Anzahl_opcodes - 2] == ZRO
 */
bool Preparser::checkInfiniteLoop(short* opcodes, QList<Row* > rows)
{



    QStringList list;
    for(int i = 0; i < rows.length(); i++)
    {
        if(rows[i]->getType() != Row::variable)
        {
            list << rows[i]->showAsMnemonic();
        }
    }

    int count = countOpCodes(list, list.length());

    QString brz = QString::number(opcodes[count - 1], 2);
    if(brz.length() > 16)
    {
        brz = brz.right(16);
    }
    while(brz.length() < 16)
    {
        brz.insert(0, "0");
    }
    QString zro = QString::number(opcodes[count - 2], 2);
    if(zro.length() > 16)
    {
        zro = zro.right(16);
    }
    while(zro.length() < 16)
    {
        zro.insert(0, "0");
    }

    bool ok = false;
    if(!brz.startsWith("0010") || zro != "1011000000000000" || brz.right(12).toInt(&ok, 2) != count - 2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Preparser::clearLines()
{
    this->lines.clear();
}
