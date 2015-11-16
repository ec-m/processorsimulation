/*
 * This file is part of Processorsimulation.
 * Author: Eva Charlotte Mayer <eva-charlotte.mayer@posteo.de>
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

#include "app.h"

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

