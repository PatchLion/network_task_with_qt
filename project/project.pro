TEMPLATE = lib
CONFIG += staticlib
TARGET = NetworkTaskLib

include(public.pri)

INCLUDEPATH += .. . ../include \
../sources \
../../../commons/macro

win32{
    PRECOMPILED_HEADER = ../stdafx.h
}

QT += network core

DESTDIR += ../lib/$(Platform)/$(Configuration)

# Input
HEADERS += ../include/*.h \
../sources/*.h

SOURCES += ../sources/*.cpp
