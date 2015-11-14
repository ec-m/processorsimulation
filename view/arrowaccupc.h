#ifndef ARROWACCUPC_H
#define ARROWACCUPC_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArrowAccuPc : public QGraphicsItem
{
public:
    bool isActive;
    ArrowAccuPc();
    ~ArrowAccuPc();
    void activate(bool t);
    void setActiveColor(QColor c);
    void setNotActiveColor(QColor c);

private:
    QColor activeColor;
    QColor notActiveColor;    
    QRectF boundingRect()const;
    QPolygonF polygon()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ARROWACCUPC_H
