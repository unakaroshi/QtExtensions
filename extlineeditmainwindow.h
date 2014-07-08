#ifndef EXTLINEEDITMAINWINDOW_H
#define EXTLINEEDITMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CExtLineEditMainWindow;
}

class CExtLineEditMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CExtLineEditMainWindow(QWidget *parent = 0);
    ~CExtLineEditMainWindow();

private:
    Ui::CExtLineEditMainWindow *ui;
};

#endif // EXTLINEEDITMAINWINDOW_H
