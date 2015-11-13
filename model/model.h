#ifndef MODEL_H
#define MODEL_H
#include "infoboxcontent.h"
#include "model/akku.h"
#include "model/alu.h"
#include "model/controllunit.h"
#include "model/ir.h"
#include "model/mux.h"
#include "model/pc.h"
#include "model/modelram.h"
#include <QDebug>
#include <QObject>
#include "model/message.h"
#include "model/parser.h"
#include "model/inifinitlooptest.h"
#include <QString>
#include <QTime>
#include <QCoreApplication>

// @author: Andreas Rist

class Model : public QObject
{
    Q_OBJECT

public:

    Model();

    //necessary to give parser for app.ccp that it can connect Parser and View
    Parser* sendParserPointer();

private:

    int megaHerz;
    infoBoxContent infoBox;
    Akku akku;
    ALU alu;
    ControllUnit controllUnit;
    IR ir;
    MUX mux;
    PC pc;
    Modelram ram;
    Parser* parser;
    QString LastFilename;
    short stepCounter;
    unsigned short aluValue ;
    bool isInSingleStep;
    bool isInAutoMode;
    bool isInPhaseMode;
    bool isInTotalMode;
    bool phase;
    bool firstInit;

    /*these are the flags*/
    enum flags {writeRam=0,
                incPC=1,
                setPC=2,
                addrIR=3,
                setIR=4,
                setAccu=5,
                aluCIn=6,
                aluMode=7,
                alu3=8,
                alu2=9,
                alu1=10,
                alu0=11};

    enum oCodes {STO=0,
                LDA=1,
                BRZ=2,
                ADD=3,
                SUB=4,
                OR=5,
                AND=6,
                XOR=7,
                NOT=8,
                INC=9,
                DEC=10,
                ZRO=11,
                NOP0=12,
                NOP1=13,
                NOP2=14,
                NOP3=15};

    /*Sends Ram to view (complete)*/
    void sendRamToView();

    /*Sends the Flags to the View*/
    void sendFlagstoView();

    /*does the singlestep*/
    void singleStep();

    /*phasenstep*/
    void phasenStep();

    /*fullstep*/
    void fullstep();

    /*automode*/

    void autoStep();
    /*Delays the Programm only used in autoStep()*/
    void delay(int millisecondsToWait);

    /*These are the Funktions for Working the Model (the phases)*/
    void addrIsIRorPC();
    void aluIsCalculation();
    void doWriteRam();
    void setTheIR();
    void incThePC();
    void setThePC();
    void setTheAccu();

    //wirtes Ram to Memory Modelram and initializies the whole Model
    void loadOntoRam(QString filename);
    //is called from loadOntoRam to initalize the Model
    void initModel();
    //Gives the status of the Model to the Console
    void status();

    //writes the Ram-Values to Console from 0-adr
    void giveRamToConsole(short adr);

public slots:

    void notify(Message &msg);

signals:

    void sendMessage(Message &msg);
};

#endif // MODEL_H
