#ifndef PSEUDOCPREPROCESSOR_H
#define PSEUDOCPREPROCESSOR_H
#include <QStringList>
#include "model/toyexception.h"
#include "model/syntaxtree.h"

/*
 * The class "PseudoCPreprocessor" checks if the file and all the
 * contained lines that are parsed by the "PseudoCCompiler" are
 * formatted correctly. The "PseudoCPreprocessor" removes all for
 * the ToyProcessor irrelevant content from the lines, such as
 * comments, spaces, empty lines, semicolons. Once this is finished
 * a SyntaxTree is build from all the given statements.
 * @author: Eva Charlotte Mayer
 */

class PseudoCPreprocessor
{
private:
    // Attribute
    QStringList lines;

    // Removes spaces in strings, comments and empty lines
    void removeSpacesCommentsEmptyLines();

    // Removes all ";" at the end of a statements
    bool removeSemicolons();

    // Receives and appends all the ToyCode-lines from
    // the objects in the SyntaxTree and finally inserts
    // the necessary infinite loop in the end
    void getLinesFromSyntaxTree(SyntaxTree* t);

public:
    // Constructor
    PseudoCPreprocessor(QStringList lines);

    // Getter
    QStringList getLines();

    // Controls formatting process
    bool format();

};

#endif // PSEUDOCPREPROCESSOR_H
