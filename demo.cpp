#include "demo.h"
#include "ui_demo.h"

CDemo::CDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CDemo)
{
    ui->setupUi(this);

    connect(ui->btnNextPage, SIGNAL(clicked()), ui->stackedWidget, SLOT(nextPage()));
}

CDemo::~CDemo()
{
    delete ui;
}
