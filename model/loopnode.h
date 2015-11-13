#ifndef LOOPNODE_H
#define LOOPNODE_H
#include "model/treenode.h"
#include "model/toyexception.h"

class SyntaxTree;

/*
 * The class LoopNode parses both while- and for-loops.
 * Parsing a while-loop:
 *      The while(...) statement is converted
 *      into according ToyProcessor-Code. Then
 *      a new SyntaxTree is established for the
 *      code in the body of the while-loop
 * Parsing a for-loop:
 *      The for(...) statement gets translated
 *      into an equivalent while-statement, which
 *      is then parsed as a while-loop.
 * @author: Eva Charlotte Mayer
 */


class LoopNode : public TreeNode
{
public:
    // Constructor
    LoopNode(int row, const TreeNode::TYPE &type, QStringList lines, QList<TreeNode *> vars);

private:
    // Attributes
    SyntaxTree* t;

    // Inserts the beginning of the ToyCode for a while loop
    // aka LDA var, BRZ to end of loop
    void insertToyCode(QString ausdruck, QString label1, QString label2);

    // Inserts body of while-loop and finally the end of
    // a while-loop into the ToyCode-List
    void insertToyCode(SyntaxTree *t, QString label1, QString label2);

    // Converts a for-loop into a while-loop, so it can be parsed as such
    QStringList convertForIntoWhileLoop(int i, QStringList lines);

    // Checks if variable used in loop-Statement has been declared
    bool checkIfDeclared(QString ausdruck, QList<TreeNode* > vars);
};

#endif // LOOPNODE_H
