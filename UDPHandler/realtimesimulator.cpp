#include "realtimesimulator.h"

RealTimeSimulator::RealTimeSimulator(std::string f)
{
    std::ifstream file(f);
    for(std::string line; getline(file, line);){
        UDPMessageData *temp = new UDPMessageData(line);
        messages.push_back(temp);
    }
}

void RealTimeSimulator::run(int scaleFactor){
    std::cout << messages[1]->get_message() << std::endl;
    for(int i = 1; i < messages.size(); i++){
        long timeToWait = messages[i]->get_time().compare_to(messages[i-1]->get_time());
        std::cout << "Time to wait: " << timeToWait << "/" << scaleFactor << " = " << (timeToWait / scaleFactor) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait / scaleFactor));
        std::cout << messages[i]->get_message() << std::endl;
    }
}
