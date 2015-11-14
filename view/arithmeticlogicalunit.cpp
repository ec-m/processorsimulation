#include "arithmeticlogicalunit.h"

// @author: Daniel Muszkiet

ArithmeticLogicalUnit::ArithmeticLogicalUnit()
{
    this->state = true;
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

ArithmeticLogicalUnit::~ArithmeticLogicalUnit()
{
}

QRectF ArithmeticLogicalUnit::boundingRect() const
{
    return this->polygon().boundingRect();
}

QPolygonF ArithmeticLogicalUnit::polygon() const
{
    QPolygonF p;
    p << QPointF(560,144) << QPointF(725,144) << QPointF(738,157)
      << QPointF(751,144) << QPointF(916,144) << QPointF(880,269) << QPointF(596,269);
    return p;
}

void ArithmeticLogicalUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawPolygon(polygon());

    QFont font = painter->font() ;

    /* twice the size than the current font size */
    painter->setPen(Qt::white);
    font.setPixelSize(20);
    font.setBold(true);

    /* set the modified font to the painter */
    painter->setFont(font);

    painter->drawText(boundingRect(),Qt::AlignCenter,"ALU");
}

void ArithmeticLogicalUnit::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(state)
        state = false;
    else
        state = true;
}

