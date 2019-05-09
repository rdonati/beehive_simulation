#include "HDate.h"

/**
 * @brief HDate::HDate
 * @param d Day (1 - 31)
 * @param m Month (1 - 12)
 * @param y Year (after 2000)
 */
HDate::HDate(int d, int m, int y){
    day = d;
    month = m;
    year = y;
}

/**
 * @brief HDate::set_day Sets the day
 * @param d Day (1 - 31)
 */
void HDate::set_day(int d){
    day = d;
}

/**
 * @brief HDate::set_month Sets the month
 * @param m Month (1 - 12)
 */
void HDate::set_month(int m){
    month = m;
}

/**
 * @brief HDate::set_year Sets the year
 * @param y Year (since 2000)
 */
void HDate::set_year(int y){
    year = y;
}

/**
 * @brief HDate::get_month Gets the month
 * @return Month (1-12)
 */
int HDate::get_month(){
    return day;
}

/**
 * @brief HDate::get_day Gets the day
 * @return Day (1-31)
 */
int HDate::get_day(){
    return month;
}

/**
 * @brief HDate::get_year Gets the year
 * @return Year (since 2000)
 */
int HDate::get_year(){
    return year;
}

/**
 * @brief HDate::format
 * @return A readable string of the date in format (MM DD, YYYY)
 */
std::string HDate::format(){
    std::string s = "";
    s.append(months[month - 1]);
    s.append(" ");
    s.append(std::to_string(day));
    s.append(", 20");
    s.append(std::to_string(year));
    return s;
}
