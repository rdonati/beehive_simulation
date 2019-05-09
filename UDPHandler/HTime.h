#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <vector>

class HTime
{
private:
    int hours;
    int minutes;
    int millis;
public:

    /**
     * @brief HTime
     * @param h Hours (0-23)
     * @param m Minutes (0-59)
     * @param ms Milliseconds (0-59,999)
     */
    HTime(int h = 0, int m = 0, int ms = 0);


    /**
     * @brief HTime::compare_to Compares two times
     * @param t The time to compare it to
     * @return The difference between the two times in milliseconds
     */
    long compare_to(HTime t);

    /**
     * @brief inMillis Converts the time to milliseconds
     * @return The time in milliseconds
     */
    long inMillis();

    /**
     * @brief format Formats time as a readable string in format
     * @return String of the time in format (HH:MM:SS.MMM)
     */
    std::string format();

    //Getters/setters
    int get_hours();
    int get_minutes();
    int get_millis();
    void set_hours(int h);
    void set_minutes(int m);
    void set_millis(int ms);
};

#endif // TIME_H

