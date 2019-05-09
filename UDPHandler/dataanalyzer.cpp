#include "dataanalyzer.h"

DataAnalyzer::DataAnalyzer(UDPMessageData * m)
{
        numOfGates = m->get_boards().at(0).get_sensors().size();
        numOfBoards = m->get_boards().size();
        messages.push_back(m);
        reset();
}

DataAnalyzer::DataAnalyzer(std::string f)
{
        reset();
        std::ifstream file(f);
        for(std::string line; getline(file, line);){
            UDPMessageData *temp = new UDPMessageData(line);
            messages.push_back(temp);
        }
        numOfGates = messages[0]->get_boards()[0].get_sensors().size();
        numOfBoards = messages[0]->get_boards().size();
}

/**
 * @brief DataAnalyzer::analyze Analyzes a group of UDP messages
 * @return Returns an array where indices 0, 1, and 2 corrospond to bees in, bees out, and exceptions respectively
 */
std::vector<int> DataAnalyzer::analyze(){

    //Initializes vector to track bees in, bees out, and exceptions
    std::vector<int> activity;
    activity.assign(3, 0);

    reset();

    //analyzes runs analysis on each message
    for(int m = 0; m < messages.size(); m++){
        printState();
        std::vector<int> results = updateState(messages[m]);
        activity.at(0) += results.at(0);
        activity.at(1) += results.at(1);
        activity.at(2) += results.at(2);
    }
    return activity;
}

int DataAnalyzer::gateToPath(int n){
    if(n < numOfGates / 2){
        return n;
    }else{
        return(((numOfGates / 2) - 1) - (n % (numOfGates / 2)));
    }
}

std::vector<int> DataAnalyzer::updateState(UDPMessageData *m){

    numOfGates = m->get_boards()[0].get_sensors().size();
    numOfBoards = m->get_boards().size();

    printState();
    printMessage(m);

    //Initializes vector to track bees in, bees out, and exceptions
    std::vector<int> activity;
    activity.assign(3, 0);

    //Initializes states for the current UDP message
    //  0 = no activity
    //  1 = going out
    //  2 = going in
    //  3 = both gates triggered
    std::vector<std::vector<int>> states;
    std::vector<int> empty;
    empty.assign(numOfGates / 2, 0);
    states.assign(numOfBoards, empty);

    //Processes inside sensors
    for(int b = 0; b < numOfBoards; b++){
        for(int g = 0; g < (numOfGates / 2); g++){
            if(m->get_boards()[b].get_sensors()[g] == true){
                states[b][gateToPath(g)] = 1;
                //If more than 5 seconds have passed since the path was last interacted with, the path resets its state
                if(m->get_time().compare_to(pathLastActivity[b][gateToPath(g)]) > 5000){
                    pathStatuses[b][gateToPath(g)] = 0;
                    activity.at(2) += 1;
                }
                //Updates most recent message relevant to this path
                pathLastActivity[b][gateToPath(g)] = m->get_time();
            }
        }
    }

    //processes outside sensors
    for(int b = 0; b < numOfBoards; b++){
        for(int g = numOfGates / 2; g < numOfGates; g++){
            if(m->get_boards()[b].get_sensors()[g] == true){
                if(states[b][gateToPath(g)] == 1){
                    states[b][gateToPath(g)] = 3;
                }else{
                    states[b][gateToPath(g)] = 2;
                }
                //If more than 5 seconds have passed since the path was last interacted with, the path resets its state
                if(m->get_time().compare_to(pathLastActivity[b][gateToPath(g)]) > 5000){
                    pathStatuses[b][gateToPath(g)] = 0;
                    activity.at(2) += 1;
                }
                //Updates most recent message relevant to this path
                pathLastActivity[b][gateToPath(g)] = m->get_time();
            }
        }
    }

    //Compares state of hive during message to the previous hive state
    for(int b = 0; b < numOfBoards; b++){
        for(int g = 0; g < numOfGates / 2; g++){
            if(states[b][gateToPath(g)] == 1){
                if(pathStatuses[b][gateToPath(g)] == 0){
                    pathStatuses[b][gateToPath(g)] = 1;
                }else if(pathStatuses[b][gateToPath(g)] == 1){
                    pathStatuses[b][gateToPath(g)] = 1;
                }else{
                    pathStatuses[b][gateToPath(g)] = 0;
                    std::cout << "Bee enters hive at time: " << m->get_time().format() << std::endl;
                    activity.at(0) += 1;
                }
            }else if(states[b][gateToPath(g)] == 2){
                if(pathStatuses[b][gateToPath(g)] == 0){
                    pathStatuses[b][gateToPath(g)] = 2;
                }else if(pathStatuses[b][gateToPath(g)] == 1){
                    pathStatuses[b][gateToPath(g)] = 0;
                    std::cout << "Bee exits hive at time: " << m->get_time().format() << std::endl;
                    activity.at(1) += 1;
                }else{
                    pathStatuses[b][gateToPath(g)] = 2;
                }
            }else if(states[b][gateToPath(g)] == 3){
                if(pathStatuses[b][gateToPath(g)] == 0){
                    pathStatuses[b][gateToPath(g)] = 1;
                    std::cout << "Bee exits hive at time: " << m->get_time().format() << std::endl;
                    activity.at(1) += 1;
                }else if(pathStatuses[b][gateToPath(g)] == 1){
                    pathStatuses[b][gateToPath(g)] = 1;
                    std::cout << "Bee exits hive at time: " << m->get_time().format() << std::endl;
                    activity.at(1) += 1;
                }else{
                    pathStatuses[b][gateToPath(g)] = 2;
                    std::cout << "Bee enters hive at time: " << m->get_time().format() << std::endl;
                    activity.at(0) += 1;
                }
            }
        }
    }


    return activity;
}

void DataAnalyzer::printData(){
    std::cout << "Boards: " << numOfBoards << std::endl << "Gates: " << numOfGates << std::endl;
    std::cout << "--Gate Activity--" << std::endl << std::endl;

    for(int m = 0; m < messages.size(); m++){
        //loops through first half of sensors
        printMessage(messages[m]);
        std::cout << std::endl << std::endl;
    }
}

void DataAnalyzer::printState(){
    for(int i = 0; i < pathStatuses.size(); i++){
        for(int j = 0; j < pathStatuses[i].size(); j++){
            std::cout << std::to_string(pathStatuses[i][j]);
        }
        std::cout << "  ";
    }
    std::cout << std::endl;
}

void DataAnalyzer::printMessage(UDPMessageData *m){
    for(int b = 0; b < numOfBoards; b++){
        std::string s = "";
        for(int g = 0; g < (numOfGates / 2); g++){
            if(m->get_boards()[b].get_sensors()[g] == false){
                s += "-";
            }else{
                s += "B";
            }
        }
        std::cout << s << "  ";
    }
    std::cout << m->get_time().format() << std::endl;
    //loops through second half of sensors
    for(int b = 0; b < numOfBoards; b++){
        std::string s = "";
        for(int g = numOfGates / 2; g < numOfGates; g++){
            if(m->get_boards()[b].get_sensors()[g] == false){
                s += "-";
            }else{
                s += "B";
            }
        }
        //Flips s, so that output makes sense
        std::string newS = "";
        for(int temp = 0; temp < s.size(); temp++){
            newS += s.at(s.size() - temp - 1);
        }
        std::cout << newS << "  ";
    }
    std::cout << std::endl;
}

std::vector<int> DataAnalyzer::analyzeComprehensive(){

    //Initializes vector to track bees in, bees out, and exceptions
    std::vector<int> activity;
    activity.assign(3, 0);

    //prints path state keys
    std::cout << std::endl << std::endl <<
                 "Path State Keys:" << std::endl << std::endl <<
                 "0 = Dormant (no bee activity)" << std::endl <<
                 "1 = Going out (bee has gone from the inside of the hive into the path)" << std::endl <<
                 "2 = Going in (bee has gone from the outside of the hive into the path)" << std::endl << std::endl << std::endl;

    reset();

    for(int m = 0; m < messages.size(); m++){
        printState();
        printMessage(messages[m]);
        std::vector<int> results = updateState(messages[m]);
        activity.at(0) += results.at(0);
        activity.at(1) += results.at(1);
        activity.at(2) += results.at(2);
        std::cout << std::endl;
    }
    return activity;
}

void DataAnalyzer::reset(){
    //initializes gate path statuses
    for(int i = 0; i < numOfBoards; i++){
        std::vector<int> temp;
        for(int z = 0; z < numOfGates / 2; z++){
            temp.push_back(0);
        }
        pathStatuses.push_back(temp);
    }
    //initializes paths' last activity
    for(int i = 0; i < numOfBoards; i++){
        std::vector<HTime> temp;
        for(int z = 0; z < numOfGates / 2; z++){
            temp.push_back(messages[0]->get_time());
        }
        pathLastActivity.push_back(temp);
    }
}
