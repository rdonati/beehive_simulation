#include "swarm.h"

/**
 * @brief Swarm::Swarm
 * Empty Constructor
 */
Swarm::Swarm()
{

}

/**
 * @brief Swarm::Swarm
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
Swarm::Swarm(std::string _HiveID, int _day, int _month, int _year, int _hours, int _minutes, int _seconds, int _num_bees)
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
 * @brief Swarm::~Swarm
 * Destructor
 */
Swarm::~Swarm()
{

}

/**
 * @brief Swarm::getStopped
 * Return state of window
 *
 * @return state of window
 */
bool Swarm::getStopped()
{
    return swarm.getStopped();
}

/**
 * @brief Swarm::showAlertWindow
 * Displays alert window with data from the UDP messages
 *
 * @param UDPMessage
 */
void Swarm::showAlertWindow(std::string UDPMessage)
{
    importInformationFromUDPMessage(UDPMessage);
    swarm.setHiveID(HiveID);
    swarm.setTime(htime);
    swarm.setDate(hdate);
    swarm.exec();

}

/**
 * @brief Swarm::importInformationFromUDPMessage
 * Imports data from UDPMesage
 *
 * @param UDP
 */
void Swarm::importInformationFromUDPMessage(std::string UDP)
{
    UDPMessageData message(UDP);
    HiveID = message.get_hiveID();
    hboards = message.get_boards();
    hdate = message.get_date();
    htime = message.get_time();
}

