#ifndef ENTERKEYLISTENER_H
#define ENTERKEYLISTENER_H
#include <QObject>
#include <QKeyEvent>
#include <QTableWidget>
#include <QMainWindow>
#include <QApplication>

// @author: Daniel Muszkiet

class MainWindow;

class EnterKeyListener : public QObject
{
    Q_OBJECT
public:
    explicit EnterKeyListener(QObject *parent = 0);
    EnterKeyListener(QTableWidget *table, MainWindow *win);
    QTableWidget *table;
    MainWindow *window;
protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:

public slots:
};

#endif // ENTERKEYLISTENER_H
