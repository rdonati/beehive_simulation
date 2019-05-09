#-------------------------------------------------
#
# Project created by QtCreator 2019-04-16T13:29:44
#
#-------------------------------------------------

QT       += core gui \
            multimedia \
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomerGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    beechimes.cpp \
    ../DatabaseUI/dbtest/dbtable.cpp \
    ../DatabaseUI/dbtest/dbtool.cpp \
    ../DatabaseUI/dbtest/messagetable.cpp \
    ../DatabaseUI/dbtest/usertable.cpp \
    ../DatabaseUI/user.cpp \
    ../DatabaseUI/createuserscreen.cpp \
    ../DatabaseUI/sqlite-amalgamation-3280000/sqlite3.c \
    ../AlertSystem/alert.cpp \
    ../AlertSystem/rob.cpp  \
    ../AlertSystem/swarm.cpp \
    ../AlertUI/robalertui.cpp \
    ../AlertUI/swarmalertui.cpp \
    ../Beehive/bee.cpp \
    ../Beehive/beehive.cpp \
    ../Beehive/board.cpp \
    ../Beehive/brood.cpp \
    ../Beehive/drone.cpp \
    ../Beehive/forager.cpp \
    ../Beehive/juvinile.cpp \
    ../Beehive/nurse.cpp \
    ../Beehive/queen.cpp \
    ../Beehive/worker.cpp \
    ../UDPHandler/dataanalyzer.cpp \
    ../UDPHandler/HBoard.cpp \
    ../UDPHandler/HDate.cpp \
    ../UDPHandler/HTime.cpp \
    ../UDPHandler/realtimesimulator.cpp \
    ../UDPHandler/udphandler.cpp \
    ../UDPHandler/udpmessagedata.cpp \
    ../WeatherGUI/weatherwidg.cpp \
    welcomescreen.cpp


HEADERS += \
    mainwindow.h \
    beechimes.h \
    ../DatabaseUI/dbtest/dbtable.h \
    ../DatabaseUI/dbtest/dbtool.h \
    ../DatabaseUI/dbtest/messagetable.h \
    ../DatabaseUI/dbtest/usertable.h \
    ../DatabaseUI/createuserscreen.h \
    ../DatabaseUI/user.h \
    ../Beehive/bee.h \
    ../Beehive/beehive.h \
    ../Beehive/board.h \
    ../Beehive/brood.h \
    ../Beehive/drone.h \
    ../Beehive/forager.h \
    ../Beehive/juvinile.h \
    ../Beehive/nurse.h \
    ../Beehive/queen.h \
    ../Beehive/worker.h \
    ../DatabaseUI/sqlite-amalgamation-3280000/sqlite3.h \
    ../AlertSystem/alert.h \
    ../AlertSystem/rob.h  \
    ../AlertSystem/swarm.h \
    ../AlertUI/robalertui.h \
    ../AlertUI/swarmalertui.h \
    ../UDPHandler/dataanalyzer.h \
    ../UDPHandler/HBoard.h \
    ../UDPHandler/HDate.h \
    ../UDPHandler/HTime.h \
    ../UDPHandler/realtimesimulator.h \
    ../UDPHandler/udphandler.h \
    ../UDPHandler/udpmessagedata.h \
    ../WeatherGUI/weatherwidg.h \
    welcomescreen.h

FORMS += \
        mainwindow.ui \
    beechimes.ui \
    ../AlertUI/robalertui.ui \
    ../AlertUI/swarmalertui.ui \
    ../DatabaseUI/createuserscreen.ui \
    ../WeatherGUI/weatherwidg.ui \
    welcomescreen.ui
#LIBS += -l sqlite3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
