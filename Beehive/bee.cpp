#include "bee.h"

Bee::Bee(){}

//make a bee with a given age
Bee::Bee(int a)
{
Age = a;
}

Bee::~Bee(){}

//getters & setters
void Bee::setAge(int x){
    Age = x;
}
void Bee::setFed(bool x){
    IsFed = x;
}
bool Bee::getFed(){
    return IsFed;
}
int Bee::getAge(){
    return Age;
}

bool Bee::getEN1(){
    return hasEnteredGate1;
}
void Bee::setEN1(bool b){
    hasEnteredGate1 = b;
}
bool Bee::getEX2(){
    return HasExitedGate2;
}
void Bee::setEX2(bool b){
    HasExitedGate2 =b;
}

bool Bee::getEN2(){
        return  hasEnteredGate2;
}
void Bee::setEN2(bool b){
    hasEnteredGate2 = b;
}
bool Bee::getEx1(){
    return HasExitedGate1;
}
void Bee::setEX1(bool b){
    HasExitedGate1 = b;
}
