#include "accumulator.h"

// @author: Daniel Muszkiet

Accumulator::Accumulator()
{
    this->state = true;
    this->curValue = 0;
}

Accumulator::~Accumulator()
{
}

QRectF Accumulator::boundingRect() const
{
    return QRectF(750,-49, 166, 105);
}

void Accumulator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    QRectF rect = boundingRect();
    rect.setY(rect.y()+10);
    painter->drawText(rect,Qt::AlignHCenter,"ACCU");
    font.setPixelSize(15);
    font.setBold(false);
    rect.setY(rect.y()+22);
    painter->setFont(font);
    painter->drawText(rect,Qt::AlignHCenter,"Inhalt:");
}

void Accumulator::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{  
    update();
    if(state)
        state = false;
    else
        state = true;
}

