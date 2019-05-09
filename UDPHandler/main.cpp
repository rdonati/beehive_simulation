#include <iostream>
#include "HDate.h"
#include "HTime.h"
#include "HBoard.h"
#include "realtimesimulator.h"
#include "udpmessagedata.h"
#include "dataanalyzer.h"
#include <vector>

using namespace std;

int main()
{
    UDPMessageData test("testID-D1.1.2019T6.0.1000-B15B15B15B15B15B15B15B15B15B15");
    std::vector<int> temp = test.musicify();

    for(int i = 0; i < temp.size(); i++){
        std::cout << (i + 1) << ": " << temp[i] << std::endl;
    }

}
