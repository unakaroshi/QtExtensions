#ifndef EXTSTACKEDWIDGET_H
#define EXTSTACKEDWIDGET_H

#include <QStackedWidget>

class CExtStackedWidget : public QStackedWidget
{
    Q_OBJECT

private:
    bool m_animate;
    int m_tempNextIndex;


public:
    explicit CExtStackedWidget(QWidget *parent = 0);

signals:

public slots:
    void nextPage();
    void gotoPage(int index);


private slots:
    void pageMovingOutFinished();

};

#endif // EXTSTACKEDWIDGET_H
