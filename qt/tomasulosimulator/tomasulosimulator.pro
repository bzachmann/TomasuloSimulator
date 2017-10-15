TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    instructionrecord.cpp \
    processor.cpp \
    reservationstationrecord.cpp \
    reservationstationaddsub.cpp \
    reservationstationmuldiv.cpp \
    functionalunit.cpp

HEADERS += \
    fifo.h \
    instructionrecord.h \
    processor.h \
    betterarray.h \
    reservationstationrecord.h \
    reservationstationaddsub.h \
    reservationstationmuldiv.h \
    functionalunit.h
