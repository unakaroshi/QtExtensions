#include "demo.h"
//#include "extstackedwidgetmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CDemo w;
    w.show();

    return a.exec();
}
