#-------------------------------------------------
#
# Project created by QtCreator 2019-01-02T16:38:37
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG(debug, debug|release){
TARGET = RouteManageD
}else{
TARGET = RouteManage
}
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
        RouteManage.cpp \
    RouteManager.cpp \
    QtFileOperate.cpp \
    DlgRouteManage.cpp

HEADERS += \
        RouteManage.h \
    RouteManager.h \
    QtFileOperate.h \
    DlgRouteManage.h

FORMS += \
        RouteManage.ui \
    DlgRouteManage.ui
DESTDIR += $$PWD/../Bin
DEPENDPATH += $$PWD/Lib
INCLUDEPATH +=  $$PWD/Inc
CONFIG(debug, debug|release){
LIBS += $$PWD/Lib/LibMotionCardD.lib
}else{
LIBS += $$PWD/Lib/LibMotionCard.lib
}
