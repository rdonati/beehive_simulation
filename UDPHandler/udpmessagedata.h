#ifndef UDPMESSAGEDATA_H
#define UDPMESSAGEDATA_H

#include <iostream>
#include <vector>
#include "udphandler.h"
#include "HBoard.h"
#include "HDate.h"
#include "HTime.h"

class UDPMessageData
{
private:
    std::vector<HBoard> boards;
    HDate date;
    HTime time;
    std::string hiveID;
    std::string message = "";
public:
    /**
     * @brief UDPMessageData Creates a new UDPMessageData
     * @param m UDP message
     */
    UDPMessageData(std::string m);

    /**
     * @brief UDPMessageData Creates a new UDPMessageData
     * @param hID Hive ID (string)
     * @param d Date (HDate)
     * @param t Time (HTime)
     * @param bs Boards (vector of HBoards)
     */
    UDPMessageData(std::string hID, HDate d, HTime t,  std::vector<HBoard> bs);

    /**
     * @brief UDPMessageData Creates a new UDPMessageData
     * @param hID Hive ID (string)
     * @param d Date (HDate)
     * @param t Time (HTime)
     * @param bs Boards (vector of a vector of booleans)
     */
    UDPMessageData(std::string hID, HDate d, HTime t,  std::vector<std::vector<bool>> gs);

    /**
     * @brief to_string Comprehensively prints all data to the console
     */
    void to_string();

    /**
     * @brief musicify Converts a UDP message into the format needed by Beechimes
     * @return A vector with an index for every gate n on a board where the value at each index is the number of Gates where the nth gate is active
     */
    std::vector<int> musicify();

    // Getters
    std::vector<HBoard> get_boards();
    HDate get_date();
    HTime get_time();
    std::string get_hiveID();
    std::string get_message();
};

#endif // UDPMESSAGEDATA_H

