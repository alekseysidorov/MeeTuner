######################################################################
# Automatically generated by qmake (2.01a) Tue Feb 7 15:06:07 2012
######################################################################

TEMPLATE = lib
TARGET = measureFreqXcorr
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += static

#QMAKE_CXXFLAGS += -O3 -ffast-math #fast mathematic

# Input
HEADERS += getNote.h \
           getNote_types.h \
           rt_nonfinite.h \
           rtGetInf.h \
           rtGetNaN.h \
           rtwtypes.h
SOURCES += getNote.cpp rt_nonfinite.cpp rtGetInf.cpp rtGetNaN.cpp

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/meetuner/lib
    INSTALLS += target
}
