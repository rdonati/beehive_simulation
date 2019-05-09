#include "forager.h"

Forager::Forager(){}
Forager::~Forager(){}


// many getters & setters for all the variables
bool Forager::getinit(){
    return initState;
}
void Forager::setInit(bool b){
    initState = b;
}
bool Forager::getFor(){
    return forageStep;
}
void Forager::setFor(bool b){
    forageStep = b;
}
bool Forager::getNest(){
   return returnToNest;
}
void Forager::setNest(bool b){
    returnToNest = b;
}
bool Forager::getSearch(){
    return searchForThing;
}
void Forager::setSearch(bool b){
    searchForThing = b;
}
bool Forager::getEx(){
    return explore;
}
void Forager::setEX(bool b){
    explore = b;
}

bool Forager::getTarget(){
    return hasTarget;
}
void Forager::setTarget(bool b){
    hasTarget = b;
}
bool Forager::getFull(){
    return isFull;
}
void Forager::setFull(bool b){
    isFull = b;
}
bool Forager::getDance(){
    return dance;
}
void Forager::setDance(bool b){
    dance = b;
}
bool Forager::getDanceB(){
    return beginDance;
}
void Forager::setDanceB(bool b){
    beginDance = b;
}
bool Forager::getEat(){
    return restOrEat;
}
void Forager::setEat(bool b){
    restOrEat = b;
}
bool Forager::getFoundFood(){
    return foundFood;
}
void Forager::setFoundFood(bool b){
    foundFood = b;
}
bool Forager::getTired(){
    return isTired;
}
void Forager::setTired(bool b){
    isTired = b;
}
int Forager::getSleep(){
    return sleep;
}
void Forager::setTime(int b){
    timekeeper =b;
}
int Forager::getTime(){
    return timekeeper;
}
void Forager::setSleep(int b){
    sleep = b;
}

bool Forager::getEnter(){
    return enterState;
}
void Forager::setEnter(bool b){
    enterState = b;
}
bool Forager::getExit(){
    return exitState;
}
void Forager::setExit(bool b){
    exitState = b;
}
