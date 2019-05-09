#ifndef SWARM_H
#define SWARM_H

#include <QApplication>
#include "../AlertUI/swarmalertui.h"
#include "../UDPHandler/udpmessagedata.h"
#include "../UDPHandler/udphandler.h"
#include "../UDPHandler/HBoard.h"
#include "../UDPHandler/HDate.h"
#include "../UDPHandler/HTime.h"
#include <string>
#include <vector>
#include <QDialog>

//significant increase in the number of bees leaving the hive
//swarm starts at 18hrs

class Swarm
{
    std::string HiveID;
    int num_bees;

    HDate hdate;
    HTime htime;

    std::vector<HBoard> hboards;

    std::string UDPMessage;

    SwarmAlertUI swarm;

public:
    Swarm();
    Swarm(std::string _HiveID, int _day, int _month, int _year, int _hours, int _minutes, int _seconds, int _num_bees);
    Swarm(HBoard h);
    ~Swarm();

    bool getStopped();
    void showAlertWindow(std::string UDPMessage);
    void importInformationFromUDPMessage(std::string UDP);
};

#endif // SWARM_H
