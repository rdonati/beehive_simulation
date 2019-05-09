#ifndef ROB_H
#define ROB_H

#include <string>
#include <QDialog>
#include <vector>
#include "../UDPHandler/udpmessagedata.h"
#include "../UDPHandler/udphandler.h"
#include "../UDPHandler/HBoard.h"
#include "../UDPHandler/HDate.h"
#include "../UDPHandler/HTime.h"
#include "../AlertUI/robalertui.h"

//more coming in than going out
//starts at noon

class Rob
{
    std::string HiveID;
    int num_bees;

    HDate hdate;
    HTime htime;

    std::vector<HBoard> hboards;

    RobAlertUI rob;


public:
    Rob();
    Rob(std::string _HiveID, int _day, int _month, int _year, int _hours, int _minutes, int _seconds, int _num_bees);
    ~Rob();

    void showAlertWindow(std::string UDPMessage);
    void importInformationFromUDPMessage(std::string UDP);
    bool getStopped();
};

#endif // ROB_H
