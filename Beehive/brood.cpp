#include "brood.h"

Brood::Brood(){}
Brood::~Brood(){}

//getter & setter
void Brood::setFert(bool x){
    Fertilized=x;
}

bool Brood::getFert(){
    return Fertilized;
}

