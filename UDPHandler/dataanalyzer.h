#ifndef DATAANALYZER_H
#define DATAANALYZER_H

#include <iostream>
#include <vector>
#include <fstream>

#include "udpmessagedata.h"

class DataAnalyzer
{
private:
    int gateSize;
    std::vector<std::vector<int>> pathStatuses;
    std::vector<std::vector<HTime>> pathLastActivity;
    int numOfBoards;
    int numOfGates;
    int gateToPath(int n);
public:
    std::vector<UDPMessageData*> messages;

    /**
     * @brief DataAnalyzer Creates a new DataAnalyzer object
     * @param f The file of UDP messages to read from
     */
    DataAnalyzer(std::string f);

    /**
     * @brief DataAnalyzer Creates a new DataAnalyzer object
     * @param m A UDP message
     */
    DataAnalyzer(UDPMessageData * m);

    /**
     * @brief printData Comprehensively prints all UDP messages
     */
    void printData();

    /**
     * @brief analyze Analyzes UDP messages
     * @return An vector or size 3 where index 1 = bees in, 2 = bees out, 3 = exceptions/errors
     */
    std::vector<int> analyze();

    /**
     * @brief analyzeComprehensive Analyzes UDP messages and prints them out as it goes
     * @return An vector or size 3 where index 1 = bees in, 2 = bees out, 3 = exceptions/errors
     */
    std::vector<int> analyzeComprehensive();

    /**
     * @brief updateState Updates the hive's state given a new UDP message
     * @param m UDP message
     * @return An vector or size 3 where index 1 = bees in, 2 = bees out, 3 = exceptions/errors
     */
    std::vector<int> updateState(UDPMessageData *m);

    /**
     * @brief reset Resets the hive's state
     */
    void reset();

    /**
     * @brief printState Prints the hive's state
     */
    void printState();

    /**
     * @brief printMessage Comprehensively prints a UDP message
     * @param m UDP message
     */
    void printMessage(UDPMessageData *m);
};

#endif // DATAANALYZER_H

