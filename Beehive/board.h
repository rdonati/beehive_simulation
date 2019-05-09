#ifndef BOARD_H
#define BOARD_H

#include "bee.h"
#include <vector>
#include "forager.h"
#include <random>

using namespace std;
class Board
{
public:

    Board(); //constructor

    void updateline(int x);// update the gates
    void addToLine(Bee *b);// add to queue to exit
    void addToEnterLine(Bee *b);// add to queue to enter
    int calculateBool();// calculate the int for the udp message
    int toTwoInt(int x);// changes binary to int
    void reset();// reset some variables
    int checkBoards();// check status of boards;

    void Traverse();// lets bees exit hive
    void Inverse();// lets bees enter hive
    void Iterate();// moves bees foward
    void InverseIterate();//moves bees backwards

    void swapping();// changes direction if conditions met
    void checkSwap();// check if ok to change direction

    bool checkFinT();// check if bees are finished exiting
    bool checkFinI();//check if bees are finished entering





private:
    vector<Bee*> line;// queue to exit
    vector<Bee*> Enterline;// queue to enter

    int condition = 0;// //thing to help change direciton
    bool enterNew = true;// can new bees enter the gate
    bool changedstates[8];// states of gates

    Bee* inner[4];// inner gates
    Bee* middle[4];// middle space between gates
    Bee* outer[4];// outer gates

    int gateCycle =0;// cycle through gates
    int timeSinceUpdate = 0;// time since send message
    int cycle =0;// help gate cycle
    bool FrontBack = false;// direction

};

#endif // BOARD_H
