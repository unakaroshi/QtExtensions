#include "extlineeditmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CExtLineEditMainWindow w;
    w.show();

    return a.exec();
}
