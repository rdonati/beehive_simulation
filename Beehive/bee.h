#ifndef BEE_H
#define BEE_H
#include <stdio.h>
#include <stdlib.h>     /*rand */
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>

class Bee
{
public:
     Bee();//constructor
    virtual ~Bee();//deconstructor
     Bee(int age);// create a bee with a given age
     void setAge(int x);// set the age of a bee
     void setFed(bool x);// set whether or not a bee was fed
     bool getFed();// get whether a bee was fed
     int getAge();// get age of bee
     bool getEN1();//get whether it made it into  sensor
     void setEN1(bool b);//set whether it made it into  sensor
     bool getEX2();//get whether it made it out of sensor
     void setEX2(bool b);//set whether it made it out of  sensor
     bool getEN2();//get whether it made it into  sensor
     void setEN2(bool b);//set whether it made it into  sensor
     bool getEx1();//get whether it made it out of  sensor
     void setEX1(bool b);//set whether it made it out of sensor


private:
    int Age = 0;// age
    bool IsFed = true;// whether a bee was fed

    // these are gates
    bool hasEnteredGate1 = false;
    bool hasEnteredGate2 = false;
    bool HasExitedGate1 = false;
    bool HasExitedGate2 = false;

};

#endif // BEE_H
