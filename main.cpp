#include "view/mainwindow.h"
#include "controller/app.h"

int main(int argc, char *argv[])
{
    App a(argc,argv);
    return a.exec();
}
