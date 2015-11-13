#include "pseudoccompiler.h"

// @author: Eva Charlotte Mayer

PseudoCCompiler::PseudoCCompiler()
{
}

QStringList PseudoCCompiler::getLines()
{
    return this->lines;
}


void PseudoCCompiler::controlCParsing(QString filename)
{
    this->readCFromFile(filename);
    this->preprocessor = new PseudoCPreprocessor(this->lines);
    if(this->preprocessor->format())
    {
        this->lines = this->preprocessor->getLines();
    }
    this->optimize();
}

void PseudoCCompiler::readCFromFile(QString filename)
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


void PseudoCCompiler::optimize()
{
    for(int i = 0; i < this->lines.length() - 1; i++)
    {
        QString a = this->lines.at(i);
        QString b = this->lines.at(i + 1);
        if(a.startsWith("STO") && b.startsWith("LDA")
                && a.right(a.length() - 3) == b.right(b.length() - 3))
        {
            this->lines.removeAt(i);
            this->lines.removeAt(i);
        }
    }
}
