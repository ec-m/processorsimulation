#ifndef INSTRUCTIONREGISTER_H
#define INSTRUCTIONREGISTER_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QDebug>

// @author: Daniel Muszkiet

class InstructionRegister : public QGraphicsItem
{
public:
    InstructionRegister();
    ~InstructionRegister();

    ushort opCodeValue;
    ushort adresseValue;

private:
    bool state;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // INSTRUCTIONREGISTER_H
