#ifndef RAM_H
#define RAM_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class RandomAccessMemory : public QGraphicsItem
{
public:
    RandomAccessMemory();
    ~RandomAccessMemory();
    ushort* arr;

private:
    bool state;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // RAM_H
