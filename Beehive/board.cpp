#include "board.h"

// initialize board variables
Board::Board(){
    // initialize gates
    inner[0]= nullptr;
    inner[1]= nullptr;
    inner[2]= nullptr;
    inner[3]= nullptr;
    outer[1]= nullptr;
    outer[2]= nullptr;
    outer[3]= nullptr;
    outer[0]= nullptr;
    middle[0]= nullptr;
    middle[1]= nullptr;
    middle[2]= nullptr;
    middle[3]= nullptr;

    // set all states to false
    changedstates[0]=false;
    changedstates[2]=false;
    changedstates[1]=false;
    changedstates[3]=false;
    changedstates[4]=false;
    changedstates[5]=false;
    changedstates[6]=false;
    changedstates[7]=false;
}

// calculate the number to be used in the udp string
int Board::calculateBool(){
    int x =0;
    if(inner[0] != nullptr&&changedstates[0]){x+=1;}
    if(inner[1] != nullptr&&changedstates[1]){x+=10;}
    if(inner[2] !=nullptr&&changedstates[2]){x+=100;}
    if(inner[3] !=nullptr&&changedstates[3]){x+=1000;}
    if(outer[3] !=nullptr&&changedstates[7]){x+=10000;}
    if(outer[2] !=nullptr&&changedstates[6]){x+=100000;}
    if(outer[1] !=nullptr&&changedstates[5]){x+=1000000;}
    if(outer[0] !=nullptr&&changedstates[4]){x+=10000000;}

    string s = to_string(x);
    int test = std::stoi(s, nullptr, 2);

    return test;
}




// change direction of the bees
void Board::swapping(){

    FrontBack = !FrontBack;

}

// checks how many bees are in the gates
int Board::checkBoards(){
    int x =0;
    if(changedstates[0]==true){
        x++;
    }
    if(changedstates[1]==true){
        x++;
    }
    if(changedstates[2]==true){
        x++;
    }
    if(changedstates[3]==true){
        x++;
    }
    if(changedstates[4]==true){
        x++;
    }
    if(changedstates[5]==true){
        x++;
    }
    if(changedstates[6]==true){
        x++;
    }
    if(changedstates[7]==true){
        x++;
    }
    return x;

}

// checks if the gates are empty
bool Board::checkFinI(){
    bool x = true;
    for (int var = 0; var < 4; ++var) {
        if(inner[var]!=nullptr){
            x=false;
        }
        if(outer[var]!=nullptr){
            x=false;
        }
        if(middle[var]!=nullptr){
            x=false;
        }
    }
    return x;
}

// checks if the program should change directions
void Board::checkSwap(){
    int randNum = (rand() % 10) + 1;
    if(condition >=randNum &&checkFinI()){
        condition = 0;
        swapping();
    }
    if(condition >=(randNum-1)){
        enterNew = false;
        if(FrontBack){
            if(Enterline.size() == 0){
                enterNew = true;
            }

        }
        else if(!FrontBack) {
            if(line.size() ==0){
                enterNew=true;
            }
        }
    }
    else {
        enterNew = true;
    }
}


// updates the bees moving through the gates
void Board::updateline(int x){
    reset();
    if(((FrontBack)||(line.size()!=0&&Enterline.size()==0))&&(x>=21600&&x<=72000)){

        if(line.size()!=0&&Enterline.size()==0){
            FrontBack = true;
        }
        Traverse();

        condition++;
    }
    else{
        Inverse();
        condition++;
    }

    checkSwap();
}

//reset the variables in the gate
void Board::reset(){
    for(int i=0;i<8;i++){
        changedstates[i]=false;
    }

}


// put a bee in the first gate(for exiting bees)
void Board::Traverse(){

    Iterate();
    for (int i=0;i<4;i++) {


        if((enterNew)&&line.size()!=0){
            if(inner[gateCycle]!=nullptr){
            }
            inner[gateCycle]=line.at(0);

            inner[gateCycle]->setEN1(true);
            line.erase(line.begin());
            changedstates[gateCycle] = true;

            gateCycle++;
            if(gateCycle>=4){
                gateCycle=0;
            }
        }
    }


}
// put a bee in the first gate(for entering bees)
void Board::Inverse(){

    InverseIterate();

    for (int i=0;i<4;i++) {
        if((enterNew )&&Enterline.size()!=0){
            if(outer[gateCycle]!=nullptr){
            }
            outer[gateCycle]=Enterline.at(0);

            outer[gateCycle]->setEN2(true);
            Enterline.erase(Enterline.begin());
            changedstates[gateCycle+4] = true;
            gateCycle++;
            if(gateCycle>=4){
                gateCycle=0;
            }
        }
    }
}

//update other steps of the gates(for exiting bees)
void Board::Iterate(){


    if(outer[0]!=nullptr){
        outer[0]->setEX2(true);
        changedstates[4] = true;
        outer[0]=nullptr;
    }


    if(outer[1]!=nullptr){
        outer[1]->setEX2(true);
        changedstates[5] = true;
        outer[1]=nullptr;
    }


    if(outer[2]!=nullptr){
        outer[2]->setEX2(true);
        changedstates[6] = true;
        outer[2]=nullptr;
    }


    if(outer[3]!=nullptr){
        outer[3]->setEX2(true);
        changedstates[7]= true;
        outer[3]=nullptr;
    }


    if(inner[0]!=nullptr){
        middle[0] = inner[0];
        changedstates[0] = true;
        inner[0]->setEX1(true);
        inner[0]=nullptr;
    }

    if(inner[1]!=nullptr){

        middle[1] = inner[1];
        changedstates[1] = true;
        inner[1]->setEX1(true);
        inner[1]=nullptr;
    }

    if(inner[2]!=nullptr){

        middle[2] = inner[2];
        changedstates[2] = true;
        inner[2]->setEX1(true);
        inner[2]=nullptr;
    }

    if(inner[3]!=nullptr){

        middle[3] = inner[3];
        changedstates[3] = true;
        inner[3]->setEX1(true);
        inner[3]=nullptr;
    }

    if(middle[0]!=nullptr){
        middle[0]->setEN2(true);
        changedstates[4] = true;
        outer[0] = middle[0];
        middle[0]=nullptr;
    }

    if(middle[1]!=nullptr){
        middle[1]->setEN2(true);
        changedstates[5] = true;
        outer[1] = middle[1];
        middle[1]=nullptr;
    }

    if(middle[2]!=nullptr){
        middle[2]->setEN2(true);
        changedstates[6] = true;
        outer[2] = middle[2];
        middle[2]=nullptr;
    }

    if(middle[3]!=nullptr){
        middle[3]->setEN2(true);
        changedstates[7] = true;
        outer[3] = middle[3];
        middle[3]=nullptr;
    }



}

//update other parts of the gates(for entering bees)
void Board::InverseIterate(){

    if(inner[0]!=nullptr){
        changedstates[0] = true;
        inner[0]->setEX1(true);
        inner[0]=nullptr;
    }

    if(inner[1]!=nullptr){

        changedstates[1] = true;
        inner[1]->setEX1(true);
        inner[1]=nullptr;
    }

    if(inner[2]!=nullptr){
        changedstates[2] = true;
        inner[2]->setEX1(true);
        inner[2]=nullptr;
    }

    if(inner[3]!=nullptr){
        changedstates[3] = true;
        inner[3]->setEX1(true);
        inner[3]=nullptr;
    }



    if(outer[0]!=nullptr){
        changedstates[4] = true;
        middle[0] = outer[0];
        outer[0]->setEX2(true);
        outer[0]=nullptr;
    }

    if(outer[1]!=nullptr){
        middle[1] = outer[1];
        changedstates[5] = true;
        outer[1]->setEX2(true);
        outer[1]=nullptr;
    }

    if(outer[2]!=nullptr){
        changedstates[6] = true;
        middle[2] = outer[2];
        outer[2]->setEX2(true);
        outer[2]=nullptr;
    }

    if(outer[3]!=nullptr){
        changedstates[7] = true;
        middle[3] = outer[3];
        outer[3]->setEX2(true);
        outer[3]=nullptr;
    }

    if(middle[0]!=nullptr){

        changedstates[0] = true;
        inner[0] = middle[0];
        middle[0]->setEN1(true);
        middle[0]=nullptr;
    }

    if(middle[1]!=nullptr){
        changedstates[1] = true;

        inner[1] = middle[1];
        middle[1]->setEN1(true);
        middle[1]=nullptr;
    }

    if(middle[2]!=nullptr){
        changedstates[2] = true;

        inner[2] = middle[2];
        middle[2]->setEN1(true);
        middle[2]=nullptr;
    }

    if(middle[3]!=nullptr){
        changedstates[3] = true;
        inner[3] = middle[3];
        middle[3]->setEN1(true);
        middle[3]=nullptr;
    }
}

// add to the queue to exit hive
void Board::addToLine(Bee *b){
    line.push_back(b);
}

// add to queue to enter hive
void Board::addToEnterLine(Bee *b){
    Enterline.push_back(b);
}
