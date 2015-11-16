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

#include "pseudocpreprocessor.h"

PseudoCPreprocessor::PseudoCPreprocessor(QStringList lines)
{
    this->lines = lines;
}

QStringList PseudoCPreprocessor::getLines()
{
    return this->lines;
}

bool PseudoCPreprocessor::format()
{
    this->removeSpacesCommentsEmptyLines();
    if(this->removeSemicolons())
    {
        QList<TreeNode* > empty; // Since in the beginning there are no variable declarations
        SyntaxTree* t = new SyntaxTree(this->lines, 0, empty);
        t->makeTree();
        t->checkTree();
        this->getLinesFromSyntaxTree(t);
        return true;
    }
    return false;
}

void PseudoCPreprocessor::removeSpacesCommentsEmptyLines()
{
    for(int i = 0; i < this->lines.length(); i++)
    {
        QString line = this->lines.at(i);

        //remove spaces in lines
        line.simplified();
        line.trimmed();
        line.replace(QRegExp("((\\t)*)"), "");
        line.replace(QRegExp("((\\s)*)"), "");

        //ignores empty lines
        if(line.isEmpty())
        {
            continue;
        }

        //ignores comments
        QString comment = "#";
        if(line.contains(comment))
        {
            if(line.startsWith(comment))
            {
                //lines that only contain comments are replaced by empty lines
                this->lines.replace(i, "");
                continue;
            }
            else
            {
                int place = line.indexOf(comment);
                line.remove(place, line.length()); //comments are cut from lines
            }

        }

        //replaces old line with formatted line in list
        this->lines.replace(i, line);
    }
}

bool PseudoCPreprocessor::removeSemicolons() //removes all ";" at the end of a statements
{
    for(int i = 0; i < this->lines.length(); i++)
    {
        QString line = this->lines.at(i);

        if(line.isEmpty())
        {
            continue;
        }
        if(!line.endsWith(";"))
        {
            if(line.endsWith("{") || line.endsWith("}") || line.endsWith(")"))
            {
                continue;
            }
            else
            {
                QString msg = "You forgot your semicolon in line: ";
                msg.append(QString::number(i+1));
                throw ToyException(msg);
                return false;
            }
        }
        else
        {
            line.remove(";");
            this->lines.replace(i, line);
        }
    }
    return true;
}

void PseudoCPreprocessor::getLinesFromSyntaxTree(SyntaxTree *t)
{
    this->lines.clear();
    for(int i = 0; i < t->getNodes().length(); i++)
    {
        this->lines << t->getNodes()[i]->getToyCode();
    }
    this->lines << "infLoop:";
    this->lines << "ZRO";
    this->lines << "BRZ infLoop";
}
