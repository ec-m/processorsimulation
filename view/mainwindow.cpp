/*
 * This file is part of Processorsimulation.
 *
 * The Processorsimulation is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the Free
 * Software Foundation, Version 3.
 *
 * The Processorsimulation is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "view/mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>

// @author: Daniel Muszkiet

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{            
    initializeWindow();

    setGraphicsScene();

    createElements();

    this->loaded = true;

    // all numbers and commands in decimal
    this->currformat = decimal;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeWindow()
{
    // Default Mode for arrows
    showAll = false;

    this->activeColor= QColor(255, 174, 201,255);
    this->notActiveColor = QColor(150, 150, 150,255);

    // Set Color Pickers and connect SIGNALS and SLOTS
    colorPicker = new QColorDialog(QColor(150, 150, 150,255),this);
    colorPicker2 = new QColorDialog(QColor(255, 174, 201,255),this);
    connect(colorPicker,SIGNAL(colorSelected(QColor)),this,SLOT(notActiveColorChange(QColor)));
    connect(colorPicker2,SIGNAL(colorSelected(QColor)),this,SLOT(activeColorChange(QColor)));

    // Flag: Gui is Loaded
    this->loaded = false;

    //Setup MainWindow
    ui->setupUi(this);
    this->setWindowTitle("Toy Processor");
    this->setMinimumWidth(900);
    this->setMinimumHeight(600);
    this->showMaximized();

    // Set Ram Content Table (Style, Default Values)
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(4096);
    for(int i = 0; i<4096; i++){
        QTableWidgetItem *item = new QTableWidgetItem("0");
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
        ui->tableWidget->setItem(i,0,item);
        ui->tableWidget->setVerticalHeaderItem(i,new QTableWidgetItem(QString::number(i)));
    }

    ui->tableWidget->setStyleSheet ( ui->tableWidget->styleSheet() +
                                     " QTableWidget::item:focus { background-color:#D0D0D0 ; color:black ;  border:0 }" );

    ui->tableWidget->setColumnWidth(1,10);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Wert"));

    // Add custom Eventlistener to TableWidget
    EnterKeyListener *enterkeylistener = new EnterKeyListener(ui->tableWidget, this);
    ui->tableWidget->installEventFilter(enterkeylistener);

    // Row Jump for table
    ui->lineEdit->setPlaceholderText("Zelle eingeben");
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));

    // Hide some Actions
    ui->menuModus->menuAction()->setVisible(false);
    ui->menuAktion->menuAction()->setVisible(false);
    ui->actionStop->setVisible(false);

    // Default Mode and format
    ui->actionStart->setEnabled(true);
    ui->actionStep_Mode->setChecked(true);
    ui->actionDezimal->setChecked(true);
    ui->actionSpeedA->setChecked(true);
}

void MainWindow::setGraphicsScene()
{
    this->scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

void MainWindow::createElements()
{
    // Creats all elements for Graphics View and add them
    clocky = new Clock();
    scene->addItem(clocky);

    controlUnit = new ControlUnit();
    scene->addItem(controlUnit);

    instructionRegister = new InstructionRegister();
    scene->addItem(instructionRegister);

    programCounter = new ProgramCounter();
    scene->addItem(programCounter);

    ram = new RandomAccessMemory();
    scene->addItem(ram);

    accumulator = new Accumulator();
    scene->addItem(accumulator);

    multiplexer = new Multiplexer();
    scene->addItem(multiplexer);

    alu = new ArithmeticLogicalUnit();
    scene->addItem(alu);

    arrowTaktSteuerwerk = new ArrowTaktSteuerwerk();
    scene->addItem(arrowTaktSteuerwerk);

    arrowIrSteuerwerk = new ArrowIRSteuerwerk();
    scene->addItem(arrowIrSteuerwerk);

    arrowIrPC = new ArrowIrProgramcounter();
    scene->addItem(arrowIrPC);

    arrowIrMulti = new ArrowIrMultiplexer();
    scene->addItem(arrowIrMulti);

    arrowPcMulti = new ArrowPcMultiplexer();
    scene->addItem(arrowPcMulti);

    arrowMultiRam = new ArrowMultiplexerRam();
    scene->addItem(arrowMultiRam);

    arrowAluRam = new ArrowAluRam();
    scene->addItem(arrowAluRam);

    arrowAluAccu = new ArrowAluAccu();
    scene->addItem(arrowAluAccu);

    arrowAccuAlu = new ArrowAccuAlu();
    scene->addItem(arrowAccuAlu);

    arrowRamIr = new ArrowRamIr();
    arrowRamAlu = new ArrowRamAlu();

    scene->addItem(arrowRamAlu);
    scene->addItem(arrowRamIr);

    arrowAccuPc = new ArrowAccuPc();
    scene->addItem(arrowAccuPc);

    arrowWriteRam = new ArrowWriteRam();
    scene->addItem(arrowWriteRam);

    arrowIncPc = new ArrowIncPc();
    scene->addItem(arrowIncPc);

    arrowSetPc = new ArrowSetPc();
    scene->addItem(arrowSetPc);

    arrowAddrIsIR = new ArrowAddrIsIR();
    scene->addItem(arrowAddrIsIR);

    arrowSetIr = new ArrowSetIr();
    scene->addItem(arrowSetIr);

    arrowSetAccu = new ArrowSetAccu();
    scene->addItem(arrowSetAccu);

    arrowAluCin = new ArrowAluCin();
    scene->addItem(arrowAluCin);

    arrowAluMode = new ArrowAluMode();
    scene->addItem(arrowAluMode);

    arrowAlu3 = new ArrowAlu3();
    scene->addItem(arrowAlu3);

    arrowAlu2 = new ArrowAlu2();
    scene->addItem(arrowAlu2);

    arrowAlu1 = new ArrowAlu1();
    scene->addItem(arrowAlu1);

    arrowAlu0 = new ArrowAlu0();
    scene->addItem(arrowAlu0);

    arrowPieceRamIrAlu = new ArrowPieceRamIrAlu();
    scene->addItem(arrowPieceRamIrAlu);

    arrowPieceIrMultiPc = new ArrowPieceIrMultiPc();
    scene->addItem(arrowPieceIrMultiPc);

    arrowPieceAluRamAccu = new ArrowPieceAluRamAccu();
    scene->addItem(arrowPieceAluRamAccu);

    // Programm Counter Content
    pcValue = new QLineEdit();
    pcValue->setMaximumWidth(110);
    pcValue->setAlignment(Qt::AlignCenter);
    QGraphicsProxyWidget *proxy = scene->addWidget(pcValue);
    proxy->setPos(380,225);

    connect(pcValue, SIGNAL(returnPressed()),this,SLOT(PCupdate()));

    // IR OpCode Content
    irOpCode = new QLineEdit();
    irOpCode->setMaximumWidth(60);
    irOpCode->setAlignment(Qt::AlignCenter);
    proxy = scene->addWidget(irOpCode);
    proxy->setPos(173,22);
    connect(irOpCode, SIGNAL(returnPressed()),this,SLOT(OpCodeUpdate()));

    // IR Adresse Content
    irAdresse = new QLineEdit();
    irAdresse->setMaximumWidth(90);
    irAdresse->setAlignment(Qt::AlignCenter);
    proxy = scene->addWidget(irAdresse);
    proxy->setPos(245,22);
    connect(irAdresse, SIGNAL(returnPressed()),this,SLOT(AdresseUpdate()));

    // Accu Content
    accu = new QLineEdit();
    accu->setMaximumWidth(110);
    accu->setAlignment(Qt::AlignCenter);
    proxy = scene->addWidget(accu);
    proxy->setPos(781,3);
    connect(accu, SIGNAL(returnPressed()),this,SLOT(accuUpdate()));

    // Info Box
    QGraphicsTextItem* title = new QGraphicsTextItem();
    title->setHtml("<h2> Info Box </h2>");
    title->setPos(3,430);
    this->scene->addItem(title);

    QGraphicsRectItem* i = new QGraphicsRectItem(0,430,270,70);
    QPen p;
    p.setStyle(Qt::DashLine);
    p.setCapStyle(Qt::RoundCap);
    i->setPen(p);
    scene->addItem(i);

    infobox = new QGraphicsTextItem();
    infobox->setPos(3,450);
    infobox->setFont(QFont ("Calibri", 12));
    this->scene->addItem(infobox);
}


/* ----------------------             Messages         ---------------------- */

void MainWindow::notify(Message& msg)
{
    switch(msg.type)
    {
    case Message::AddrIsIR:{
        deactivateAll();
        arrowIrMulti->activate(true);
        arrowMultiRam->activate(true);
        arrowPieceIrMultiPc->activate(true);
        if(showAll)
            arrowIrPC->activate(true);
        break;
    }

    case Message::AddrIsPC:{
        deactivateAll();
        arrowPcMulti->activate(true);
        arrowMultiRam->activate(true);
        break;
    }

    case Message::AlluIsAccu:{
        deactivateAll();
        arrowAccuAlu->activate(true);
        break;
    }

    case Message::WriteRAM:{
        deactivateAll();
        arrowAluRam->activate(true);
        arrowPieceAluRamAccu->activate(true);
        if(showAll)
            arrowAluAccu->activate(true);
        break;
    }

    case Message::SetIR:{
        deactivateAll();
        arrowRamIr->activate(true);
        //arrowIrSteuerwerk->activate(true); Noch ganz weg machen
        arrowPieceRamIrAlu->activate(true);
        if (showAll)
            arrowRamAlu->activate(true);
        break;
    }

    case Message::CUisIR:{
        arrowIrSteuerwerk->activate(true);
        break;
    }

    case Message::IncPC:{
        deactivateAll();
        break;
    }

    case Message::AluIsRAM:{
        deactivateAll();
        arrowRamAlu->activate(true);
        arrowPieceRamIrAlu->activate(true);
        if(showAll)
            arrowRamIr->activate(true);
        break;
    }

    case Message::SetAccu:{
        deactivateAll();
        arrowAluAccu->activate(true);
        arrowPieceAluRamAccu->activate(true);
        if(showAll)
            arrowAluRam->activate(true);
        break;
    }

    case Message::SetPC:{
        deactivateAll();
        arrowAccuPc->activate(true);
        arrowIrPC->activate(true);
        arrowPieceIrMultiPc->activate(true);
        if(showAll)
            arrowIrMulti->activate(true);
        break;
    }

    case Message::AluWork:{
        deactivateAll();
        arrowRamAlu->activate(true);
        arrowAccuAlu->activate(true);
        arrowPieceRamIrAlu->activate(true);
        if(showAll)
            arrowRamIr->activate(true);
        break;
    }

    case Message::ClockCircle:{
        deactivateAll();
        arrowTaktSteuerwerk->activate(!arrowTaktSteuerwerk->isActive);
        break;
    }

    case Message::SetPcWithout:{
        deactivateAll();
        arrowIrPC->activate(true);
        arrowPieceIrMultiPc->activate(true);
        if(showAll)
            arrowIrMulti->activate(true);
        break;
    }

    case Message::Phase1withRam:{
        deactivateAll();
        arrowTaktSteuerwerk->activate(true);
        arrowIrMulti->activate(true);
        arrowMultiRam->activate(true);
        arrowAccuAlu->activate(true);
        arrowAluRam->activate(true);
        arrowPieceIrMultiPc->activate(true);
        arrowPieceAluRamAccu->activate(true);
        if(showAll){
            arrowIrPC->activate(true);
            arrowAluAccu->activate(true);
        }
        break;
    }

    case Message::Phase1withAccu:{
        deactivateAll();
        arrowTaktSteuerwerk->activate(true);
        arrowIrMulti->activate(true);
        arrowMultiRam->activate(true);
        arrowRamAlu->activate(true);
        arrowAccuAlu->activate(true);
        arrowAluAccu->activate(true);
        arrowPieceIrMultiPc->activate(true);
        arrowPieceRamIrAlu->activate(true);
        arrowPieceAluRamAccu->activate(true);
        if(showAll){
            arrowIrPC->activate(true);
            arrowRamIr->activate(true);
            arrowAluRam->activate(true);
        }
        break;
    }

    case Message::Phase1withoutAdresse:{
        deactivateAll();
        arrowTaktSteuerwerk->activate(true);
        arrowAccuAlu->activate(true);
        arrowAluAccu->activate(true);
        arrowPieceAluRamAccu->activate(true);
        if(showAll)
            arrowAluRam->activate(true);
        break;
    }

    case Message::Phase2:{
        deactivateAll();
        arrowTaktSteuerwerk->activate(false);
        arrowPcMulti->activate(true);
        arrowMultiRam->activate(true);
        arrowRamIr->activate(true);
        arrowPieceRamIrAlu->activate(true);
        if(showAll)
            arrowRamAlu->activate(true);
        break;
    }

    case Message::FullstepNormal:{
        deactivateAll();

        arrowIrMulti->activate(true);
        arrowMultiRam->activate(true);
        arrowRamAlu->activate(true);
        arrowAluAccu->activate(true);
        arrowAccuAlu->activate(true);
        arrowAluRam->activate(true);
        arrowPcMulti->activate(true);
        arrowRamIr->activate(true);

        arrowTaktSteuerwerk->activate(true);
        arrowIrSteuerwerk->activate(true);

        arrowPieceIrMultiPc->activate(true);
        arrowPieceRamIrAlu->activate(true);
        arrowPieceAluRamAccu->activate(true);

        if(showAll){
            arrowIrPC->activate(true);
            arrowRamIr->activate(true);
            arrowAluRam->activate(true);
        }

        break;
    }

    case Message::FullstepBRZ:{
        deactivateAll();
        arrowIrPC->activate(true);
        arrowPcMulti->activate(true);
        arrowRamIr->activate(true);

        arrowTaktSteuerwerk->activate(true);
        arrowIrSteuerwerk->activate(true);

        arrowPieceIrMultiPc->activate(true);
        arrowPieceRamIrAlu->activate(true);

        if(showAll){
            arrowIrMulti->activate(true);
            arrowRamAlu->activate(true);
        }


        break;
    }

    case Message::FullstepBRZJump:{
        deactivateAll();
        arrowIrPC->activate(true);
        arrowPcMulti->activate(true);
        arrowRamIr->activate(true);
        arrowAccuPc->activate(true);

        arrowTaktSteuerwerk->activate(true);
        arrowIrSteuerwerk->activate(true);

        arrowPieceIrMultiPc->activate(true);
        arrowPieceRamIrAlu->activate(true);

        if(showAll){
            arrowIrMulti->activate(true);
            arrowRamAlu->activate(true);
        }

        break;
    }

    case Message::FullstepSingle:{
        deactivateAll();
        arrowMultiRam->activate(true);
        arrowRamAlu->activate(true);
        arrowAluAccu->activate(true);
        arrowAccuAlu->activate(true);
        arrowAluRam->activate(true);
        arrowPcMulti->activate(true);
        arrowRamIr->activate(true);

        arrowTaktSteuerwerk->activate(true);
        arrowIrSteuerwerk->activate(true);

        arrowPieceRamIrAlu->activate(true);
        arrowPieceAluRamAccu->activate(true);
        break;
    }

    case Message::RAMwasSet:{
        unsigned short *ram = (unsigned short*)msg.content;

        this->ram->arr = ram;

        if(this->currformat == decimal)
        {
            for(int i=0; i<4096; i++)
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(ram[i])));
        }
        else if(this->currformat == hexa)
        {
            for(int i=0; i<4096; i++)
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(showAsHexa(ram[i])));
        }
        else if(this->currformat == binary)
        {
            for(int i=0; i<4096; i++)
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(showAsBin(ram[i])));
        }
        else if(this->currformat == mnemonic)
        {
            QString temp;
            for(int i=0; i<4096; i++){
                if(i<this->opCodeNumber){
                    temp = showAsMnemonic(ram[i]);
                }else{
                    temp = QString::number(ram[i]);
                }

                ui->tableWidget->setItem(i,0,new QTableWidgetItem(temp));
            }
        }


        break;
    }

    case Message::IRvalues:{
        short *ir = (short*)msg.content;
        short opCode = ir[0];
        short adresse = ir[1];

        this->instructionRegister->opCodeValue = (ushort) opCode;
        this->instructionRegister->adresseValue = (ushort) adresse;

        if(this->currformat == decimal){
            irOpCode->setPlaceholderText(QString::number(opCode));
            irAdresse->setPlaceholderText(QString::number(adresse));
        }else if(this->currformat == hexa){
            irOpCode->setPlaceholderText(showAsHexa((ushort) opCode));
            irAdresse->setPlaceholderText(showAsHexa((ushort) adresse));
        }else if(this->currformat == binary){
            irOpCode->setPlaceholderText(showAsBin((ushort) opCode));
            irAdresse->setPlaceholderText(showAsBin((ushort) adresse));
        }else if(this->currformat == mnemonic){
            irOpCode->setPlaceholderText(showOpCodeAsMnemonic(opCode));
            irAdresse->setPlaceholderText(QString::number(adresse));
        }

        break;
    }

    case Message::PCupdate:{
        unsigned short* value = (unsigned short*)msg.content;

        if(this->currformat == decimal || this->currformat == mnemonic){
            pcValue->setPlaceholderText(QString::number(*value));
        }else if(this->currformat == hexa){
            pcValue->setPlaceholderText(showAsHexa(*value));
        }else if(this->currformat == binary){
            pcValue->setPlaceholderText(showAsBin(*value));
        }
        break;
    }

    case Message::ACCUupdate:{
        unsigned short* value = (unsigned short*)msg.content;

        this->accumulator->curValue = *value;

        if(this->currformat == decimal || this->currformat == mnemonic){
            accu->setPlaceholderText(QString::number(*value));
        }else if(this->currformat == hexa){
            accu->setPlaceholderText(showAsHexa(*value));
        }else if(this->currformat == binary){
            accu->setPlaceholderText(showAsBin(*value));
        }

        break;
    }

    case Message::RefreshCuFlags:{
        bool* flags = (bool*) msg.content;

        arrowWriteRam->activate(flags[0]);
        arrowIncPc->activate(flags[1]);
        arrowSetPc->activate(flags[2]);
        arrowAddrIsIR->activate(flags[3]);
        arrowSetIr->activate(flags[4]);
        arrowSetAccu->activate(flags[5]);
        arrowAluCin->activate(flags[6]);
        arrowAluMode->activate(flags[7]);
        arrowAlu3->activate(flags[8]);
        arrowAlu2->activate(flags[9]);
        arrowAlu1->activate(flags[10]);
        arrowAlu0->activate(flags[11]);

        scene->update();
        break;
    }

    case Message::WrongInputPC:{
        pcValue->clear();
        pcValue->setPlaceholderText("ERROR");

        break;
    }

    case Message::WrongInputAccu:{
        accu->clear();
        accu->setPlaceholderText("ERROR");

        break;
    }

    case Message::WrongInputOpCode:{
        irOpCode->clear();
        irOpCode->setPlaceholderText("ERROR");

        break;
    }

    case Message::WrongInputAddress:{
        irAdresse->clear();
        irAdresse->setPlaceholderText("ERROR");
        break;
    }

    case Message::WrongInputRAM:{
        QString *content = (QString*) msg.content;
        short row = content[0].toShort();
        QString value = content[1];
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(value));
        break;
    }

    case Message::ParserError:{
        QString *errorMsg = (QString*)msg.content;
        QMessageBox::warning(this,"Error","<p><b>"+*errorMsg+"</b></p>");

        break;
    }

    case Message::SendSingleRAMCell:{
        unsigned short* content = (unsigned short*)msg.content;
        int row = content[0];
        int value = content[1];

        this->ram->arr[row] = (ushort) value;

        if(this->currformat == decimal){
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(value)));
        }else if(this->currformat == hexa){
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(showAsHexa((ushort) value)));
        }else if(this->currformat == binary){
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(showAsBin((short)value)));
        }else if(this->currformat == mnemonic){
            if(row < this->opCodeNumber)
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(showAsMnemonic((short) value)));
            else
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(value)));
        }

        break;
    }

    case Message::StopAuto:{
        ui->actionStop->setVisible(false);
        ui->actionStart->setVisible(true);
        break;
    }

    case Message::GetOpCodeRows:{
        int *val = (int*) msg.content;
        this->opCodeNumber = *val;
        break;
    }

    case Message::GetActiveRamRow:{
        short *row = (short*) msg.content;
        QTableWidgetItem *item = ui->tableWidget->item(*row, 0);
        ui->tableWidget->scrollToItem(item,QAbstractItemView::PositionAtCenter);
        ui->tableWidget->selectRow(*row);
        break;
    }

    case Message::infoText:{
        QString *info = (QString*) msg.content;
        infobox->setHtml(*info);
        scene->update();
        break;
    }

    }
}


/* ----------------------  All Actions: Start, Stop, Mode etc. ------------------ */

void MainWindow::on_actionLoadFile_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Datei laden","",tr("Toy Programm (*.toy *.toyc)"));
    if(!filename.isEmpty()){
        Message msg(Message::FileOpen);
        msg.content = &filename;
        emit(sendMessage(msg));
    }
}

void MainWindow::on_actionStart_triggered()
{
    if(ui->actionStep_Mode->isChecked()){
        Message msg(Message::SingleStep);
        emit(sendMessage(msg));
    }
    else if(ui->actionAutomaticMode->isChecked()){
        ui->actionStart->setVisible(false);
        ui->actionStop->setVisible(true);
        Message msg(Message::Automatic);
        emit(sendMessage(msg));
    }
    else if(ui->actionCycle_Modus->isChecked()){
        Message msg(Message::Cycle);
        emit(sendMessage(msg));
    }
    else if(ui->actionHalf_Cycle_Mode->isChecked()){
        Message msg(Message::HalfCycle);
        emit(sendMessage(msg));
    }

    scene->update();
}

void MainWindow::on_actionAutomaticMode_triggered(){

    ui->actionAutomaticMode->setChecked(true);
    ui->actionStep_Mode->setChecked(false);
    ui->actionCycle_Modus->setChecked(false);
    ui->actionHalf_Cycle_Mode->setChecked(false);
    ui->actionStart->setEnabled(true);

}

void MainWindow::on_actionCycle_Modus_triggered()
{
    ui->actionCycle_Modus->setChecked(true);
    ui->actionAutomaticMode->setChecked(false);
    ui->actionStep_Mode->setChecked(false);
    ui->actionHalf_Cycle_Mode->setChecked(false);
    ui->actionStart->setEnabled(true);
}

void MainWindow::on_actionStep_Mode_triggered()
{
    ui->actionStep_Mode->setChecked(true);
    ui->actionAutomaticMode->setChecked(false);
    ui->actionCycle_Modus->setChecked(false);
    ui->actionHalf_Cycle_Mode->setChecked(false);
    ui->actionStart->setEnabled(true);
}

void MainWindow::on_actionHalf_Cycle_Mode_triggered()
{    
    ui->actionHalf_Cycle_Mode->setChecked(true);
    ui->actionAutomaticMode->setChecked(false);
    ui->actionCycle_Modus->setChecked(false);
    ui->actionStep_Mode->setChecked(false);
    ui->actionStart->setEnabled(true);
}

void MainWindow::on_actionDokumentation_triggered()
{
    QString p = QDir::currentPath();
    p = p + "/ToyProcessorDokumentation.pdf";
    QDesktopServices::openUrl(QUrl("file:///"+p));
}

void MainWindow::on_actionReset_triggered()
{
    Message msg(Message::Reset);
    emit(sendMessage(msg));
}

void MainWindow::on_actionStop_triggered()
{
    ui->actionStop->setVisible(false);
    ui->actionStart->setVisible(true);
    Message msg(Message::Stop);
    emit(sendMessage(msg));
}

void MainWindow::on_actionAktive_Farbe_triggered()
{
    colorPicker2->open();
}

void MainWindow::on_actionNicht_aktive_Farbe_triggered()
{
    colorPicker->open();
}

void MainWindow::on_actionSeperateArrow_triggered()
{
    this->showAll = false;
}

void MainWindow::on_actionWholeArrow_triggered()
{
    this->showAll = true;
}

void MainWindow::on_actionMnemonic_triggered()
{
    ui->actionMnemonic->setChecked(true);
    ui->actionDezimal->setChecked(false);
    ui->actionHexadezimal->setChecked(false);
    ui->actionBin_r->setChecked(false);

    this->currformat = mnemonic;


    // Ram ändern
    QString temp;
    for(int i=0; i<4096; i++){

        if(i< this->opCodeNumber){
            temp = showAsMnemonic(this->ram->arr[i]);
        }else{
            temp = QString::number(this->ram->arr[i]);
        }

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(temp));
    }

    // PC ändern
    pcValue->setPlaceholderText(QString::number(this->programCounter->pcVal));

    // ACCU ändern
    accu->setPlaceholderText(QString::number(this->accumulator->curValue));

    // IR ändern
    irOpCode->setPlaceholderText(showOpCodeAsMnemonic(this->instructionRegister->opCodeValue));
    irAdresse->setPlaceholderText(QString::number(this->instructionRegister->adresseValue));
}

void MainWindow::on_actionHexadezimal_triggered()
{
    ui->actionHexadezimal->setChecked(true);
    ui->actionDezimal->setChecked(false);
    ui->actionMnemonic->setChecked(false);
    ui->actionBin_r->setChecked(false);

    this->currformat = hexa;

    // Ram ändern
    for(int i=0; i<4096; i++)
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(showAsHexa(this->ram->arr[i])));

    // PC ändern
    pcValue->setPlaceholderText(showAsHexa(this->programCounter->pcVal));

    // ACCU ändern
    accu->setPlaceholderText(showAsHexa(this->accumulator->curValue));

    // IR ändern
    irOpCode->setPlaceholderText(showAsHexa(this->instructionRegister->opCodeValue));
    irAdresse->setPlaceholderText(showAsHexa(this->instructionRegister->adresseValue));
}

void MainWindow::on_actionBin_r_triggered()
{
    ui->actionBin_r->setChecked(true);
    ui->actionDezimal->setChecked(false);
    ui->actionHexadezimal->setChecked(false);
    ui->actionMnemonic->setChecked(false);

    this->currformat = binary;

    // Ram ändern
    for(int i=0; i<4096; i++)
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(showAsBin(this->ram->arr[i])));

    // PC ändern
    pcValue->setPlaceholderText(showAsBin(this->programCounter->pcVal));

    // ACCU ändern
    accu->setPlaceholderText(showAsBin(this->accumulator->curValue));

    // IR ändern
    irOpCode->setPlaceholderText(showAsBin(this->instructionRegister->opCodeValue).right(4));
    irAdresse->setPlaceholderText(showAsBin(this->instructionRegister->adresseValue).right(12));
}

void MainWindow::on_actionDezimal_triggered()
{
    ui->actionDezimal->setChecked(true);
    ui->actionMnemonic->setChecked(false);
    ui->actionHexadezimal->setChecked(false);
    ui->actionBin_r->setChecked(false);

    this->currformat = decimal;

    // Ram ändern
    for(int i=0; i<4096; i++)
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(this->ram->arr[i])));

    // PC ändern
    pcValue->setPlaceholderText(QString::number(this->programCounter->pcVal));

    // ACCU ändern
    accu->setPlaceholderText(QString::number(this->accumulator->curValue));

    // IR ändern
    irOpCode->setPlaceholderText(QString::number(this->instructionRegister->opCodeValue));
    irAdresse->setPlaceholderText(QString::number(this->instructionRegister->adresseValue));
}

void MainWindow::on_actionSpeedA_triggered()
{
    ui->actionSpeedA->setChecked(true);
    ui->actionSpeedB->setChecked(false);
    ui->actionFullspeed->setChecked(false);

    Message msg(Message::Speed);
    int val = 500;
    msg.content = &val;
    emit(sendMessage(msg));
}

void MainWindow::on_actionSpeedB_triggered()
{
    ui->actionSpeedA->setChecked(false);
    ui->actionSpeedB->setChecked(true);
    ui->actionFullspeed->setChecked(false);

    Message msg(Message::Speed);
    int val = 250;
    msg.content = &val;
    emit(sendMessage(msg));
}

void MainWindow::on_actionFullspeed_triggered()
{
    ui->actionSpeedA->setChecked(false);
    ui->actionSpeedB->setChecked(false);
    ui->actionFullspeed->setChecked(true);

    Message msg(Message::Speed);
    int val = 0;
    msg.content = &val;
    emit(sendMessage(msg));
}


/* ---------------------- All Updates: PC, RAM, ACCU, IR, Color ---------------------- */

void MainWindow::PCupdate()
{
    QString userinput = pcValue->text();
    pcValue->clear();
    pcValue->setPlaceholderText(userinput);
    QString input[2] = {userinput, QString::number(this->currformat)};

    Message msg(Message::UserInputPC);
    msg.content = input;
    emit(sendMessage(msg));
}

void MainWindow::OpCodeUpdate()
{    
    QString userinput = irOpCode->text();
    irOpCode->clear();
    irOpCode->setPlaceholderText(userinput);
    QString input[2] = {userinput,QString::number(this->currformat)};

    Message msg(Message::UserInputOpCode);
    msg.content = input;
    emit(sendMessage(msg));
}

void MainWindow::AdresseUpdate()
{    
    QString userinput = irAdresse->text();
    irAdresse->clear();
    irAdresse->setPlaceholderText(userinput);
    QString input[2] = {userinput,QString::number(this->currformat)};

    Message msg(Message::UserInputAddress);
    msg.content = input;
    emit(sendMessage(msg));
}

void MainWindow::accuUpdate()
{
    QString userinput = accu->text();
    accu->clear();
    accu->setPlaceholderText(userinput);
    QString input[2] = {userinput,QString::number(this->currformat)};

    Message msg(Message::UserInputAccu);
    msg.content = input;
    emit(sendMessage(msg));
}

void MainWindow::RAMupdate(int row, int col,QString newVal, QString oldVal)
{
    QString data[4] = {newVal,QString::number(this->currformat),oldVal,QString::number(row)};
    Message msg(Message::UserInputRAM);
    msg.content = data;
    emit(sendMessage(msg));
}

void MainWindow::notActiveColorChange(QColor c)
{
    this->notActiveColor = c;
    setColor();
}

void MainWindow::activeColorChange(QColor c)
{
    this->activeColor = c;
    setColor();
}

void MainWindow::setColor()
{
    arrowAccuPc->setActiveColor(this->activeColor);
    arrowAccuPc->setNotActiveColor(this->notActiveColor);

    arrowIrSteuerwerk->setActiveColor(this->activeColor);
    arrowIrSteuerwerk->setNotActiveColor(this->notActiveColor);

    arrowIrPC->setActiveColor(this->activeColor);
    arrowIrPC->setNotActiveColor(this->notActiveColor);

    arrowIrMulti->setActiveColor(this->activeColor);
    arrowIrMulti->setNotActiveColor(this->notActiveColor);

    arrowPcMulti->setActiveColor(this->activeColor);
    arrowPcMulti->setNotActiveColor(this->notActiveColor);

    arrowMultiRam->setActiveColor(this->activeColor);
    arrowMultiRam->setNotActiveColor(this->notActiveColor);

    arrowAluRam->setActiveColor(this->activeColor);
    arrowAluRam->setNotActiveColor(this->notActiveColor);

    arrowAluAccu->setActiveColor(this->activeColor);
    arrowAluAccu->setNotActiveColor(this->notActiveColor);

    arrowAccuAlu->setActiveColor(this->activeColor);
    arrowAccuAlu->setNotActiveColor(this->notActiveColor);

    arrowRamAlu->setActiveColor(this->activeColor);
    arrowRamAlu->setNotActiveColor(this->notActiveColor);

    arrowRamIr->setActiveColor(this->activeColor);
    arrowRamIr->setNotActiveColor(this->notActiveColor);

    arrowTaktSteuerwerk->setActiveColor(this->activeColor);
    arrowTaktSteuerwerk->setNotActiveColor(this->notActiveColor);

    arrowWriteRam->setActiveColor(this->activeColor);
    arrowWriteRam->setNotActiveColor(this->notActiveColor);

    arrowIncPc->setActiveColor(this->activeColor);
    arrowIncPc->setNotActiveColor(this->notActiveColor);

    arrowSetPc->setActiveColor(this->activeColor);
    arrowSetPc->setNotActiveColor(this->notActiveColor);

    arrowAddrIsIR->setActiveColor(this->activeColor);
    arrowAddrIsIR->setNotActiveColor(this->notActiveColor);

    arrowSetIr->setActiveColor(this->activeColor);
    arrowSetIr->setNotActiveColor(this->notActiveColor);

    arrowSetAccu->setActiveColor(this->activeColor);
    arrowSetAccu->setNotActiveColor(this->notActiveColor);

    arrowAluCin->setActiveColor(this->activeColor);
    arrowAluCin->setNotActiveColor(this->notActiveColor);

    arrowAluMode->setActiveColor(this->activeColor);
    arrowAluMode->setNotActiveColor(this->notActiveColor);

    arrowAlu3->setActiveColor(this->activeColor);
    arrowAlu3->setNotActiveColor(this->notActiveColor);

    arrowAlu2->setActiveColor(this->activeColor);
    arrowAlu2->setNotActiveColor(this->notActiveColor);

    arrowAlu1->setActiveColor(this->activeColor);
    arrowAlu1->setNotActiveColor(this->notActiveColor);

    arrowAlu0->setActiveColor(this->activeColor);
    arrowAlu0->setNotActiveColor(this->notActiveColor);

    arrowPieceAluRamAccu->setActiveColor(this->activeColor);
    arrowPieceAluRamAccu->setNotActiveColor(this->notActiveColor);


    arrowPieceIrMultiPc->setActiveColor(this->activeColor);
    arrowPieceIrMultiPc->setNotActiveColor(this->notActiveColor);

    arrowPieceRamIrAlu->setActiveColor(this->activeColor);
    arrowPieceRamIrAlu->setNotActiveColor(this->notActiveColor);

    scene->update();
}


/* ------------------------------------------------------- */

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->clearFocus();
    bool isNummber;
    short row = ui->lineEdit->text().toShort(&isNummber);
    if(isNummber){
        QTableWidgetItem *item = ui->tableWidget->item(row, 0);
        ui->tableWidget->scrollToItem(item,QAbstractItemView::PositionAtCenter);
        ui->tableWidget->selectRow(row);
    }
    ui->lineEdit->clear();
}

void MainWindow::deactivateAll()
{
    //Deactivate Arrows
    arrowIrSteuerwerk->activate(false);
    arrowIrPC->activate(false);
    arrowIrMulti->activate(false);
    arrowPcMulti->activate(false);
    arrowMultiRam->activate(false);
    arrowAluRam->activate(false);
    arrowAluAccu->activate(false);
    arrowAccuAlu->activate(false);
    arrowRamAlu->activate(false);
    arrowRamIr->activate(false);
    arrowAccuPc->activate(false);
    arrowPieceAluRamAccu->activate(false);
    arrowPieceIrMultiPc->activate(false);
    arrowPieceRamIrAlu->activate(false);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    if(loaded){
        QRectF bRect = ui->graphicsView->scene()->itemsBoundingRect();
        bRect.setX(bRect.x()-50);
        bRect.setY(bRect.y()-70);
        bRect.setWidth(bRect.width()+10);
        bRect.setHeight(bRect.height()+60);
        ui->graphicsView->fitInView(bRect,Qt::KeepAspectRatio);
    }
}


/* ---------------------- Convert Functions ----------------------
 * @author: Eva Charlotte Mayer
 */

QString MainWindow::showAsBin(ushort v)
{
    QString res = QString::number(v, 2);
    while(res.length()<16){
        res.insert(0,"0");
    }
    if(res.length() > 16)
    {
        res = res.right(16);
    }
    return res;
}

QString MainWindow::showAsHexa(ushort v)
{
    // Convert to binary and cut into address and command
    QString s = showAsBin(v);
    QString command = s.left(4);
    QString address = s.right(12);

    // Convert command and address into hexadecimals
    // and combine them into one string
    bool ok = false;
    QString res = QString::number(address.toUShort(&ok,2), 16);
    while(res.length() < 3)
    {
        res.insert(0, "0");
    }
    res.insert(0, QString::number(command.toUShort(&ok, 2), 16));

    return "$"+res;
}

QString MainWindow::showAsMnemonic(ushort v)
{
    // Receive string as hexadecimal
    // and find according command
    QString s = showAsHexa(v);
    s.remove(0,1);
    QString command;
    if(s.startsWith("0"))
    {
        command = "STO";
    }
    if(s.startsWith("1"))
    {
        command = "LDA";
    }
    if(s.startsWith("2"))
    {
        command = "BRZ";
    }
    if(s.startsWith("3"))
    {
        command = "ADD";
    }
    if(s.startsWith("4"))
    {
        command = "SUB";
    }
    if(s.startsWith("5"))
    {
        command = "OR";
    }
    if(s.startsWith("6"))
    {
        command = "AND";
    }
    if(s.startsWith("7"))
    {
        command = "XOR";
    }
    if(s.startsWith("8"))
    {
        return "NOT";
    }
    if(s.startsWith("9"))
    {
        return "INC";
    }
    if(s.startsWith("a"))
    {
        return "DEC";
    }
    if(s.startsWith("b"))
    {
        return "ZRO";
    }

    // Convert address and append command and address
    bool ok = false;
    QString address = QString::number(s.right(3).toUShort(&ok, 16), 10);
    QString res = command.append(" " + address);

    return res;
}

QString MainWindow::showOpCodeAsMnemonic(short op)
{
    if(op == 0)
    {
        return "STO";
    }
    if(op == 1)
    {
        return "LDA";
    }
    if(op == 2)
    {
        return "BRZ";
    }
    if(op == 3)
    {
        return "ADD";
    }
    if(op == 4)
    {
        return "SUB";
    }
    if(op == 5)
    {
        return "OR";
    }
    if(op == 6)
    {
        return "AND";
    }
    if(op == 7)
    {
        return "XOR";
    }
    if(op == 8)
    {
        return "NOT";
    }
    if(op == 9)
    {
        return "INC";
    }
    if(op == 10)
    {
        return "DEC";
    }
    if(op == 11)
    {
        return "ZRO";
    }
    if(op >= 12){
        return "nope";
    }
}


