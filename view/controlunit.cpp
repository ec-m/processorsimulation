#include "controlunit.h"

// @author: Daniel Muszkiet

ControlUnit::ControlUnit()
{
    this->state = true;
}

ControlUnit::~ControlUnit()
{
}

QRectF ControlUnit::boundingRect() const
{
    return QRectF(0,178,170,209);
}

void ControlUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(boundingRect(),Qt::AlignCenter,"ControlUnit");
}

void ControlUnit::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(state)
        state = false;
    else
        state = true;
}

