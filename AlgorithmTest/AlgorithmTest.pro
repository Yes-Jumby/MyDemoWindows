#-------------------------------------------------
#
# Project created by QtCreator 2018-09-20T14:59:07
#
#-------------------------------------------------
QT       += core
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlgorithmTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        AlgorithmTest.cpp \
    MyLabel.cpp

HEADERS += \
        AlgorithmTest.h \
    MyLabel.h

FORMS += \
        AlgorithmTest.ui

DESTDIR += $$PWD/../Bin

INCLUDEPATH += $$PWD/Inc

CONFIG(debug, debug|release){
LIBS += $$PWD/Lib/AlgInspectorD.lib
}else{
LIBS += $$PWD/Lib/AlgInspector.lib
}

RESOURCES += \
    icon.qrc

RC_FILE = myIcon.rc #设置exe程序图标


