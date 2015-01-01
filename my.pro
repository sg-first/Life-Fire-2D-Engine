#-------------------------------------------------
#
# Project created by QtCreator 2013-11-09T19:02:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    NewType.cpp \
    maincall.cpp \
    EngineBeh.cpp \
    event.cpp \
    KeyPress.cpp \
    library.cpp \
    js.cpp

HEADERS  += widget.h \
    head.h \
    GlobalVar.h \
    maincall.h \
    library.h \
    NewType.h

FORMS    += widget.ui
QT += core gui declarative

OTHER_FILES +=

QT += multimedia multimediawidgets
INSTALLS += target
QT += script
