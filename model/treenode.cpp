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

#include "treenode.h"

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
