TEMPLATE = app
TARGET = LaserLine
DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += ./LaserLine.h
SOURCES += ./LaserLine.cpp \
    ./main.cpp
FORMS += ./LaserLine.ui

DEPENDPATH += $$PWD/Lib
INCLUDEPATH +=  C:\extern_libs\opencv\opencv_3_2\include
INCLUDEPATH +=  C:\extern_libs\opencv\opencv_3_2\include\opencv
INCLUDEPATH +=  C:\extern_libs\opencv\opencv_3_2\include\opencv2
LIBS += C:\extern_libs\opencv\opencv_3_2\x64\vc14\lib\*.lib
