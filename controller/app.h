#ifndef APP_H
#define APP_H
#include <QApplication>
#include "model/model.h"
#include "view/mainwindow.h"
#include "controller.h"
#include "model/parser.h"

// @author: Eva Charlotte Mayer

class App : public QApplication
{
public:
    App(int argc, char *argv[]);
private:   
    MainWindow window;
    Controller controller;
    Model model;
    Parser parser;
};

#endif // APP_H
