#ifndef EXTLINEEDIT_H
#define EXTLINEEDIT_H

#include <QLineEdit>
#include <QResizeEvent>
#include <QPushButton>
#include <QState>
#include <QStateMachine>
#include <QPropertyAnimation>

/**
 * @brief Extension of the QLineEdit-Class which has a Clear-Button which can be animated.
 */
class CExtLineEdit : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)

private:
    bool m_animated; ///< Is the animation of the Clear-Button shown or not? (default: true)
    int  m_animationDurationMS; ///< How long should the animation of the Clear-Button last? (default: 500)

protected:
    QPushButton *m_clearButton; ///< The button which is shown on the left side of the LineEdit

    QStateMachine *m_textStateMachine; ///< The statemachine which handles if the Clear-Button has to be shown or not
    QState *m_textNotEmptyState; ///< The state when the textfield is not empty (Clear-Button shown)
    QState *m_textEmptyState; ///< The state when the textfield is empty (Clear-Button shown)

    QPropertyAnimation *m_animHideClearButton; ///< Animation for the hidingeffect of the Clear-Button
    QPropertyAnimation *m_animShowClearButton; ///< Animation for the showingeffect of the Clear-Button


    void layoutClearButton();
    void ensureStateMachineIsRunning();

public:
    CExtLineEdit(QWidget *parent = 0);

    /**
     * @brief Calls the baseclasses resizeEvent and then lays out the Clear-Button.
     * @param event The event
     */
    void resizeEvent(QResizeEvent* event);

    /**
     * @brief Returns whether the Clear-Button is animated or not (default: true).
     *
     * @return true, if the Clear-Button is animated, false otherwise.
     */
    bool isAnimated();

    /**
     * @brief Sets whether the Clear-Button should be animated or not.
     * @param animate true, if the Clear-Button should be animated, false otherwise.
     */
    void setAnimated(bool animate);

    /**
     * @brief Gets the duration of the animation in ms.(default: 500ms)
     * @return The duration of the animation in ms.
     */
    int animationDuration();

    /**
     * @brief Sets the duration of the animation
     * @param durationInMS Duration in ms.
     */
    void setAnimationDuration(int durationInMS);

public slots:
    void onTextChanged(const QString &text);

signals:
    void textEmptyToggled();

};

#endif // EXTLINEEDIT_H
