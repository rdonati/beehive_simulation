#include "HTime.h"

/**
 * @brief HTime::HTime
 * @param h Hours (0-23)
 * @param m Minutes (0-59)
 * @param ms Milliseconds (0-59,999)
 */
HTime::HTime(int h, int m, int ms){
    hours = h;
    minutes = m;
    millis = ms;
}

/**
 * @brief HTime::set_hours Sets hours
 * @param h Hours (0-23)
 */
void HTime::set_hours(int h){
    hours = h;
}

/**
 * @brief HTime::set_minutes Sets minutes
 * @param m Minutes (0-59)
 */
void HTime::set_minutes(int m){
    minutes = m;
}

/**
 * @brief HTime::set_millis Sets milliseconds
 * @param ms Milliseconds (0-59,999)
 */
void HTime::set_millis(int ms){
    millis = ms;
}

/**
 * @brief HTime::get_minutes Gets minutes
 * @return Minutes (0-59)
 */
int HTime::get_minutes(){
    return minutes;
}

/**
 * @brief HTime::get_hours Gets hours
 * @return Hours (0-23)
 */
int HTime::get_hours(){
    return hours;
}

/**
 * @brief HTime::get_millis Gets milliseconds
 * @return Milliseconds (0-59,999)
 */
int HTime::get_millis(){
    return millis;
}

/**
 * @brief HTime::format Formats time as a readable string in format
 * @return String of the time in format (HH:MM:SS.MMM)
 */
std::string HTime::format(){
    std::string s = "";
    if(hours < 10){
        s.append("0");
    }
    if(hours == 0){
        s.append("0");
    }
    s.append(std::to_string(hours));
    s.append(":");
    if(minutes < 10){
        s.append("0");
    }
    s.append(std::to_string(minutes));
    s.append(":");
    int secs = ((millis - (millis % 1000)) / 1000);
    if(secs < 10){
        s.append("0");
    }
    s.append(std::to_string(secs));
    s.append(".");
    if(millis % 1000 < 100){
        s.append("0");
    }
    if(millis % 1000 < 10){
        s.append("0");
    }
    s.append(std::to_string(millis % 1000));
    return s;
}

/**
 * @brief HTime::compare_to Compares two times
 * @param t The time to compare it to
 * @return The difference between the two times in milliseconds
 */
long HTime::compare_to(HTime t){
    if(this->inMillis() < t.inMillis()){
        return (86400000 - this->inMillis()) + t.inMillis();
    }
    return this->inMillis() - t.inMillis();
}

long HTime::inMillis(){
    int total = 0;
    total += this->hours * 3600000;
    total += this->minutes * 60000;
    total += this->millis;

    return total;
}
