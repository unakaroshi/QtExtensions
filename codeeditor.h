#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

class CCodeEditor : public QPlainTextEdit
{
    Q_OBJECT

private:
    QWidget *lineNumberArea;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);


protected:
    void resizeEvent(QResizeEvent *event);

public:
    explicit CCodeEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
};

#endif // CODEEDITOR_H
