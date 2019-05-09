TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dbtool.cpp \
    dbtableex.cpp \
    dbtable.cpp \
    messagetable.cpp

HEADERS += \
    dbtool.h \
    dbtableex.h \
    dbtable.h \
    messagetable.h

LIBS += -l sqlite3
