#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

class HBoard
{
private:
    std::vector<bool> sensors;
public:
    /**
     * @brief HBoard Creates a new HBoard object
     */
    HBoard();

    /**
     * @brief HBoard Creates a new HBoard object
     * @param s A vector of booleans (representing sensors)
     */
    HBoard(std::vector<bool> s);

    // Getter/setter
    void set_sensors(std::vector<bool> s);
    std::vector<bool> get_sensors();
};

#endif // BOARD_H

