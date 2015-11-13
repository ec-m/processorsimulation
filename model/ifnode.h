#ifndef IFNODE_H
#define IFNODE_H
#include "model/treenode.h"
#include "model/toyexception.h"

class SyntaxTree;

/*
 * The class IfNode parses an if-statement in
 * Pseudo-C-Code. First, the if(...) statement
 * is converted into according ToyProcessor-Code.
 * Then a new SyntaxTree is established for the
 * code in the body of the if-statement.
 * @author: Eva Charlotte Mayer
 */

class IfNode : public TreeNode
{
public:
    // Constructor
    IfNode(int row, const TreeNode::TYPE &type, QStringList lines, QList<TreeNode*> vars);

private:
    // Attributes
    SyntaxTree* t;

    // Inserts the beginning of the ToyCode for an
    // if-condition aka LDA var, BRZ to end of statement
    void insertToyCode(QString variable, QString label);

    // Inserts body of if-statement and finally the end of
    // a if-statement into the ToyCode-List
    void insertToyCode(SyntaxTree* t);

    // Checks if variable used in if-Statement with (var != 0) has been declared
    bool checkIfDeclaredUnequalZero(QString ausdruck, QList<TreeNode* > vars);

    // Checks if variable used in if-Statement with (var) has been declared
    bool checkIfDeclaredBool(QString ausdruck, QList<TreeNode* > vars);

};

#endif // IFNODE_H
