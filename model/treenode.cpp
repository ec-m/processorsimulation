#include "treenode.h"

// @author: Eva Charlotte Mayer

TreeNode::TreeNode(int row, const TYPE &type) : type(type)
{
    this->row = row;
}

TreeNode::TYPE TreeNode::getType()
{
    return this->type;
}

int TreeNode::getRow()
{
    return this->row;
}

QStringList TreeNode::getToyCode()
{
    return this->toyCode;
}
