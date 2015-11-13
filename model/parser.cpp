#include "model/parser.h"

// @author: Eva Charlotte Mayer

Parser::Parser()
{
    this->opCodes = new short[OPCODESLENGTH];
    this->opCodesCopy = new short[OPCODESLENGTH];
    for(int i = 0; i < OPCODESLENGTH; i++)
    {
        this->opCodes[i] = 0;
        this->opCodesCopy[i] = 0;
    }
    this->preparser = new Preparser();
}

short* Parser::getOpCodes()
{
    // Needs to be copied so that model can change values
    short* newArr = new short[OPCODESLENGTH];
    for(int i = 0; i < OPCODESLENGTH; i++)
    {
        newArr[i] = this->opCodesCopy[i];
    }
    return newArr;
}

int Parser::getOpCodesLength()
{
    return OPCODESLENGTH;
}

void Parser::controlParsing(QString filename)
{
    try {
        if(this->preparser->checkFileName(filename))
        {
            QRegExp rx("*.toy");
            QRegExp rxC("*.toyc");
            rx.setPatternSyntax(QRegExp::Wildcard);
            rxC.setPatternSyntax(QRegExp::Wildcard);
            if(rx.exactMatch(filename))
            {
                this->readFromFile(filename);
            }
            else
            {
                this->pseudoCCompiler = new PseudoCCompiler();
                this->pseudoCCompiler->controlCParsing(filename);
                this->lines = this->pseudoCCompiler->getLines();
            }
        }
        if(this->preparser->format(this->lines))
        {
            this->lines = this->preparser->getLines();
        }

        // Parse lines into array of Row-Objects
        this->rows = parse();

        // Store all objects in Row-Array as shorts in array "opcodes"
        store();

        // Check if file ends with infinite loop
        bool infLoopExists = this->preparser->checkInfiniteLoop(this->opCodes, this->rows);

        // If file does not end in infinite loop erase all stored data
        if(!infLoopExists)
        {
            for(int i = 0; i < OPCODESLENGTH; i++)
            {
                this->opCodes[i] = 0;
            }
            this->lines.clear();
            this->rows.clear();
            QString msg = QString("File must end in infinite loop.");
            throw ToyException(msg);
        }
        else
        {
            this->copyOpCodes();
        }
    }
    catch (ToyException e)
    {
        // Sends msg to GUI so that ToyException can be shown to User
        Message parsererror(Message::ParserError);
        QString content = (QString) e.what();
        parsererror.content = &content;
        emit(sendMessage(parsererror));
        clearAll();
    }
    catch (...)
    {
    }

}

void Parser::readFromFile(QString filename)
{
    //Einlesen aller Zeilen
    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            this->lines << in.readLine();
        }
    }
    inputFile.close();
}

QList<Row *> Parser::parse()
{
    QList<Row *> rows;

    QRegExp rxBin("^(^[0-1]{16,16})$");
    QRegExp rxBinRAM("^(^:[0-1]{16,16}:[0-1]{16,16})$");
    QRegExp rxHex("^(^\\$((\\d|[A-F,a-f]){4,4}))$");
    QRegExp rxHexRAM("^(^:\\$((\\d|[A-F,a-f]){4,4}):\\$((\\d|[A-F]){4,4}))$");
    QRegExp rxMnemonic("^(^(STO(\\d{1,2}|[A-Z,a-z]+)|LDA(\\d{1,2}|[A-Z,a-z]+)|BRZ(\\d{1,2}|[A-Z,a-z]+)|ADD(\\d{1,2}|[A-Z,a-z]+)|SUB(\\d{1,2}|[A-Z,a-z]+)|OR(\\d{1,2}|[A-Z,a-z]+)|AND(\\d{1,2}|[A-Z,a-z]+)|XOR(\\d{1,2}|[A-Z,a-z]+)|NOT|INC|DEC|ZRO))$");
    QRegExp rxMnemonicRAM("^(^:\\d+:\\d+)$");

    for(int i = 0; i < this->lines.length(); i++)
    {
        if (rxBin.exactMatch(this->lines.at(i)))
        {
            Row* r = new Row(this->lines.at(i), i, Row::binary, Row::instruction);
            rows << r;
            continue;
        }
        else if (rxBinRAM.exactMatch(this->lines.at(i)))
        {
            Row* r = new Variable(this->lines.at(i), i, Row::binary, Row::variable);
            rows << r;
            continue;
        }
        else if (rxHex.exactMatch(this->lines.at(i)))
        {
            QString hex = this->lines.at(i);
            Row* r = new Row(hex.remove("$"), i, Row::hexa, Row::instruction);
            rows << r;
            continue;
        }
        else if (rxHexRAM.exactMatch(this->lines.at(i)))
        {
            Row* r = new Variable(this->lines.at(i), i, Row::hexa, Row::variable);
            rows << r;
            continue;
        }
        else if (rxMnemonic.exactMatch(this->lines.at(i)))
        {
            Row* r = new Row(this->lines.at(i), i, Row::mnemonic, Row::instruction);
            rows << r;
            continue;
        }
        else if (rxMnemonicRAM.exactMatch(this->lines.at(i)))
        {
            Row* r = new Variable(this->lines.at(i), i, Row::mnemonic, Row::variable);
            rows << r;
            continue;
        }
    }

    return rows;
}


void Parser::store()
{
    int count = 0;
    for(int i = 0; i < this->rows.length(); i++)
    {
        if(count >= 4096)
        {
            QString msg = QString("Programm is too big - RAM cannot hold so many Opcodes and settings. Please reduce!");
            throw ToyException(msg);
        }
        else
        {
            // Dies nur für OpCodes machen --> falls type = instruction
            if (this->rows.at(i)->getType() == Row::instruction)
            {
                if (this->opCodes[count] != 0)
                {
                    QString msg = QString("Conflict with RAM-Setting while storing opcode - Please chose higher RAM-address for your variables.");
                    throw ToyException(msg);
                }
                else
                {
                    this->opCodes[count] = this->rows.at(i)->getOpcode();
                    count++;
                    continue;
                }
            }
            else if (this->rows.at(i)->getType() == Row::variable)
            {
                if (this->opCodes[this->rows.at(i)->getPlace()] != 0)
                {
                    QString msg = QString("Conflict with RAM-Setting while storing opcode - Please chose higher RAM-address for your variables.");
                    throw ToyException(msg);
                }
                else
                {
                    this->opCodes[this->rows.at(i)->getPlace()] = this->rows.at(i)->getOpcode();
                    continue;
                }
            }
        }
    }
}

void Parser::showRows(const MODE &m)
{
    switch (m)
    {
    case binary :
        for(int i = 0; i < this->rows.length(); i++)
        {
            if (this->rows.at(i)->getType() == Row::variable)
            {
                short address = this->rows.at(i)->getPlace();
                short value = this->rows.at(i)->getOpcode();
                QString theAddress = QString::number(address, 2);
                while(theAddress.length() < 16)
                {
                    theAddress.insert(0, "0");
                }
                QString theValue = QString::number(value, 2);
                while(theValue.length() < 16)
                {
                    theValue.insert(0, "0");
                }
                QString binLine = ":";
                binLine.append(theAddress);
                binLine.append(":");
                binLine.append(theValue);
                qDebug() << binLine;
                continue;
            }
            qDebug() << this->rows.at(i)->showAsBin();
        }
        break;
    case hexadecimal :
        for(int i = 0; i < this->rows.length(); i++)
        {
            if (this->rows.at(i)->getType() == Row::variable)
            {
                short address = this->rows.at(i)->getPlace();
                short value = this->rows.at(i)->getOpcode();
                QString theAddress = QString::number(address, 16);
                while(theAddress.length() < 4)
                {
                    theAddress.insert(0, "0");
                }
                QString theValue = QString::number(value, 16);
                while(theValue.length() < 4)
                {
                    theValue.insert(0, "0");
                }
                QString binLine = ":$";
                binLine.append(theAddress);
                binLine.append(":$");
                binLine.append(theValue);
                qDebug() << binLine;
                continue;
            }
            qDebug() << this->rows.at(i)->showAsHexa();
        }
        break;
    case mnemonic :
        for(int i = 0; i < this->rows.length(); i++)
        {
            if (this->rows.at(i)->getType() == Row::variable)
            {
                short address = this->rows.at(i)->getPlace();
                short value = this->rows.at(i)->getOpcode();
                QString theAddress = QString::number(address, 10);
                QString theValue = QString::number(value, 10);
                QString binLine = ":";
                binLine.append(theAddress);
                binLine.append(":");
                binLine.append(theValue);
                qDebug() << binLine;
                continue;
            }
            qDebug() << this->rows.at(i)->showAsMnemonic();
        }
        break;
    case ram :
        for(int i = 0; i < this->getOpCodesLength(); i++)
        {
            qDebug() << this->getOpCodes()[i];
        }
    }
}

void Parser::copyOpCodes()
{
    for(int i = 0; i < OPCODESLENGTH; i++)
    {
        this->opCodesCopy[i] = this->opCodes[i];
    }
    clearAll();

    // Send Message to GUI with number of opCodes
    // so only opCodes and not RAM-Setting get
    // converted in different modi (hexa, dec..)
    Message msg(Message::GetOpCodeRows);
    int content = this->preparser->getNumberOfOpCodes();
    msg.content = &content;
    emit(sendMessage(msg));
}

void Parser::clearAll()
{
    for(int i = 0; i < OPCODESLENGTH; i++)
    {
        this->opCodes[i] = 0;
    }
    this->preparser->clearLines();
    this->lines.clear();
}
