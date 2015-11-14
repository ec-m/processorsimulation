#-------------------------------------------------
#
# Project created by QtCreator 2015-05-02T00:42:36
#
#-------------------------------------------------


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToyProcessor2
TEMPLATE = app

SOURCES += main.cpp\
    view/mainwindow.cpp \
    model/parser.cpp \
    model/toyexception.cpp \
    model/pseudoccompiler.cpp \
    model/preparser.cpp \
    model/row.cpp \
    model/variable.cpp \
    view/clock.cpp \
    view/controlunit.cpp \
    view/instructionregister.cpp \
    view/programcounter.cpp \
    view/accumulator.cpp \
    view/multiplexer.cpp \
    view/arithmeticlogicalunit.cpp \
    view/arrowtaktsteurwerk.cpp \
    view/randomaccessmemory.cpp \
    view/arrrowirsteuerwerk.cpp \
    view/arrowirprogramcounter.cpp \
    view/arrowirmultiplexer.cpp \
    view/arrowpcmultiplexer.cpp \
    view/arrowmultiplexerram.cpp \
    view/arrowaluram.cpp \
    view/arrowaluaccu.cpp \
    view/arrowaccualu.cpp \
    view/arrowramalu.cpp \
    view/arrowramir.cpp \
    model/akku.cpp \
    model/alu.cpp \
    model/controllunit.cpp \
    model/ir.cpp \
    model/model.cpp \
    model/mux.cpp \
    model/pc.cpp \
    model/modelram.cpp \
    model/message.cpp \
    controller/controller.cpp \
    controller/app.cpp \
    view/arrowaccupc.cpp \
    view/arrowwriteram.cpp \
    view/arrowincpc.cpp \
    view/arrowsetpc.cpp \
    view/arrowaddrisir.cpp \
    view/arrowsetir.cpp \
    view/arrowsetaccu.cpp \
    view/arrowalucin.cpp \
    view/arrowalumode.cpp \
    view/arrowalu3.cpp \
    view/arrowalu2.cpp \
    view/arrowalu1.cpp \
    view/arrowalu0.cpp \
    model/pseudocpreprocessor.cpp \
    model/syntaxtree.cpp \
    model/treenode.cpp \
    model/variabledeclarationnode.cpp \
    model/operationnode.cpp \
    model/inifinitlooptest.cpp\
    view/enterkeylistener.cpp \
    view/arrowpieceramiralu.cpp \
    view/arrowpieceirmultipc.cpp \
    view/arrowpiecealuramaccu.cpp \
    model/ifnode.cpp \
    model/loopnode.cpp \
    model/infoboxcontent.cpp


HEADERS  += view/mainwindow.h \
    model/parser.h \
    model/toyexception.h \
    model/pseudoccompiler.h \
    model/preparser.h \
    model/row.h \
    model/variable.h \
    view/clock.h \
    view/controlunit.h \
    view/instructionregister.h \
    view/programcounter.h \
    view/accumulator.h \
    view/multiplexer.h \
    view/arithmeticlogicalunit.h \
    view/arrowtaktsteurwerk.h \
    view/randomaccessmemory.h \
    view/arrrowirsteuerwerk.h \
    view/arrowirprogramcounter.h \
    view/arrowirmultiplexer.h \
    view/arrowpcmultiplexer.h \
    view/arrowmultiplexerram.h \
    view/arrowaluram.h \
    view/arrowaluaccu.h \
    view/arrowaccualu.h \
    view/arrowramalu.h \
    view/arrowramir.h \
    model/akku.h \
    model/alu.h \
    model/controllunit.h \
    model/ir.h \
    model/model.h \
    model/mux.h \
    model/pc.h \
    model/modelram.h \
    model/message.h \
    controller/controller.h \
    controller/app.h \
    view/arrowaccupc.h \
    view/arrowwriteram.h \
    view/arrowincpc.h \
    view/arrowsetpc.h \
    view/arrowaddrisir.h \
    view/arrowsetir.h \
    view/arrowsetaccu.h \
    view/arrowalucin.h \
    view/arrowalumode.h \
    view/arrowalu3.h \
    view/arrowalu2.h \
    view/arrowalu1.h \
    view/arrowalu0.h \
    model/pseudocpreprocessor.h \
    model/syntaxtree.h \
    model/treenode.h \
    model/variabledeclarationnode.h \
    model/operationnode.h \
    model/inifinitlooptest.h\
    view/enterkeylistener.h \
    view/arrowpieceramiralu.h \
    view/arrowpieceirmultipc.h \
    view/arrowpiecealuramaccu.h \
    model/ifnode.h \
    model/loopnode.h \
    model/infoboxcontent.h

FORMS    += uiForms/mainwindow.ui

RESOURCES += \
    icons.qrc

DISTFILES +=
CONFIG += warn_off
