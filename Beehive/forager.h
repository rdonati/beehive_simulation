#ifndef FORAGER_H
#define FORAGER_H
#include "bee.h"
#include <string>
using namespace std;
class Forager: public Bee
{
public:
    Forager();// constructor
    ~Forager();// deconstructor

    bool getinit();// get if this is current state
    void setInit(bool b);//set state
    bool getFor();// get if this is current state
    void setFor(bool b);//set state
    bool getNest();// get if this is current state
    void setNest(bool b);//set state
    bool getSearch();// get if this is current state
    void setSearch(bool b);//set state
    bool getEx();// get if this is current state
    void setEX(bool b);//set state
    bool getTarget();// get if this is current state
    void setTarget(bool b);//set state
    bool getFull();// get if this is current state
    void setFull(bool b);//set state
    bool getDance();// get if this is current state
    void setDance(bool b);//set state
    bool getDanceB();// get if this is current state
    void setDanceB(bool b);//set state
    bool getEat();// get if this is current state
    void setEat(bool b);//set state
    bool getFoundFood();// get if this is current state
    void setFoundFood(bool b);//set state
    bool getTired();// get if this is current state
    void setTired(bool b);//set state
    int getSleep();// get if this is current state
    void setTime(int b);//set state
    int getTime();// get if this is current state
    void setSleep(int b);//set state

    bool getEnter();// get if this is current state
    void setEnter(bool b);//set state
    bool getExit();// get if this is current state
    void setExit(bool b);//set state



private:
    bool hasTarget = false;// does forager have a target
    bool isTired = false;// is bee tired
    bool foundFood = false;// has the bee found food
    bool isFull = true;// is the bee full
    bool dance = false;// is the bee dnacing
    bool beginDance = false;//state
    bool restOrEat= false;//state
    int timekeeper = 0;//keeps track of timings
    int sleep = 0;// how long has bee slept
    bool enterState = false;//state
    bool exitState = true;// state

    bool forageStep = false;//state
    bool initState = false;//state
    bool returnToNest = false;//state
    bool explore = false;//state
    bool searchForThing = false;//state

};

#endif // FORAGER_H
