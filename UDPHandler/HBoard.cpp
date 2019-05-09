#include "HBoard.h"

/**
 * @brief HBoard::HBoard Empty constructor
 */
HBoard::HBoard(){}

/**
 * @brief HBoard::HBoard
 * @param s Sensors
 */
HBoard::HBoard(std::vector<bool> s){
    set_sensors(s);
}

/**
 * @brief HBoard::get_sensors Gets the sensors
 * @return Sensors
 */
std::vector<bool> HBoard::get_sensors(){
    return sensors;
}

/**
 * @brief HBoard::set_sensors Sets values for the sensors
 * @param s Sensors
 */
void HBoard::set_sensors(std::vector<bool> s){
    sensors = s;
}
