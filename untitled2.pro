#-------------------------------------------------
#
# Project created by QtCreator 2020-03-22T09:50:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qimageshowwidget.cpp \
    haclon.cpp

HEADERS += \
        mainwindow.h \
    qimageshowwidget.h \
    haclon.h

FORMS += \
        mainwindow.ui
macx {
  LIBS          += -framework HALCONCpp
}
else {
  #defines
  win32:DEFINES += WIN32

  #includes
  INCLUDEPATH   += "$$(HALCONROOT)/include"
  INCLUDEPATH   += "$$(HALCONROOT)/include/halconcpp"

  #libs
  QMAKE_LIBDIR  += "$$(HALCONROOT)/lib/$$(HALCONARCH)"
  unix:LIBS     += -lhalconcpp -lhalcon -lXext -lX11 -ldl -lpthread
  win32:LIBS    += "$$(HALCONROOT)/lib/$$(HALCONARCH)/halconcpp.lib" \
                   "$$(HALCONROOT)/lib/$$(HALCONARCH)/halcon.lib"
}

INCLUDEPATH += E:\kinggsoft\include
INCLUDEPATH +=E:\kinggsoft\include\halconcpp
INCLUDEPATH +=E:\kinggsoft\include\com
INCLUDEPATH +=E:\kinggsoft\include\cpp
INCLUDEPATH +=E:\kinggsoft\include\halconc
INCLUDEPATH +=E:\kinggsoft\include\hdevengine
INCLUDEPATH +=E:\kinggsoft\include\hdevengine10
INCLUDEPATH +=E:\kinggsoft\include\hlib


LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalcon
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalconc
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalconcpp
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalconcpp10
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalconcpp10xl
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalconcppxl
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalconcxl
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalconx
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalconxl
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhalconxxl
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhdevenginecpp
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhdevenginecpp10
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhdevenginecpp10xl
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhdevenginecppxl
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhdevenginex
LIBS += -LE:/kinggsoft/lib/x86sse2-win32/ -lhdevenginexxl




