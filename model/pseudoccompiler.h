#ifndef PSEUDOCCOMPILER_H
#define PSEUDOCCOMPILER_H
#include <QStringList>
#include <QDebug>
#include <QString>
#include <QFile>
#include "model/pseudocpreprocessor.h"


/*
 * The class "PseudoCCompiler" is responsible for the whole
 * parsing process of pseudo-c-code. If a file ends with
 * "*.toyc", then the PseudoCCompiler is created, reads the
 * lines out of the given file and converts them into normal
 * ToyProcessor-Code. The first step is the passing on of
 * all lines to the PseudoCPreprocessor. If the parsing there
 * wents well, the class "Parser" can receive the converted
 * lines from the PseudoCCompiler.
 * @author: Eva Charlotte Mayer
 */


class PseudoCCompiler
{
private:
    // Reads Pseudo-C-Code from file
    void readCFromFile(QString filename);

    // Optimizes the ToyCode such that STO a and
    // LDA a right behind each other get cut
    void optimize();

public:   
    // Constructor
    PseudoCCompiler();

    // Attributes
    QStringList lines;
    PseudoCPreprocessor* preprocessor;

    // Controls the whole parsing process of pseudo-c-code
    void controlCParsing(QString filename);

    // Getter
    QStringList getLines();
};

#endif // PSEUDOCCOMPILER_H
