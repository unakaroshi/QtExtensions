#include "extlineeditmainwindow.h"
#include "ui_extlineeditmainwindow.h"

CExtLineEditMainWindow::CExtLineEditMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CExtLineEditMainWindow)
{
    ui->setupUi(this);
}

CExtLineEditMainWindow::~CExtLineEditMainWindow()
{
    delete ui;
}
