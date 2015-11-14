#ifndef ARROWTAKTSTEURWERK_H
#define ARROWTAKTSTEURWERK_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class ArrowTaktSteuerwerk : public QGraphicsItem
{
public:
    bool isActive;
    ArrowTaktSteuerwerk();
    ~ArrowTaktSteuerwerk();
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

#endif // ARROWTAKTSTEURWERK_H
