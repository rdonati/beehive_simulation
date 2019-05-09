#include "rob.h"
#include "swarm.h"
#include "alert.h"
#include <QApplication>
#include <fstream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

//    Rob r;
//    r.showAlertWindow("HC0002-D19.12.19T13.43.16285-B0B1B16B0B0B0B0B0B0B12");

//    Swarm s("HC0002-D21.12.20T13.43.16985-B33B0B0B0B0B0B0B0B0B0");
//    s.showAlertWindow();


    Alert al;
//    al.addUDPMessage("HC0002-D19.12.19T13.43.16285-B0B1B16B0B0B0B0B0B0B12");
//    al.addUDPMessage("HC0002-D21.12.20T13.43.16985-B33B0B0B0B0B0B0B0B0B0");

    //Absolute path version
//    std::fstream file;
//    file.open("/Users/ricdonati/desktop/build-repo_donatir_dorwardc_markaris_trezzas-Desktop_Qt_5_12_0_clang_64bit-Debug/AlertSystem/example.txt"); //read from file

   /*For Others */
    std::fstream file("example.txt");

    std::string first;

        getline(file, first);
        al.da = new DataAnalyzer(new UDPMessageData(first)); //makes new data analyzer for first line
    getline(file, first);
    al.da = new DataAnalyzer(new UDPMessageData(first)); //makes new data analyzer for first line
    for(std::string line; getline(file, line);){ //read every other line
           al.addUDPMessage(line); //adds every udp message

    }

    return a.exec();

//    std::fstream inFile("/Users/ricdonati/desktop/build-repo_donatir_dorwardc_markaris_trezzas-Desktop_Qt_5_12_0_clang_64bit-Debug/AlertSystem/dummy.txt");
//    if(inFile.is_open()){
//        std::cout << "yes";
//    }
//    else{
//        std::cout << "no";
//    }
}
