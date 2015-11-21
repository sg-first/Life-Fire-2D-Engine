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
    js.cpp \
    AES.cpp \
    EngineAPI.cpp \
    EngineBeh.cpp \
    SC.cpp \
    InputEvent.cpp

HEADERS  += widget.h \
    head.h \
    GlobalVar.h \
    maincall.h \
    library.h \
    NewType.h \
    AES.h \
    js.h \
    macro.h

FORMS    += widget.ui
QT += core gui declarative

OTHER_FILES +=

QT += multimedia multimediawidgets
INSTALLS += target
QT += script
QMAKE_CXXFLAGS += -std=c++11
