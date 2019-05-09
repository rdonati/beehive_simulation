#ifndef BEEHIVE_H
#define BEEHIVE_H
#include <stdio.h>
#include <stdlib.h>     /*rand */
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include "queen.h"
#include "nurse.h"
#include "worker.h"
#include "juvinile.h"
#include "forager.h"
#include "drone.h"
#include "brood.h"
#include "bee.h"
#include "board.h"


#include <fstream>


using namespace std;

class Board;

class Beehive
{
public:

    Beehive(string ID,int forageNum, int NumOfBoard,int droneNum, double grow);//constructor
    Beehive(string ID);
    Beehive();
    ~Beehive(); //deconstructor

    void beeSimpleGrowth(double x);// function if you want simple bee growth
    int growthfunction(double x);// uses growth param x to see how many bees to make

    void randomSwarm();// reset and make new times for the swarms & attacks

    bool checkBoards();// check if there is something in the gates

    bool dance(Forager *f);// function for state of forager
    bool foundFood(Forager *f);// function for state of forager
    bool hasTarget(Forager *f);// function for state of forager
    bool isTired(Forager *f);// function for state of forager
    void beginDance(Forager *f);// function for state of forager
    void enterState(Forager *f);// function for state of forager
    void enterStates(Forager *f);// function for state of forager
    void exitState(Forager *f);// function for state of forager
    void exitStates(Forager *f);// function for state of forager
    void explore(Forager *f);// function for state of forager
    void forageStep(Forager *f);// function for state of forager
    void forageTech(Forager *f);// function for state of forager
    void restOrEat(Forager *f);// function for state of forager
    void returnToNest(Forager *f);// function for state of forager
        void searchForThing(Forager *f);// function for state of forager

    string boardString();// string for udp message
    string parseTime(int t);// time for udp message


    void OneDayTimeStep();// one day
    void OneHourTimeStep();// one hour
    void OneMillisecondTimeStep();// one millisecond
    void OneMinuteTimeStep();// one minute
    void OneMonthTimeStep();// one month
    void OneSecondTimeStep();// one second
    void OneWeekTimeStep();// one weed
    void OneYearTimeStep();// one year

    void SwarmTech(Bee *b);// make a bee swarm
    void attackTech(Bee *b);// make a bee attack


    void birthBees();// make new brood
    void evolveBees();// make bees grow up
    void fertilizeEggs();// decide gender of bees
    void foodCalculation();// feed all the bees
    void killBees();// kill old bees
    void nurseBees();// nurse young brood

    void run();// run simulation
    void run(string ID);



    void setNumOfBoards(int x);//set number of boards
    void setSeason(int x);// set season
    void setStartingValues();// set the starting values
    void setWeather(double s);//set temperature
    void setYearsToRun(int x);// set # of years to run
    void setup();// set up simulation


    void updateBoards();// update the boards
    void workerTech(Worker w);// do things with the workers
    bool divide10();// random number 1-10

private:
    double printOut=0;// current day (print out % done)
    bool initrun=true;// sets if its the first day or not(it corrects number of bees on first day)
    Queen q;// make a queen to birth bees
    int droneNum;// number of drones to swarm/ attack
    double growthP;// simple growth %
    int forNum;// number of foragers to start with
    int randNumGen;// random number gen
    bool Attack = true;// is there an attack
    bool domilli = true;// do millisecond simulation
    bool swarm = true;// is there a swarm
    double foodAmount= 1000000;//food in hive in grams
    double pollenAmmount = 1000000;//pollen in hive in grams
    double pollenGen = 100;// init values
    double pollenUsed = 20;// init values
    double temperature = 70;// starting temperature
    int AttackTime = 43200;// rob time(init at noon)
    int BeeCounter=0;// number of bee enters into hive today
    int BeeCounter2=0;// number of bee enters total
    int TOD;// current time today
    int boardcycle = 0;// cycle through boards to even it out
    int changenow;// idk what this does but its important(I think it helps boardcycle)
    int currentTime = 0;// current sim time
    int exitCounter=0;// number of exits today
     int exitCounter2=0;// num of exits total
    int milliCounter=0;// number of milliseconds this second
    int numOfBoards = 10;// number of boards
    int season = 1;// season
    int swarmTime = 64800;// swarm time (init at 6:00pm)

    int timeSinceMessage=0;// time since last udp in milliseconds
    int atkC = 0;// # of attacking bees today
    int SWRMC = 0;// num of swarming bees today
    int atkC2 = 0;// tot num of attacking bees
    int SWRMC2 = 0;//tot num of swarming bees

    string hiveID = "testID";// id of hive
    int numofyears = 1;// num of years to run

    vector<Board> boardVect;// vector of boards
    vector<Brood> broodVect;// brood vector
    vector<Drone> droneVect;//drone vector
    vector<Forager> forageVect;//forager vector
    vector<Juvinile> juviVect;// juvinile vector
    vector<Nurse> nurseVect;// nurse vector
    vector<Worker> workerVect;// worker vector

    ofstream myfile;// file reader



};

#endif // BEEHIVE_H
