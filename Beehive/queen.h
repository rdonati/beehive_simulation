#ifndef QUEEN_H
#define QUEEN_H
#include <stdio.h>
#include <stdlib.h>     /*rand */
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <random>
#include <algorithm>
using namespace std;

class Queen
{
public:
    Queen();//constructor
    ~Queen();// deconstructor
    void BirthEggs(int season,double pollenGen,double pollenUsed);// make new brood

    void setAge(int x);// set age of queen
    void setFed(bool x);// set if queen is fed
    bool getFed();// get if queen is fed
    int getAge();// get age of queen

    void setSeason(int x);// set season
    double getRatio();// get ratio
    int getSeason();// get season
    void setEgg(int x);// set egg
    int getEgg();// get egg
    double lookup(int season);// lookup ratio depending on season
private:
    std::default_random_engine generator;// random gen

    int Age;// age of queen
    int eggsMadeToday;// eggs made today
    bool isFed;// is the queen fed
    int season;// current season
    double ratioFert;// ratio for fertility
};

#endif // QUEEN_H
