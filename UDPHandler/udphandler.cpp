#include "udphandler.h"

UDPHandler::UDPHandler(){

}

void UDPHandler::read_UDP(std::string message){
    try{
        UDPMessage = message;
        hiveID = message.substr(0, message.find('-'));
        message = message.substr(message.find('-') + 2);
        dateString = message.substr(0, message.find('T'));
        message = message.substr(message.find('T') + 1);
        timeString = message.substr(0, message.find('-'));
        message = message.substr(message.find('-') + 1);
        gateString = message;
    }catch(std::exception e){
        std::cerr << "Invalid UDP message passed to UDPHandler" << std::endl;
    }
}

HDate UDPHandler::get_date(){
    HDate d;
    if(dateString.size() == 0){
        std::cerr << "Tried to read date when it does not exist" << std::endl;
    }else{
        d.set_day(std::stoi(dateString.substr(0, dateString.find('.'))));
        std::string temp = dateString.substr(dateString.find('.') + 1);
        d.set_month(std::stoi(temp.substr(0, dateString.find('.'))));
        temp = temp.substr(dateString.find('.') + 1);
        d.set_year(std::stoi(temp));
    }
    return d;
}

HTime UDPHandler::get_time(){
    HTime t;
    if(timeString.size() == 0){
        std::cerr << "Tried to read time when it does not exist" << std::endl;
    }else{
        t.set_hours(std::stoi(timeString.substr(0, timeString.find('.'))));
        std::string temp = timeString.substr(timeString.find('.') + 1);
        t.set_minutes(std::stoi(temp.substr(0, timeString.find('.'))));
        temp = temp.substr(temp.find('.') + 1);
        t.set_millis(std::stoi(temp));
    }
    return t;
}

std::vector<HBoard> UDPHandler::get_boards(){
    std::vector<HBoard> bs;
    std::string temp = gateString;
    int numOfGates = std::count(temp.begin(), temp.end(), 'B');

    for(int i = 0; i < (numOfGates - 1); i++){
        HBoard tempBoard;
        temp = temp.substr(1);
        std::vector<bool> sensors = decode_gates(temp.substr(0, temp.find('B')));
        tempBoard.set_sensors(sensors);
        temp = temp.substr(temp.find('B'));
        bs.push_back(tempBoard);
    }
    HBoard b;
    temp = temp.substr(1);
    b.set_sensors(decode_gates(temp));
    bs.push_back(b);
    return bs;
}

std::vector<bool> UDPHandler::decode_gates(std::string s){
    std::vector<bool> temp;
    int asInt = std::stoi(s);
    while (asInt > 0) //converts decimal to binary
        {
            temp.push_back(asInt % 2);
            asInt /= 2;
        }
    while(temp.size() < 8){
        temp.push_back(0);
    }
    return temp;
}

std::string UDPHandler::get_hiveID(){
    return hiveID;
}

std::string UDPHandler::encode_boards(std::vector<std::vector<bool>> gs){
    std::string data;
    for(int i = 0; i < gs.size(); i++){
        data += "B";
        data += encode_gates(gs[i]);
    }
    return data;
}

std::string UDPHandler::encode_gates(std::vector<bool> g){
    int n = 0;
    for(int i = 0; i < g.size(); i++){
        if(g[i]){
            n += pow(2.0, g.size() - (i + 1));
        }
    }
    return std::to_string(n);
}

std::string UDPHandler::get_message(){
    if(UDPMessage != ""){
        return UDPMessage;
    }else{
        std::cerr << "Requested message when there is no message";
        return "";
    }
}

std::string UDPHandler::create_message(std::string hID, HDate d, HTime t, std::vector<std::vector<bool>> gs){
    std::string m = "";
    m += hID;
    m += "-D";
    if(d.get_day() < 10) m += "0";
    m += std::to_string(d.get_day());
    m += ".";
    if(d.get_month() < 10) m += "0";
    m += std::to_string(d.get_month());
    m += ".";
    m += std::to_string(d.get_year());
    m += "T";
    if(t.get_hours() < 10) m += "0";
    m += std::to_string(t.get_hours());
    if(t.get_minutes() < 10) m += "0";
    m += std::to_string(t.get_minutes());
    if(t.get_millis() < 1000) m += "0";
    if(t.get_millis() < 100) m += "0";
    if(t.get_millis() < 10) m += "0";
    m += std::to_string(t.get_millis());
    m += "-";
    m += encode_boards(gs);
    return m;
}
