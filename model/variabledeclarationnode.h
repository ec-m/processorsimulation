#ifndef VARIABLEDECLARATIONNODE_H
#define VARIABLEDECLARATIONNODE_H
#include <QRegExp>
#include "model/treenode.h"
#include "model/toyexception.h"

/*
 * The class "VariableDeclarationNode" parses statements that
 * declare variables in Pseudo-C-Code. The allowed data types
 * are "short int", "bool" and "char".
 * @author: Eva Charlotte Mayer
 */

class VariableDeclarationNode : public TreeNode
{
public:
    // Constructor
    VariableDeclarationNode(int row, const TreeNode::TYPE &type, QString line);

    // Getters
    DATATYPE getDatatype();
    short getValue();
    QString getName();

private:
    // Parses the data type "short int" in pseudo c code
    bool parseShortInts(QString line);

    // Parses the data type "char" in pseudo c code
    bool parseChars(QString line);

    // Parses the data type "bool" in pseudo c code
    bool parseBools(QString line);

    // Produces the toy-Code for the variable declaration and
    // saves it in the TreeNode-Attribute "QStringList toyCode"
    void makeToyCode();

    // Attributes
    DATATYPE datatype;
    short value;
    QString name;

};

#endif // VARIABLEDECLARATIONNODE_H
