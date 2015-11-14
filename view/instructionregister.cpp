#include "instructionregister.h"

// @author: Daniel Muszkiet

InstructionRegister::InstructionRegister()
{
    this->state = true;
    this->opCodeValue = 0;
    this->adresseValue = 0;
}

InstructionRegister::~InstructionRegister()
{
}

QRectF InstructionRegister::boundingRect() const
{
    return QRectF(118, -40 , 252, 127);
}

void InstructionRegister::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    rect.setY(rect.y()+20);
    painter->drawText(rect,Qt::AlignHCenter,"IR");

    font.setPixelSize(15);
    font.setBold(false);
    rect.setY(rect.y()+22);
    painter->setFont(font);
    painter->drawText(rect,Qt::AlignHCenter,"OpCode      Adresse");
}

void InstructionRegister::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    if(state)
        state = false;
    else
        state = true;
}

