TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    udphandler.cpp \
    udpmessagedata.cpp \
    HDate.cpp \
    HBoard.cpp \
    dataanalyzer.cpp \
    HTime.cpp \
    realtimesimulator.cpp

HEADERS += \
    HTime.h \
    udphandler.h \
    udpmessagedata.h \
    HDate.h \
    HBoard.h \
    dataanalyzer.h \
    realtimesimulator.h

FORMS +=
