#ifndef PC_H
#define PC_H
#include <QDebug>

// @author: Andreas Rist

class PC
{
public:

   PC();

   // sets Adress++
   // if Adress>4096 ==> 0
   void nextAdress();

   //sets the this->Adress to Adress necessary for View messegages
   //visit model->notify()for more information
   void setAdress(unsigned short Adress);
   unsigned short getAdress();

private:

    unsigned short Adress;
};

#endif // PC_H
