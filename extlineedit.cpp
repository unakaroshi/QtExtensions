#include "extlineedit.h"
#include <QPushButton>
#include <QIcon>
#include <QPropertyAnimation>
#include <QSignalTransition>


CExtLineEdit::CExtLineEdit(QWidget* parent)
    : QLineEdit(parent)
    , m_animated(true)
    , m_animationDurationMS(500)
    , m_clearButton(new QPushButton(this))
    , m_textStateMachine(new QStateMachine(this))
    , m_textNotEmptyState(new QState(m_textStateMachine))
    , m_textEmptyState(new QState(m_textStateMachine))
    , m_animHideClearButton(new QPropertyAnimation(m_clearButton, "pos"))
    , m_animShowClearButton(new QPropertyAnimation(m_clearButton, "pos"))
{
    QPixmap buttonImage(":/Icon/remove_16.png");
    QIcon icon;
    icon.addPixmap(buttonImage, QIcon::Normal, QIcon::Off);

    m_clearButton->setFlat(true);
    m_clearButton->setIcon(icon);
    m_clearButton->setFocusPolicy(Qt::NoFocus);    
    m_clearButton->setCursor(Qt::ArrowCursor);

    m_animHideClearButton->setDuration(m_animationDurationMS);
    m_animHideClearButton->setEasingCurve(QEasingCurve::OutExpo);
    m_animShowClearButton->setDuration(m_animationDurationMS);
    m_animShowClearButton->setEasingCurve(QEasingCurve::OutBounce);

    // Note on the StateMachine:
    // Propertyassignment is added in CExtLineEdit::layoutClearButton()
    // because we don't no the size of the button here.
    // Starting of the the StateMachine is also done in CExtLineEdit::layoutClearButton().
    QSignalTransition *transition;
    transition = m_textNotEmptyState->addTransition(this, SIGNAL(textEmptyToggled()), m_textEmptyState);
    transition->addAnimation(m_animHideClearButton);

    transition = m_textEmptyState->addTransition(this, SIGNAL(textEmptyToggled()), m_textNotEmptyState);
    transition->addAnimation(m_animShowClearButton);

    connect(m_clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(this, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
}


bool CExtLineEdit::isAnimated()
{
    return m_animated;
}

void CExtLineEdit::setAnimated(bool animate)
{
    m_animated = animate;
    if ( m_animated ) {
        m_animHideClearButton->setDuration(m_animationDurationMS);
        m_animShowClearButton->setDuration(m_animationDurationMS);
    } else {
        m_animHideClearButton->setDuration(0);
        m_animShowClearButton->setDuration(0);
    }
}

int CExtLineEdit::animationDuration() {
    return m_animationDurationMS;
}

void CExtLineEdit::setAnimationDuration(int durationInMS) {
    m_animationDurationMS = durationInMS;
    if ( isAnimated() ) {
        m_animHideClearButton->setDuration(m_animationDurationMS);
        m_animShowClearButton->setDuration(m_animationDurationMS);
    }
}

void CExtLineEdit::ensureStateMachineIsRunning()
{
    if ( !m_textStateMachine->isRunning() ) {
        if ( text().isEmpty() ) {
            m_textStateMachine->setInitialState(m_textEmptyState);
        } else {
            m_textStateMachine->setInitialState(m_textNotEmptyState);
        }
        m_textStateMachine->start();
    }
}

void CExtLineEdit::resizeEvent(QResizeEvent* event)
{
      QLineEdit::resizeEvent(event);
      layoutClearButton();
}

void CExtLineEdit::layoutClearButton()
{
    ensurePolished();

    // If the statemachine is not running we start it here with the correct state.
    // This has to be done here because otherwise it is possible that someone calls
    // setText on the LineEdit and then the statemachine would be in the wrong state.
    ensureStateMachineIsRunning();

    QSize buttonSize = m_clearButton->minimumSizeHint();
    QPoint buttonVisiblePos(rect().right() - buttonSize.width(),(rect().height() - buttonSize.height() ) / 2);
    QPoint buttonInvisiblePos(rect().right(), (rect().height() - buttonSize.height() ) / 2);

    m_textNotEmptyState->assignProperty(m_clearButton, "pos", buttonVisiblePos);
    m_textEmptyState->assignProperty(m_clearButton, "pos", buttonInvisiblePos);

    if (m_textStateMachine->configuration().contains(m_textNotEmptyState)) {
        m_clearButton->setProperty("pos", buttonVisiblePos);
    } else {
        m_clearButton->setProperty("pos", buttonInvisiblePos);
    }
    //maybe the size has changed so we better set the text margins again
    int left, top, bottom;
    this->getTextMargins (&left, &top, 0, &bottom );
    this->setTextMargins(left, top, 2 + m_clearButton->minimumSizeHint().width() + 2, bottom);
}

void CExtLineEdit::onTextChanged(const QString &text)
{
    if (    ( text.isEmpty() && m_textStateMachine->configuration().contains(m_textNotEmptyState))
         || (!text.isEmpty() && m_textStateMachine->configuration().contains(m_textEmptyState))
       ) {
        emit textEmptyToggled();
    }
}
