#include "programcounter.h"

// @author: Daniel Muszkiet

ProgramCounter::ProgramCounter()
{
    this->state = true;
    this->pcVal = 0;
}

ProgramCounter::~ProgramCounter()
{
}

QRectF ProgramCounter::boundingRect() const
{
    return QRectF(352, 174, 165, 101);
}

void ProgramCounter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(rect,Qt::AlignHCenter,"PC");

    font.setPixelSize(15);
    font.setBold(false);
    rect.setY(rect.y()+22);
    painter->setFont(font);
    painter->drawText(rect,Qt::AlignHCenter,"Zähler:");
}

void ProgramCounter::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    state = !state;
}

