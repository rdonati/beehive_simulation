#ifndef ALERT_H
#define ALERT_H

#include <string>
#include <QDialog>
#include <vector>
#include "../UDPHandler/udpmessagedata.h"
#include "../UDPHandler/udphandler.h"
#include "../UDPHandler/HBoard.h"
#include "../UDPHandler/HDate.h"
#include "../UDPHandler/HTime.h"
#include "../AlertUI/robalertui.h"
#include "../UDPHandler/dataanalyzer.h"
#include "swarm.h"
#include "rob.h"

class Alert
{
    std::vector<std::string> UDPMessages;
    std::string currentUDPMessage;
    std::vector<std::vector<HBoard>> boards;

    std::vector<HBoard> hboards;
    int numBeesIn;
    int numBeesOut;
    int time;

    int numMessages;


public:
    Alert();
    void addUDPMessage(std::string UDP);
    void detectSwarm();
    void detectRob();
    bool stopped= false;
    DataAnalyzer * da;

};

#endif // ALERT_H
