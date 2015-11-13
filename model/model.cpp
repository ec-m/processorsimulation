#include "model/model.h"

// @author: Andreas Rist

Model::Model()
{
    parser = new Parser();
    megaHerz= 500;
    stepCounter=0;

    isInSingleStep=false;
    isInAutoMode=false;
    isInPhaseMode=false;
    isInTotalMode=false;
    phase=false;
    for (int i = 0; i < 4096; ++i) {
        ram.setMemory(i,0);
    }
    firstInit=true;
    ram.setCurrentAdress(0);
    ir.runAndSet(0b1111000000000000);
    pc.setAdress(0);
    controllUnit.setOpCode(ir.getOpCode());
    controllUnit.refreshFlags(0);
    mux.decide(ir.getAdress(),pc.getAdress(),controllUnit.getFlag(addrIR));
    ram.setCurrentAdress(0);
    stepCounter=0;
}

void Model::loadOntoRam(QString filename)
{
    this->LastFilename=filename;
    parser->controlParsing(filename);

    short* ramVal = parser->getOpCodes();

    for (int i = 0; i < Modelram::memLength; ++i) {
        ram.setMemory(i,(unsigned)ramVal[i]);
    }
    delete[] ramVal;


    this->sendRamToView();
    this->initModel();
}

Parser *Model::sendParserPointer()
{
    return this->parser;
}

void Model::sendRamToView()
{
    Message msg(Message::RAMwasSet);
    unsigned short* ramVal = ram.copyRam();

    msg.content= ramVal;
    emit(sendMessage(msg));
}

void Model::sendFlagstoView()
{
    bool flagers[12];
    for (int i =0; i < 12;i++){
        flagers[i] = controllUnit.getFlag(i);
    }

    Message msg(Message::RefreshCuFlags);
    msg.content = flagers;
    emit(sendMessage(msg));
}

void Model::singleStep()
{
    stepCounter++;
    if(stepCounter==7){
        stepCounter=1;
    }
    switch (stepCounter) {
    case 1:{
        Message msg9(Message::ClockCircle);
        emit(sendMessage(msg9));
        phase=true;
        controllUnit.refreshFlags(0);
        this->sendFlagstoView();

        //status();
        if(ir.getOpCode()==LDA){
            this->addrIsIRorPC();
        }else if(ir.getOpCode()==BRZ){
            this->setThePC();
            stepCounter=3;

        }else if(ir.getOpCode()>= NOP0){
            stepCounter=3;
            this->singleStep();
        }else if(ir.getOpCode()> XOR){
            stepCounter=1;
            this->singleStep();
        }else if(ir.getOpCode()<=XOR){
            this->addrIsIRorPC();

        }
        Message msg1(Message::CUisIR);
        emit(sendMessage(msg1));
        if(isInSingleStep){
        Message msg9(Message::infoText);
        QString s= infoBox.step1();
        msg9.content = &s;
        emit(sendMessage(msg9));
        }
        break;}
    case 2:{
        phase=true;
        this->aluIsCalculation();
        if(isInSingleStep){
        Message msg9(Message::infoText);
        QString s= infoBox.step2(ir.getOpCode());
        msg9.content = &s;
        emit(sendMessage(msg9));
        }
        break;}
    case 3:{
        phase=true;
        this->doWriteRam();
        this->setTheAccu();
        if(isInSingleStep){
        Message msg9(Message::infoText);
        QString s= infoBox.step3(ir.getOpCode());
        msg9.content = &s;
        emit(sendMessage(msg9));
        }
        //TODO MESSAGE VALUE
        break;}
    case 4:{
        Message msg9(Message::ClockCircle);
        emit(sendMessage(msg9));
        phase=false;

        if(ir.getOpCode()<NOP0){
            controllUnit.refreshFlags(1);

        }
        this->sendFlagstoView();
        //this->addrIsIRorPC();
        mux.decide(ir.getAdress(),pc.getAdress(),false);
        ram.setCurrentAdress(mux.getAdress());
        if(isInSingleStep){
            Message msgE(Message::AddrIsPC);
            emit(sendMessage(msgE));
        }
        Message msg1(Message::CUisIR);
        emit(sendMessage(msg1));

        if(isInSingleStep){
        Message msg9(Message::infoText);
        QString s= infoBox.step4();
        msg9.content = &s;
        emit(sendMessage(msg9));
        }
        break;}

    case 5:{
        phase=false;
        this->setTheIR();
        //TODO MESSAGE VALUE
        if(isInSingleStep){
        Message msg9(Message::infoText);
        QString s= infoBox.step5();
        msg9.content = &s;
        emit(sendMessage(msg9));
        }
        break;}
    case 6:{
        phase=false;
        this->incThePC();
        //TODO MESSAGE VALUE
        if(isInSingleStep){
        Message msg9(Message::infoText);
        QString s= infoBox.step6();
        msg9.content = &s;
        emit(sendMessage(msg9));
        }
        break;}
    default:
        qDebug()<<"singleStep accured a Problem: Went out of stepCounter";
        break;
    }
    if(stepCounter==3||stepCounter==6){
    }
}

void Model::phasenStep()
{
    phase = !phase;
    if(isInPhaseMode){
    Message msg2(Message::infoText);
    QString s = infoBox.halfStepInfo(phase,ir.getOpCode());
    msg2.content = &s;
    emit(sendMessage(msg2));}
    while(stepCounter<=3){
        this->singleStep();
    }
    short Opcode = ir.getOpCode();

    if(isInPhaseMode){
        if(Opcode == BRZ){

            if(akku.isEmpty()){
                Message msg(Message::SetPC);
                emit(sendMessage(msg));
            }else{
                Message msg(Message::SetPcWithout);
                emit(sendMessage(msg));
            }

        }else if(Opcode == STO){
            Message msg(Message::Phase1withRam);
            emit(sendMessage(msg));
        }else if(Opcode <XOR){
            Message msg(Message::Phase1withAccu);
            emit(sendMessage(msg));
        }else if(Opcode <NOP0){
            Message msg(Message::Phase1withoutAdresse);
            emit(sendMessage(msg));
        }
    }

    if(phase==true){
        while(stepCounter>3&&stepCounter<=6){
            this->singleStep();
        }
        if(isInPhaseMode){
        Message msg2(Message::infoText);
        QString s = infoBox.halfStepInfo(phase,ir.getOpCode());
        msg2.content = &s;
        emit(sendMessage(msg2));}
        if(isInPhaseMode){
            Message msg(Message::Phase2);
            emit(sendMessage(msg));
        }
    }
}

void Model::fullstep()
{
    bool flaggers[12];
    for (int i = 0; i < 12; ++i) {
        flaggers[i]=false;
    }
    phasenStep();
    Message msg123(Message::infoText);
    QString str =infoBox.fullStepInfo(ir.getOpCode());
    msg123.content= &str;

    emit(sendMessage(msg123));
    unsigned short oCod = ir.getOpCode();


    for (int i = 0; i < 12; ++i) {
        flaggers[i]=controllUnit.getFlag(i);
    }
    phasenStep();
    for (int i = 0; i < 12; ++i) {
        if(controllUnit.getFlag(i)){
            flaggers[i]=true;
        }
    }
    Message msg1234(Message::RefreshCuFlags);
    msg1234.content = flaggers;
    emit(sendMessage(msg1234));
    if(oCod==BRZ){
        if(akku.isEmpty()){
            Message msg(Message::FullstepBRZJump);
            emit(sendMessage(msg));
        }else{
            Message msg(Message::FullstepBRZ);
            emit(sendMessage(msg));
        }
    }else if(oCod<8){
        Message msg(Message::FullstepNormal);
        emit(sendMessage(msg));
    }else if(oCod>=12){
        Message msg(Message::Phase2);
        emit(sendMessage(msg));
    }else if(oCod>=8){
        Message msg(Message::FullstepSingle);
        emit(sendMessage(msg));
    }
}

void Model::autoStep()
{
    Inifinitlooptest loopTester;
    int i=0;
    while(isInAutoMode){
        i++;
        phasenStep();

        loopTester.insertAdressNOperation(pc.getAdress(),ir.getOpCode());
        if(megaHerz>0){
        delay(((int)(megaHerz/2)));}
        phasenStep();
        if(megaHerz>0){
        delay(((int)(megaHerz/2)));}
        if(isInAutoMode){
            isInAutoMode=!loopTester.testIfLoop();
            if(!isInAutoMode){
                Message msgE(Message::StopAuto);
                emit(sendMessage(msgE));
            }
        }
    }
}

void Model::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}



void Model::addrIsIRorPC()
{
    if(controllUnit.getFlag(addrIR)){


        this->mux.decide(ir.getAdress(),pc.getAdress(),controllUnit.getFlag(addrIR));
        this->ram.setCurrentAdress(mux.getAdress());

        unsigned short RamCell = mux.getAdress();
        Message msg3(Message::GetActiveRamRow);
        msg3.content= &RamCell;
        emit(sendMessage(msg3));

        if(isInSingleStep){
            if(controllUnit.getFlag(addrIR)){

                Message msg(Message::AddrIsIR);
                emit(sendMessage(msg));

            }else{

                Message msg(Message::AddrIsPC);
                emit(sendMessage(msg));

            }
        }
    }
}

void Model::aluIsCalculation()
{
    this->alu.aluResult = this->alu.workAlu(controllUnit.getALU3210(),
                                            akku.getValue(),
                                            ram.getValue(),
                                            controllUnit.getFlag(aluMode),
                                            controllUnit.getFlag(aluCIn));
    if(isInSingleStep){
        short oc = ir.getOpCode();
        if(oc==LDA){
            Message msg(Message::AluIsRAM);
            emit(sendMessage(msg));
        }else if((oc>=INC&&oc<=ZRO)||oc==0){
            Message msg(Message::AlluIsAccu);
            emit(sendMessage(msg));
        }else{
            Message msg(Message::AluWork);
            emit(sendMessage(msg));
        }
    }
}

void Model::doWriteRam()
{
    if(controllUnit.getFlag(writeRam)){
        ram.setMemory(ir.getAdress(),alu.aluResult);
        if(isInSingleStep){
            Message msg(Message::WriteRAM);
            emit(sendMessage(msg));
        }
        Message msg(Message::SendSingleRAMCell);
        unsigned short con[2];
        con[0]= ir.getAdress();
        con[1]=ram.getValue(con[0]);
        msg.content=con;
        emit(sendMessage(msg));

        unsigned short RamCell = mux.getAdress();
        Message msg3(Message::GetActiveRamRow);
        msg3.content= &RamCell;
        emit(sendMessage(msg3));
    }
}

void Model::setTheIR()
{
    if(controllUnit.getFlag(setIR)){
        ir.runAndSet(ram.getValue());
        controllUnit.setOpCode(ir.getOpCode());

        if(isInSingleStep){
            Message msg(Message::SetIR);

            emit(sendMessage(msg));
        }
        unsigned short RamCell = mux.getAdress();
        Message msg3(Message::GetActiveRamRow);
        msg3.content= &RamCell;
        emit(sendMessage(msg3));
        Message msg(Message::IRvalues);
        short content[2];
        content[0]= ir.getOpCode();
        content[1]= ir.getAdress();
        msg.content = content;
        emit(sendMessage(msg));
    }
}

void Model::incThePC()
{
    if(controllUnit.getFlag(incPC)){
        pc.nextAdress();
        if(isInSingleStep){
            Message msg(Message::IncPC);
            emit(sendMessage(msg));
        }
        Message msg(Message::PCupdate);
        short con = pc.getAdress();
        msg.content = &con;
        emit(sendMessage(msg));
    }
}

void Model::setThePC()
{
    if(controllUnit.getFlag(setPC)){

        if(akku.isEmpty()){
            pc.setAdress(ir.getAdress());
            if(isInSingleStep){
                Message msg(Message::SetPC);
                emit(sendMessage(msg));
            }
            Message msg(Message::PCupdate);
            short con = pc.getAdress();
            msg.content = &con;
            emit(sendMessage(msg));
        }else{
            if(isInSingleStep){
                Message msg(Message::SetPcWithout);
                emit(sendMessage(msg));
            }


        }
        Message msg(Message::PCupdate);
        short con = pc.getAdress();
        msg.content = &con;
        emit(sendMessage(msg));
    }
}

void Model::setTheAccu()
{
    if(controllUnit.getFlag(setAccu)){
        if(isInSingleStep){
            Message msg(Message::SetAccu);
            emit(sendMessage(msg));
        }
        akku.setValue(alu.aluResult);
        Message msg4(Message::ACCUupdate);
        short con= akku.getValue();
        msg4.content = &con;
        emit(sendMessage(msg4));
    }
}

void Model::initModel()
{
    ram.setCurrentAdress(0);
    ir.runAndSet(0b1111000000000000);
    pc.setAdress(0);
    controllUnit.setOpCode(ir.getOpCode());
    controllUnit.refreshFlags(0);
    this->sendFlagstoView();
    mux.decide(ir.getAdress(),pc.getAdress(),controllUnit.getFlag(addrIR));
    ram.setCurrentAdress(0);

    Message msg2(Message::IRvalues);
    short content[2];
    content[0]= ir.getOpCode();
    content[1]= ir.getAdress();
    msg2.content = content;
    emit(sendMessage(msg2));

    Message msg3(Message::PCupdate);
    short con = pc.getAdress();
    msg3.content = &con;
    emit(sendMessage(msg3));

    Message msg4(Message::ACCUupdate);
    con= akku.getValue();
    msg4.content = &con;
    emit(sendMessage(msg4));

    stepCounter=0;
}

void Model::status()
{
    qDebug() << "IR: OpCode: " << ir.getOpCode() << " Adress" << ir.getAdress();
    qDebug() << "PC: " << pc.getAdress();
    qDebug() << "RamAktuell: "<< ram.getValue()<<mux.getAdress();
    qDebug() << "Steuerung: ";
    qDebug() << "wirteRam:" << controllUnit.getFlag(writeRam);
    qDebug() << "incPC:" << controllUnit.getFlag(incPC);
    qDebug() << "setPC:" << controllUnit.getFlag(setPC);
    qDebug() << "addrIR:" << controllUnit.getFlag(addrIR);
    qDebug() << "setIR:" << controllUnit.getFlag(setIR);
    qDebug() << "setAccu:" << controllUnit.getFlag(setAccu);
    qDebug() << "alucin:" << controllUnit.getFlag(aluCIn);
    qDebug() << "alumode:" << controllUnit.getFlag(aluMode);
    qDebug() << "alu3:" << controllUnit.getFlag(alu3);
    qDebug() << "alu2:" << controllUnit.getFlag(alu2);
    qDebug() << "alu1:" << controllUnit.getFlag(alu1);
    qDebug() << "alu0:" << controllUnit.getFlag(alu0);
    qDebug() << "Akku: "<< akku.getValue();
    qDebug() << "AkkuB:"<< akku.isEmpty();
    qDebug() << "AluResulst" << alu.aluResult;
    qDebug()<< "Ram[26]: "<< ram.getValue(26);
    qDebug() << "Step:"<<stepCounter;
    qDebug()<<"";
}

void Model::giveRamToConsole(short adr)
{
    ram.wirteRamTo(adr);
}

void Model::notify(Message &msg)
{
    if(msg.type == Message::FileOpen)
    {
        QString* content = (QString*) msg.content;
        this->loadOntoRam(*content);

    }else if(msg.type==Message::SingleStep)
    {

        isInAutoMode=false;
        isInPhaseMode=false;
        isInSingleStep=true;
        isInTotalMode=false;
        this->singleStep();
    }else if(msg.type == Message::UserInputAccu)
    {
        unsigned short* aVal = (unsigned short*) msg.content;
        akku.setValue(*aVal);
    }else if(msg.type == Message::UserInputAddress)
    {
        unsigned short* adre = (unsigned short*) msg.content;
        ir.setAdress(*adre);
    }else if(msg.type == Message::UserInputOpCode)
    {
        unsigned short* opC = (unsigned short*) msg.content;
        ir.setAdress(*opC);

    }else if(msg.type==Message::HalfCycle){
        isInAutoMode=false;
        isInPhaseMode=true;
        isInSingleStep=false;
        isInTotalMode=false;
        this->phasenStep();
    }else if(msg.type==Message::Cycle){
        isInAutoMode=false;
        isInPhaseMode=false;
        isInSingleStep=false;
        isInTotalMode=true;
        this->fullstep();
    }else if(msg.type ==Message::Automatic){
        isInAutoMode=true;
        isInPhaseMode=true;
        isInSingleStep=false;
        isInTotalMode=false;
        this->autoStep();

    }else if(msg.type == Message::Stop){

        isInAutoMode=false;
        isInPhaseMode=false;
        isInSingleStep=false;
        isInTotalMode=false;

    }else if(msg.type == Message::Reset){
        short *ramCopy= parser->getOpCodes();
        for (int i = 0;  i< parser->getOpCodesLength(); ++i) {
            ram.setMemory(i,ramCopy[i]);
        }
        delete[] ramCopy;
        this->sendRamToView();
        this->initModel();
    }else if(msg.type == Message::UserInputRAM){
        unsigned short *con = (unsigned short*)msg.content;
        ram.setMemory(con[0],con[1]);
    }else if(msg.type == Message::Speed){
        int *con1 = (int*) msg.content;
        this->megaHerz=*con1;

    }
}



