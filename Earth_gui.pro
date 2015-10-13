#-------------------------------------------------
#
# Project created by QtCreator 2015-04-01T11:20:48
#
#-------------------------------------------------

QT       += core gui

TARGET = Earth_gui
TEMPLATE = app


SOURCES += main.cpp\
        interface.cpp \
    glwidget.cpp \
    window.cpp \
    satellite.cpp

HEADERS  += interface.h \
    glwidget.h \
    window.h \
    satellite.h \
    dataTypes.h

FORMS    += interface.ui

QT           += opengl
LIBS += -lncurses

OTHER_FILES += \
    notes.txt
