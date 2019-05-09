#include "rob.h"

/**
 * @brief Rob::Rob
 * Empty Constructor
 */
Rob::Rob()
{

}

/**
 * @brief Rob::Rob
 * Constructor for testing purposes
 *
 * @param _HiveID
 * @param _day
 * @param _month
 * @param _year
 * @param _hours
 * @param _minutes
 * @param _seconds
 * @param _num_bees
 */
Rob::Rob(std::string _HiveID, int _day, int _month, int _year, int _hours, int _minutes, int _seconds, int _num_bees)
{
    HiveID = _HiveID;
    hdate.set_day(_day);
    hdate.set_month(_month);
    hdate.set_year(_year);
    htime.set_hours(_hours);
    htime.set_minutes(_minutes);
    htime.set_millis(_seconds * 1000);
}

/**
 * @brief Rob::~Rob
 * Destructor
 */
Rob::~Rob()
{

}

/**
 * @brief Rob::showAlertWindow
 * Displays alert window with data from the UDP messages
 *
 * @param UDPMessage
 */
void Rob::showAlertWindow(std::string UDPMessage)
{
    importInformationFromUDPMessage(UDPMessage);
    rob.setHiveID(HiveID);
    rob.setTime(htime);
    rob.setDate(hdate);
    rob.exec();

}

/**
 * @brief Rob::importInformationFromUDPMessage
 * Imports data from UDPMessage
 * @param UDP
 */
void Rob::importInformationFromUDPMessage(std::string UDP)
{
    UDPMessageData message(UDP);
    HiveID = message.get_hiveID();
    hboards = message.get_boards();
    hdate = message.get_date();
    htime = message.get_time();
}

/**
 * @brief Rob::getStopped
 * Returns true if user pressed stop
 *
 * @return state of window
 */
bool Rob::getStopped()
{
    return rob.getStopped();
}

