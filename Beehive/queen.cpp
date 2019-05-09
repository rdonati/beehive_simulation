#include "queen.h"

Queen::Queen(){}
Queen::~Queen(){}

//set how many brood the queen wants to make today
void Queen::BirthEggs(int season,double pollenGen,double pollenUsed){
    std::poisson_distribution<int> distribution(714);
    double x;
    if(1<(pollenGen/(pollenUsed+50.25))*lookup(season)){
        x=distribution(generator);
    }
    else {
        x=distribution(generator)*(pollenGen/(pollenUsed+50.25))*lookup(season);
    }
    setEgg(round(x/2));

}

// looks up the ratio for birthing new bees depending on the season
double Queen::lookup(int x){
    if(x==1){
        return .5;
    }
    else if (x==2) {
        return .4;
    }
    else if (x==3) {
        return .3;
    }
    else if (x==4) {
        return .2;
    }
    else if (x==5) {
        return .4;
    }
    else if (x==6) {
        return .8;
    }
    else if (x==7) {
        return .9;
    }
    else if (x==8) {
        return .9;
    }
    else if (x==9) {
        return .7;
    }
    else if (x==10) {
        return .6;
    }
    else if (x==11) {
        return .6;
    }
    else {
        return .5;
    }
}


// some getters and setters
void Queen::setAge(int x){
    Age = x;
}
void Queen::setFed(bool x){
    isFed =x;
}
bool Queen::getFed(){
    return isFed;
}
int Queen::getAge(){
    return Age;
}
void Queen::setEgg(int x){
    eggsMadeToday = x;
}
int Queen::getEgg(){
    return eggsMadeToday;
}

void Queen::setSeason(int x){
    season =x;
}
double Queen::getRatio(){
    return ratioFert;
}
int Queen::getSeason(){
    return season;
}

