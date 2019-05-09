#include "alert.h"

/**
 * @brief Alert::Alert
 * Empty constructor to set up numBeesIn, numBeesOut, and numMessages
 */
Alert::Alert()
{
    numBeesIn = 0;
    numBeesOut = 0;
    numMessages = 0;
}

/**
 * @brief Alert::addUDPMessage
 * Adds UDP message to alert object. Message is then used to update numBeesIn and numBeesOut to determine a rob or swarm
 *
 * @param UDP Message that is recieved that contains bee information
 */
void Alert::addUDPMessage(std::string UDP)
{
    //set up UDP Message to be used
    numMessages++;
    UDPMessageData message(UDP);
    hboards = message.get_boards();
    currentUDPMessage = UDP;
    if(boards.size() > 20) {
        boards.erase(boards.begin());
    }

    if(hboards.size() != 0) {

        //translate bee movement from UDP Message
        std::vector<int> activity;
        activity = da->updateState(&message);
        numBeesIn += activity[0];
        std::cout << "Added " << activity[0] << " to numBeesIn" << std::endl;
        numBeesOut += activity[1];
        std::cout << "Added " << activity[1] << " to numBeesOut" << std::endl;
        std::cout << "Num bees in: " << numBeesIn << std::endl;
        std::cout << "Num bees out: " << numBeesOut<< std::endl;

        //check if rob or swarm occured
        detectRob();
        detectSwarm();
    }
}

/**
 * @brief Alert::detectRob
 * Evaluates currentUDPMessage and determines if the message signals a rob occuring in the hive
 */
void Alert::detectRob()
{
    UDPMessageData mess(currentUDPMessage);
    HTime ht = mess.get_time();
    if(numBeesIn >= 1000){ //change 1000 to variable
        Rob r;
        if(!stopped) {
            r.showAlertWindow(currentUDPMessage);
            if(r.getStopped()) {
                stopped = true;
            }
            numBeesIn = 0;
            numBeesOut = 0;
        }
    }

}


/**
 * @brief Alert::detectSwarm
 * Evaluates currentUDPMessage and determines if the message signals a swarm occuring in the hive
 */
void Alert::detectSwarm()
{
    UDPMessageData mess(currentUDPMessage);
    HTime ht = mess.get_time();
    if(ht.get_hours() >= 12) {
        if(numBeesOut >= 1000) {
            Swarm s;
            if(!stopped){
                s.showAlertWindow(currentUDPMessage);
                if(s.getStopped()) {
                    stopped = true;
                }
                numBeesIn = 0;
                numBeesOut = 0;
            }
        }
    }
}
