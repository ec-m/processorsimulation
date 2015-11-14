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

