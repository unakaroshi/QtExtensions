#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include "codeeditor.h"

class CLineNumberArea : public QWidget
{

private:
   CCodeEditor *codeEditor;

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

public:
    CLineNumberArea(CCodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }
};

#endif // LINENUMBERAREA_H
