/*
 * This file is part of Processorsimulation.
 * Author: Eva Charlotte Mayer <eva-charlotte.mayer@posteo.de>
 *
 * The Processorsimulation is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the Free
 * Software Foundation, Version 3.
 *
 * The Processorsimulation is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
