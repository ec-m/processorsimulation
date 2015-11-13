#ifndef TREENODE_H
#define TREENODE_H
#include <QString>
#include <QStringList>

/*
 * The class "TreeNode" receives lines from the "SyntaxTree"
 * and by them defines objects containing the toyCode
 * the row-number and also the information, if the line contains
 * an loop-statement or a variable declaration.
 * @author: Eva Charlotte Mayer
 */

class TreeNode
{
public:
    // Enumeration for TreeNode-Elements
    enum TYPE {
        variabledeclaration,
        operation,
        ifstatement,
        whileloop,
        forloop
    };

    // Enumeration for VariableDeclarationNode-Elements
    enum DATATYPE {
        shortinttype,
        chartype,
        booltype
    };

    // Enumeration for OperationNode-Elements
    enum OPERATION {
        Plus,
        Minus,
        Or,
        And,
        Xor,
        Not,
        Inc,
        Dec
    };

    // Constructor
    TreeNode(int row, const TYPE &type);

    // Getters
    TYPE getType();
    int getRow();
    QStringList getToyCode();
    virtual DATATYPE getDatatype() {};
    virtual short getValue() {};
    virtual QString getName() {};
    virtual QString getResult() {};
    virtual QString getOperand1() {};
    virtual QString getOperand2() {};
    virtual OPERATION getOperation() {};

protected:
    // Attributes
    const TYPE type;
    int row;
    QStringList toyCode;
};

#endif // TREENODE_H
