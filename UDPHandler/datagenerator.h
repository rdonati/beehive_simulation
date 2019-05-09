#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H
#include <iostream>
#include <vector>

class DataGenerator
{
public:
    DataGenerator();
    std::string generateMessage();
    int tempH; //in fahrenheit
    int tempL;
    int month;
    int deathRateConstant;
    int errorConstant;

};

#endif // DATAGENERATOR_H
