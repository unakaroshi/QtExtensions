#ifndef EXTLINEEDITMAINWINDOW_H
#define EXTLINEEDITMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CDemo;
}

class CDemo : public QMainWindow
{
    Q_OBJECT

private:
    Ui::CDemo *ui;

public:
    explicit CDemo(QWidget *parent = 0);
    ~CDemo();

};

#endif // EXTLINEEDITMAINWINDOW_H
