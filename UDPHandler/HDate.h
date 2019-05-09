#ifndef HDate_H
#define HDate_H

#include <iostream>
#include <vector>

class HDate
{
private:
    std::vector<std::string> months = {"January", "February", "March", "April",
                                       "May", "June", "July", "August",
                                       "September", "October", "November", "December"};
    int day;
    int month;
    int year;
public:
    /**
     * @brief HDate
     * @param d Day (1 - 31)
     * @param m Month (1 - 12)
     * @param y Year (after 2000)
     */
    HDate(int d = 0, int m = 0, int y = 0);

    /**
     * @brief format
     * @return A readable string of the date in format (MM DD, YYYY)
     */
    std::string format();


    //Getters/setters
    int get_day();
    int get_month();
    int get_year();
    void set_day(int d);
    void set_month(int m);
    void set_year(int y);
};

#endif // HDate_H

