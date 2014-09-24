TARGET   = QtExtensions
TEMPLATE = app

QT += core 
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES   += \
             demo.cpp      \
             extlineedit.cpp                \
             extstackedwidget.cpp           \
             main.cpp                       \
    codeeditor.cpp

HEADERS   += \
             demo.h \
             extlineedit.h           \
             extstackedwidget.h      \
    codeeditor.h \
    linenumberarea.h

FORMS     += \
             demo.ui      \

RESOURCES += Resources.qrc
