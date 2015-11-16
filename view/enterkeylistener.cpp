/*
 * This file is part of Processorsimulation.
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

#include "enterkeylistener.h"
#include "mainwindow.h"
#define ENTER 16777220

// @author: Daniel Muszkiet

EnterKeyListener::EnterKeyListener(QObject *parent)
{
}

EnterKeyListener::EnterKeyListener(QTableWidget *t, MainWindow *w)
{
    this->table = t;
    this->window = w;
}


bool EnterKeyListener::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if(keyEvent->key() == ENTER){
            int row = table->currentRow();
            if(row != -1){
                QString oldVal = table->item(row,0)->text();
                QApplication::processEvents();
                QString newVal = table->item(row,0)->text();
                window->RAMupdate(row,0,newVal, oldVal);
            }
        }
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

