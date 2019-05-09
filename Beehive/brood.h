#ifndef BROOD_H
#define BROOD_H
#include "bee.h"

class Brood : public Bee
{
public:
    Brood();// constructor
    ~Brood();//deconstructor

    void setFert(bool x);// set if fertilized
    bool getFert();// get if fertilized

private:
   bool Fertilized;//true is yes false is no



};

#endif // BROOD_H
