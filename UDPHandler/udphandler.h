#ifndef UDPHANDLER_H
#define UDPHANDLER_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "HTime.h"
#include "HDate.h"
#include "HBoard.h"
#include "math.h"


class UDPHandler
{
private:
    std::string UDPMessage;
    std::vector<bool> sensors;
    std::string dateString;
    std::string timeString;
    std::string hiveID;
    std::string gateString;
public:
    /**
     * @brief UDPHandler Creates a new UDPHandler object
     */
    UDPHandler();

    /**
     * @brief read_UDP Reads a UDP message
     * @param message UDP message
     */
    void read_UDP(std::string message);

    /**
     * @brief encode_boards Encodes boards into UDP format (e.g. B123B0B84...)
     * @param gs A vector of a vector of booleans (boards of gates)
     * @return The boards in UDP format
     */
    std::string encode_boards(std::vector<std::vector<bool>> gs);

    /**
     * @brief create_message Creates a UDP message from its components
     * @param hID Hive ID (string)
     * @param d Date (HDate)
     * @param t Time (HTime)
     * @param gs Gates (vector of vectors of booleans)
     * @return Gates in UDP format
     */
    std::string create_message(std::string hID, HDate d, HTime t,  std::vector<std::vector<bool>> gs);

    /**
     * @brief decode_gates Converts board from UDP format (e.g. B322) to a vector of booleans representing gates
     * @param s Board in UDP format (e.g. B322)
     * @return Vector of booleans representing gates
     */
    std::vector<bool> decode_gates(std::string s);

    /**
     * @brief encode_gates Converts from a vector of booleans to a gate in UDP format (e.g. B322)
     * @param g Vector of booleans (gates)
     * @return Board in UDP format (e.g. B322)
     */
    std::string encode_gates(std::vector<bool> g);

    /**
     * @brief to_string Comprehensively prints all data to the console
     */
    void to_string();

    //Getters/setters
    std::string get_hiveID();
    std::vector<HBoard> get_boards();
    HDate get_date();
    HTime get_time();
    std::string get_message();
    void set_message();
};

#endif // UDPHANDLER_H

