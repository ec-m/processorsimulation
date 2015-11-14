#ifndef ARROWIRPROGRAMCOUNTER_H
#define ARROWIRPROGRAMCOUNTER_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArrowIrProgramcounter : public QGraphicsItem
{
public:
    ArrowIrProgramcounter();
    ~ArrowIrProgramcounter();
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

#endif // ARROWIRPROGRAMCOUNTER_H
