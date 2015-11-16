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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QColorDialog>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtGui>
#include <QObject>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QRegExp>
#include <QSpinBox>
#include "QDebug"
#include "QFileDialog"
#include "QToolButton"

// components (Ram, Accu, etc.)
#include "clock.h"
#include "controlunit.h"
#include "instructionregister.h"
#include "programcounter.h"
#include "randomaccessmemory.h"
#include "accumulator.h"
#include "multiplexer.h"
#include "arithmeticlogicalunit.h"

// arrows
#include "arrowtaktsteurwerk.h"
#include "arrrowirsteuerwerk.h"
#include "arrowirprogramcounter.h"
#include "arrowirmultiplexer.h"
#include "arrowpcmultiplexer.h"
#include "arrowmultiplexerram.h"
#include "arrowaluram.h"
#include "arrowaluaccu.h"
#include "arrowaccualu.h"
#include "arrowramalu.h"
#include "arrowramir.h"
#include "arrowaccupc.h"

// arrow pieces
#include "arrowpieceramiralu.h"
#include "arrowpieceirmultipc.h"
#include "arrowpiecealuramaccu.h"

// state arrows
#include "arrowwriteram.h"
#include "arrowincpc.h"
#include "arrowsetpc.h"
#include "arrowaddrisir.h"
#include "arrowsetir.h"
#include "arrowsetaccu.h"
#include "arrowalucin.h"
#include "arrowalumode.h"
#include "arrowalu3.h"
#include "arrowalu2.h"
#include "arrowalu1.h"
#include "arrowalu0.h"

// messages
#include "model/message.h"

// custom filter for tabel widget
#include "enterkeylistener.h"

// @author: Daniel Muszkiet

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QColor activeColor;
    QColor notActiveColor;  

signals:
    void sendMessage(Message &msg);

public slots:

    void notify(Message& msg);

    void RAMupdate(int row, int col,QString newVal, QString oldVal);

    void notActiveColorChange(QColor c);

    void activeColorChange(QColor c);

private slots:

    void on_actionLoadFile_triggered();

    void on_actionDokumentation_triggered();

    void on_actionStart_triggered();

    void on_actionStep_Mode_triggered();

    void on_actionAutomaticMode_triggered();

    void on_actionCycle_Modus_triggered();        

    void PCupdate();

    void OpCodeUpdate();

    void AdresseUpdate();

    void accuUpdate();

    void on_actionReset_triggered();

    void on_actionHalf_Cycle_Mode_triggered();

    void on_actionStop_triggered();

    void on_actionAktive_Farbe_triggered();

    void on_actionNicht_aktive_Farbe_triggered();

    void on_pushButton_clicked();

    void on_actionSeperateArrow_triggered();

    void on_actionWholeArrow_triggered();

    void on_actionMnemonic_triggered();

    void on_actionHexadezimal_triggered();

    void on_actionBin_r_triggered();

    void on_actionDezimal_triggered();

    void on_actionSpeedA_triggered();

    void on_actionSpeedB_triggered();

    void on_actionFullspeed_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    void resizeEvent(QResizeEvent *e);

    bool loaded;

    bool showAll;

    void initializeWindow();

    void setGraphicsScene();

    void createElements();

    void deactivateAll();

    void setColor();

    QString showAsBin(ushort v);
    QString showAsHexa(ushort v);
    QString showAsMnemonic(ushort v);
    QString showOpCodeAsMnemonic(short op);

    Clock  *clocky;
    ControlUnit *controlUnit;
    InstructionRegister *instructionRegister;
    ProgramCounter *programCounter;
    RandomAccessMemory *ram;
    Accumulator *accumulator;
    Multiplexer *multiplexer;
    ArithmeticLogicalUnit *alu;

    ArrowTaktSteuerwerk *arrowTaktSteuerwerk;
    ArrowIRSteuerwerk *arrowIrSteuerwerk;
    ArrowIrProgramcounter *arrowIrPC;
    ArrowIrMultiplexer *arrowIrMulti;
    ArrowPcMultiplexer *arrowPcMulti;
    ArrowMultiplexerRam *arrowMultiRam;
    ArrowAluRam *arrowAluRam;
    ArrowAluAccu *arrowAluAccu;
    ArrowAccuAlu *arrowAccuAlu;
    ArrowRamAlu *arrowRamAlu;
    ArrowRamIr *arrowRamIr;
    ArrowAccuPc *arrowAccuPc;

    ArrowPieceRamIrAlu *arrowPieceRamIrAlu;
    ArrowPieceIrMultiPc *arrowPieceIrMultiPc;
    ArrowPieceAluRamAccu *arrowPieceAluRamAccu;

    ArrowWriteRam *arrowWriteRam;
    ArrowIncPc *arrowIncPc;
    ArrowSetPc *arrowSetPc;
    ArrowAddrIsIR *arrowAddrIsIR;
    ArrowSetIr *arrowSetIr;
    ArrowSetAccu *arrowSetAccu;
    ArrowAluCin *arrowAluCin;
    ArrowAluMode *arrowAluMode;
    ArrowAlu3 *arrowAlu3;
    ArrowAlu2 *arrowAlu2;
    ArrowAlu1 *arrowAlu1;
    ArrowAlu0 *arrowAlu0;

    QLineEdit *pcValue;
    QLineEdit *irOpCode;
    QLineEdit *irAdresse;
    QLineEdit *accu;

    QGraphicsTextItem* infobox;

    QColorDialog *colorPicker;
    QColorDialog *colorPicker2;

    QSpinBox *speed;

    short currformat;

    enum format{
        decimal,
        binary,
        hexa,
        mnemonic
    };

    int opCodeNumber;
};

#endif // MAINWINDOW_H
