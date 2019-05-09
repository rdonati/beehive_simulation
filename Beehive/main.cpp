#include <iostream>
#include "beehive.h"
using namespace std;

int main()
{

    Beehive b; // make a beehive

    //Beehive b("testID",1000/* num of bees*/,10/* num of boards*/,10000/*swarm/attack number*/,.05/*growth function*/);

      b.run("example");    //run simulation

}
