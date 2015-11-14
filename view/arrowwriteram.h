#ifndef ARROWWRITERAM_H
#define ARROWWRITERAM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QLabel>

// @author: Daniel Muszkiet

class ArrowWriteRam : public QGraphicsItem
{
public:
    ArrowWriteRam();
    ~ArrowWriteRam();
    void activate(bool t);
    void setActiveColor(QColor c);
    void setNotActiveColor(QColor c);

private:
    bool isActive;
    QColor activeColor;
    QColor notActiveColor;
    QRectF boundingRect()const;
    QPolygonF polygon()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ARROWWRITERAM_H
