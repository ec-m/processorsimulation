#include "clock.h"

// @author: Daniel Muszkiet

Clock::Clock()
{
    this->state = true;
}

Clock::~Clock()
{
}

QRectF Clock::boundingRect() const
{
     return QRectF(0,0,88,87);
}

void Clock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush blueBrush(QColor(20, 49, 99,255));

    QPen blackPen;
    blackPen.setWidth(1);

    if(state)
        blackPen.setColor(Qt::black);
    else
        blackPen.setColor(Qt::red);

    painter->setPen(blackPen);
    painter->setBrush(blueBrush);
    painter->drawRect(boundingRect());

    QFont font = painter->font() ;

    /* twice the size than the current font size */
    painter->setPen(Qt::white);
    font.setPixelSize(20);
    font.setBold(true);

    /* set the modified font to the painter */
    painter->setFont(font);

    painter->drawText(boundingRect(),Qt::AlignCenter,"Clock");
}


void Clock::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(state)
        state = false;
    else
        state = true;
}

