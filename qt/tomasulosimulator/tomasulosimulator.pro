TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    instructionrecord.cpp

HEADERS += \
    fifo.h \
    instructionrecord.h
