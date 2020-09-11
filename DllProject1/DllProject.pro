#-------------------------------------------------
#
# Project created by QtCreator 2019-01-23T09:51:20
#
#-------------------------------------------------

QT       -= gui
QT       += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DllProject1
TEMPLATE = lib

DEFINES += DLLPROJECT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DESTDIR += $$PWD/../Bin

SOURCES += \
        DllProject.cpp \
    DllProjectImpl.cpp

HEADERS += \
        DllProject.h \
    DllProjectImpl.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
