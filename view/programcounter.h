#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ProgramCounter : public QGraphicsItem
{
public:
    ProgramCounter();
    ~ProgramCounter();
    short pcVal;

private:
    bool state;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PROGRAMCOUNTER_H
