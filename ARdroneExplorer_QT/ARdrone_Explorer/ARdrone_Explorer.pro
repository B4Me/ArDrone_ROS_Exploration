#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T22:42:24
#
#-------------------------------------------------

QT       += core gui

TARGET = ARdrone_Explorer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    path_window.cpp \
    drone_item.cpp \
    mythread.cpp \
    dataworker.cpp

HEADERS  += mainwindow.h \
    path_window.h \
    drone_item.h \
    mythread.h \
    dataworker.h

FORMS    += mainwindow.ui \
    path_window.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    test.qml
