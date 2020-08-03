#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T13:33:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

msvc:QMAKE_CXXFLAGS += /utf-8

TARGET              = netcomtool
TEMPLATE            = app
MOC_DIR             = temp/moc
RCC_DIR             = temp/rcc
UI_DIR              = temp/ui
OBJECTS_DIR         = temp/obj
DESTDIR             = bin
win32:RC_FILE       = other/main.rc
CONFIG              += warn_off
CONFIG				+= C++11

include             ($$PWD/src/src.pri)

INCLUDEPATH         += $$PWD
INCLUDEPATH         += $$PWD/src

RESOURCES += \
	other/main.qrc

