#ifndef REALTIMESIMULATOR_H
#define REALTIMESIMULATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "udpmessagedata.h"


class RealTimeSimulator
{
private:
    std::vector<UDPMessageData*> messages;
public:
    RealTimeSimulator(std::string in);
    void run(int scaleFactor);
};

#endif // REALTIMESIMULATOR_H
