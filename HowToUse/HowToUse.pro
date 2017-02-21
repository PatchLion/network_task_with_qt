TEMPLATE = app
TARGET = HowToUse
QT += core network gui widgets

include(../public.pri)

INCLUDEPATH += ../include .. . \

win32{
    LIBS += -L../lib/$(Platform)/$(Configuration)
    DESTDIR = ../bin/$(Platform)/$(Configuration)
}

unix:!macx{
    LIBS += -L../lib
    DESTDIR = ../bin
}

macx{
    LIBS += -L../lib
    DESTDIR = ../bin
}

LIBS += -lNetworkTaskLib

# Input
HEADERS += ./*.h

SOURCES += ./*.cpp

FORMS += ./*.ui

#RESOURCES += ../resources/*.qrc
