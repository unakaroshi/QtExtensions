#include "extstackedwidget.h"
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QThread>


CExtStackedWidget::CExtStackedWidget(QWidget *parent) :
    QStackedWidget(parent)
  , m_animate(true)
  , m_tempNextIndex(0)
{
}


void CExtStackedWidget::pageMovingOutFinished()
{
    widget(m_tempNextIndex)->setGeometry(currentWidget()->geometry().width(),0,currentWidget()->geometry().width(),currentWidget()->geometry().height());
    setCurrentIndex(m_tempNextIndex);
    //currentWidget()

    if ( m_animate ) {
        QPropertyAnimation *anim = new QPropertyAnimation(currentWidget(),"pos");

        QPoint target(0, 0);
        QPoint start(currentWidget()->geometry().width(), 0);

        anim->setStartValue(start);
        anim->setEndValue(target);
        anim->setDuration(500);
        anim->setEasingCurve(QEasingCurve::OutQuad);

        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void CExtStackedWidget::nextPage()
{
    gotoPage((currentIndex()+1) % this->count());
}

void CExtStackedWidget::gotoPage(int index)
{
    m_tempNextIndex = index;
    if ( m_animate ) {
        QPropertyAnimation *anim = new QPropertyAnimation(currentWidget(),"pos");

        QPoint target(currentWidget()->geometry().width()*(-1), currentWidget()->geometry().y());
        QPoint start(currentWidget()->geometry().x(), currentWidget()->geometry().y());

        anim->setStartValue(start);
        anim->setEndValue(target);
        anim->setDuration(500);
        anim->setEasingCurve(QEasingCurve::InQuad);
        connect(anim, SIGNAL(finished()), this, SLOT(pageMovingOutFinished()));

        anim->start(QAbstractAnimation::DeleteWhenStopped);
    } else {
        pageMovingOutFinished();
    }
}
