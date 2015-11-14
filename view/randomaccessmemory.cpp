#include "randomaccessmemory.h"

// @author: Daniel Muszkiet

RandomAccessMemory::RandomAccessMemory()
{
    this->state = true;
    this->arr = new ushort[4096];
    for(int i = 0; i<4096; i++){
        arr[i] = 0;
    }
}

RandomAccessMemory::~RandomAccessMemory()
{
}

QRectF RandomAccessMemory::boundingRect() const
{
    return QRectF(594,356, 287,187);
}

void RandomAccessMemory::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

    painter->drawText(boundingRect(),Qt::AlignCenter,"RAM");
}

void RandomAccessMemory::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(state)
        state = false;
    else
        state = true;
}

