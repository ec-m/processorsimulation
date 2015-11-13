#include "app.h"

// @author: Eva Charlotte Mayer

App::App(int argc, char *argv[]) : QApplication(argc, argv)
{
    this->window.show();

    /* Connections */
    connect(&this->model, SIGNAL(sendMessage(Message&)), &this->window, SLOT(notify(Message&)));
    connect(&this->controller, SIGNAL(sendMessage(Message&)), &this->model, SLOT(notify(Message&)));
    connect(&this->window, SIGNAL(sendMessage(Message&)), &this->controller, SLOT(notify(Message&)));
    connect(&this->controller, SIGNAL(sendMessage(Message&)), &this->window, SLOT(notify(Message&)));
    connect(this->model.sendParserPointer(), SIGNAL(sendMessage(Message&)), &this->window, SLOT(notify(Message&)));
}

