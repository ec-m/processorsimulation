#ifndef IR_H
#define IR_H
#include <QDebug>

// @author: Andreas Rist

class IR
{
public:

    IR();

    // Takes the Ram entry and speparates Opcode from Adress
    void runAndSet( unsigned short RamEntry);
    unsigned short getOpCode();
    unsigned short getAdress();

    //setOpcode and setAdress to change Values with Message
    //for more information visit model->notify()
    unsigned short setOpCode(unsigned short opCode);
    unsigned short setAdress(unsigned short adress);

private:

    unsigned short opCode;
    unsigned short adress;
};

#endif // IR_H
