#include "beehive.h"


// constructor with all var
Beehive::Beehive(string ID,int foNum, int NumOfBoard,int dronNum, double grow)
{
    using namespace std;
    growthP = grow;
    hiveID = ID;
    forNum = foNum;
    droneNum = dronNum;
    setNumOfBoards(NumOfBoard);
    randNumGen = (rand() % 10) + 1;
    srand (36);
    myfile.open("example.txt");
}

// constructor with no var
Beehive::Beehive(){
    using namespace std;
    growthP = .05;
    hiveID = "ID";
    forNum = 1000;
    droneNum = 10000;
    setNumOfBoards(10);
    randNumGen = (rand() % 10) + 1;
    srand (36);


}

//constructor with 1 var
Beehive::Beehive(string ID){
    using namespace std;
    growthP = .05;
    hiveID = ID;
    forNum = 1000;
    droneNum = 10000;
    setNumOfBoards(10);
    randNumGen = (rand() % 10) + 1;
    srand (36);

    myfile.open ("example.txt");
}

//deconstructor
Beehive::~Beehive(){
    //NOW CLOSED IN THE RUN METHOD WITH A PARAMETER
    //myfile.close();
}

// reset random times for the swarms/ arracks
void Beehive::randomSwarm(){
    Attack = true;
    swarm = true;
    int randTime1 = (rand() % 72000) + 21600;
    int randTime2 = (rand() % 72000) + 21600;
    AttackTime = randTime1;
    swarmTime = randTime2;
}

// the function for growing the bees simlpy
void Beehive::beeSimpleGrowth(double x){
    for (int i=0;i<x;i++) {
        Forager f;
        forageVect.push_back(f);
    }
    forNum +=x;
}
// set the number of years to run
void Beehive::setYearsToRun(int x){
    numofyears = x;
}

// initialize the starting number of bees
void Beehive::setStartingValues(){
    for (int i=0;i<numOfBoards;i++) {
        Board b;
        boardVect.push_back(b);
    }
    for (int i=0;i<forNum;i++) {
        Forager f;
        forageVect.push_back(f);
    }

    for (int i=0;i<1000;i++) {
        Worker f;
        workerVect.push_back(f);
    }

    for (int i=0;i<droneNum;i++) {
        Drone d;
        droneVect.push_back(d);
    }

    for (int i=0;i<500;i++) {
        Nurse n;
        nurseVect.push_back(n);
    }


}// need all the starting values

//set the season
void Beehive::setSeason(int x){
    q.setSeason(x);
    season = x;
}

//setup simulation
void Beehive::setup(){// need to finish this
    int x=1;
    setYearsToRun(x);
    setStartingValues();// need the starting values
}
// do 1 year of simulation(12 months)
void Beehive::OneYearTimeStep(){
    for (int i=0;i<12;i++) {
        OneMonthTimeStep();
    }
    cout<<"total bees entering normaly "<<BeeCounter<<"---"<<" total bees exiting normaly "<<exitCounter<<endl;
}

// do 1 month(28 days)
void Beehive::OneMonthTimeStep(){
    setSeason(season+1);
    for (int i=0;i<4;i++) {
        OneWeekTimeStep();
    }
}

//find how many bees to makw with simple growth
int Beehive::growthfunction(double x){
    return forNum*x;
}

// do 1 week of simulation
void Beehive::OneWeekTimeStep(){
    for (int i=0;i<7;i++) {
        killBees();
        foodCalculation();
        birthBees();
        pollenGen=0;
        pollenUsed=0;
        evolveBees();
        nurseBees();
        OneDayTimeStep();
        randomSwarm();
        //beeSimpleGrowth(growthfunction(growthP));
    }
}

//calculate how much food is used, and if bees starve
void Beehive::foodCalculation(){
    double pollenOut=0;
    double foodOut=0;

    for (int i=0;i<nurseVect.size();i++) {
        if(nurseVect.at(i).getFed()){

        }
        else{
            nurseVect.erase(nurseVect.begin()+i);

            i--;
        }


    }
    for (int i=0;i<workerVect.size();i++) {
        if(workerVect.at(i).getFed()){}
        else{
            workerVect.erase(workerVect.begin()+i);
            i--;
        }

    }
    for (int i=0;i<droneVect.size();i++) {
        if(droneVect.at(i).getFed()){}
        else{
            droneVect.erase(droneVect.begin()+i);
            i--;
        }

    }
    for (int i=0;i<forageVect.size();i++) {
        if(forageVect.at(i).getFed()){}
        else{
            forageVect.erase(forageVect.begin()+i);
            i--;
        }

    }
    for (int i=0;i<juviVect.size();i++) {
        if(juviVect.at(i).getFed()){}
        else{
            juviVect.erase(juviVect.begin()+i);
            i--;
        }

    }
    for (int i=0;i<broodVect.size();i++) {
        if(broodVect.at(i).getFed()){}
        else{
            broodVect.erase(broodVect.begin()+i);
            i--;
        }

    }
    for (int i=0;i<forageVect.size();i++) {
        if(foodAmount>=.013){
            foodAmount-=.013;
            foodOut+=.013;
            forageVect.at(i).setFed(true);
        }
        else{
            forageVect.at(i).setFed(false);
        }

    }

    for (int i=0;i<nurseVect.size();i++) {
        if(foodAmount>=.008){
            foodAmount-=.008;
            foodOut+=.008;
            nurseVect.at(i).setFed(true);
        }
        else{
            nurseVect.at(i).setFed(false);
        }



    }

    for (int i=0;i<juviVect.size();i++) {
        if(foodAmount>=.008){
            foodAmount-=.008;
            foodOut+=.008;
            juviVect.at(i).setFed(true);
        }
        else{
            juviVect.at(i).setFed(false);
        }

    }
    for (int i=0;i<broodVect.size();i++) {
        if(foodAmount>=.018&&pollenAmmount>=.067){
            foodAmount-= .018;
            foodOut+=.018;
            pollenAmmount-= .067;
            pollenOut+=.067;
            broodVect.at(i).setFed(true);
        }
        else{
            broodVect.at(i).setFed(false);
        }
    }
    for (int i=0;i<workerVect.size();i++) {
        if(foodAmount>=.008){
            foodAmount-=.008;
            foodOut+=.008;
            workerVect.at(i).setFed(true);
        }
        else{
            workerVect.at(i).setFed(false);
        }
    }
    for (int i=0;i<droneVect.size();i++) {
        if(foodAmount>=.01){
            foodAmount-=.01;
            foodOut+=.008;
            droneVect.at(i).setFed(true);
        }
        else{
            droneVect.at(i).setFed(false);
        }
    }
    pollenUsed = pollenOut;
}

// do 1 day of simulation
void Beehive::OneDayTimeStep(){//1x day things will need to update
    double temp =0;
    if(printOut==0){
        cout<<"0% done"<<endl;
    }
    else{
        temp= printOut/28;//336
        cout<<temp*100<<"% done"<<endl;
    }
    printOut+=1;
    TOD=0;

    for (int i=0;i<nurseVect.size();i++) {
        nurseVect.at(i).setAge(nurseVect.at(i).getAge()+86400);
    }
    for (int i=0;i<workerVect.size();i++) {
        workerVect.at(i).setAge(workerVect.at(i).getAge()+86400);
    }
    for (int i=0;i<droneVect.size();i++) {
        droneVect.at(i).setAge(droneVect.at(i).getAge()+86400);
    }
    for (int i=0;i<forageVect.size();i++) {
        forageVect.at(i).setAge(forageVect.at(i).getAge()+86400);
    }
    for (int i=0;i<juviVect.size();i++) {
        juviVect.at(i).setAge(juviVect.at(i).getAge()+86400);


    }
    for (int i=0;i<broodVect.size();i++) {
        broodVect.at(i).setAge(broodVect.at(i).getAge()+86400);
    }

    for (int i=0;i<24;i++) {
        OneHourTimeStep();
    }

    BeeCounter2=0;
    exitCounter2=0;
    atkC2=0;
    SWRMC2=0;

}

//do 1 hour of simulation
void Beehive::OneHourTimeStep(){
    for (int i=0;i<60;i++) {
        OneMinuteTimeStep();
    }
}

// do 1 minute of simulation
void Beehive::OneMinuteTimeStep(){
    for (int i=0;i<60;i++) {
        OneSecondTimeStep();
    }
}

// randomly a true bool 1:10 times
bool Beehive::divide10(){
    int x= (rand() % 10) + 1;
    int y =round(printOut);
    if(x==10 && y%10 >=5){
        return true;
    }
    return false;
}

// do 1 sec of simulation
void Beehive::OneSecondTimeStep(){
    currentTime++;
    TOD++;
    if(swarm&& TOD>=swarmTime && droneVect.size()>=droneNum){
        for (int i=0;i< droneVect.size();i++) {
            SwarmTech(&droneVect.at(i));
            droneVect.erase(droneVect.begin()+i);
            i--;
        }
        swarm = false;
    }
    if(Attack && TOD>=AttackTime && divide10()){
        for (int i=0;i <droneNum;i++) {
            Drone d;
            attackTech(&d);
        }
        Attack = false;
    }
    for (int i=0;i< forageVect.size();i++) {
        forageTech(&forageVect.at(i));
    }

    if(domilli){
        for (int i=0;i<1000;i++) {
            OneMillisecondTimeStep();
        }
    }
}

// do 1 millisecond of simulation
void Beehive::OneMillisecondTimeStep(){
    if(timeSinceMessage>=50){
        updateBoards();
        timeSinceMessage=0;
        if(checkBoards()){
            myfile << hiveID<<"-"<<parseTime(currentTime)<<boardString()<<"\n";
        }
    }
    timeSinceMessage++;
    milliCounter++;
    if(milliCounter > 999){
        milliCounter =0;
    }
}

//update all gates on all boards
void Beehive::updateBoards(){
    for(int j=0;j<boardVect.size();j++){
        boardVect.at(j).updateline(TOD);
    }
}

//checks if there are things in the gates
bool Beehive::checkBoards(){
    bool x = false;
    for (int i=0;i<boardVect.size();i++) {
        if (boardVect.at(i).checkBoards() ==0) {
        }
        else {
           x=true;
        }
    }
    return x;
}

//set the number of boards in the hive
void Beehive::setNumOfBoards(int x){
    numOfBoards =x;
}

//kill bees when they get too old
void Beehive::killBees(){
    int y=0;
    for (int i=0;i<droneVect.size();i++){
        if(droneVect.at(i).getAge()>=12960000+((rand() % 10)-5)){
            y++;
            droneVect.erase(droneVect.begin()+i);
            i--;
        }
    }
    for (int i=0;i<forageVect.size();i++){
        if(forageVect.at(i).getAge()>=12960000+((rand() % 10)-5)){
            forageVect.erase(forageVect.begin()+i);
            i--;
            y++;

        }
    }
    for (int i=0;i<nurseVect.size();i++){
        if(nurseVect.at(i).getAge()>=12960000+((rand() % 10)-5)){
            nurseVect.erase(nurseVect.begin()+i);
            y++;
            i--;

        }
    }
    for (int i=0;i<workerVect.size();i++){
        if(workerVect.at(i).getAge()>=12960000+((rand() % 10)-5)){
            workerVect.erase(workerVect.begin()+i);
            y++;
            i--;
        }
    }
}

//make new bees once a day
void Beehive::birthBees(){
    q.BirthEggs(season,pollenGen,pollenUsed);
    for (int i=0;i<q.getEgg();i++) {
        Brood b;
        broodVect.push_back(b);
    }
    fertilizeEggs();
}

//fertilize the brood to decide gender
void Beehive::fertilizeEggs(){
    int j=broodVect.size()-1;
    int i=0;
    double k= q.getEgg();
    k = k*2;
    k = k/3;
    while(i<k){
        broodVect.at(j).setFert(true);
        j--;
        i++;
    }
}

// make bees into other kinds of bees
void Beehive::evolveBees(){
    if(broodVect.size()!=0){
        for(int i=0;i<broodVect.size();i++){
            if(broodVect.at(i).getFert()&& broodVect.at(i).getAge() >= 1814400){
                Juvinile j;
                j.setAge(broodVect.at(i).getAge());
                juviVect.push_back(j);
                broodVect.erase(broodVect.begin()+i);
                i--;
            }
            else if(!broodVect.at(i).getFert() && broodVect.at(i).getAge() >= 2073600){
                Drone d;
                d.setAge(broodVect.at(i).getAge());
                droneVect.push_back(d);
                broodVect.erase(broodVect.begin()+i);
                i--;
            }
            else{

            }
        }
    }
    if(juviVect.size()!=0){
        for(int i=0;i<juviVect.size();i++){
            if(juviVect.at(i).getAge() >= (1814400+259200)){
                Nurse n;
                n.setAge(juviVect.at(i).getAge());
                nurseVect.push_back(n);
                juviVect.erase(juviVect.begin()+i);
                i--;
            }

            else{

            }
        }
    }

    if(nurseVect.size()!=0){
        for(int i=0;i<nurseVect.size();i++){
            if(broodVect.size()>(nurseVect.size()*3/2)&& !initrun){
                }
            else if (forageVect.size()>.3*(forageVect.size()+nurseVect.size()+workerVect.size()+droneVect.size()+juviVect.size()+broodVect.size())) {
                Worker w;
                w.setAge(nurseVect.at(i).getAge());
                workerVect.push_back(w);
                nurseVect.erase(nurseVect.begin()+i);

                i--;
            }
            else{
                Forager f;
                f.setAge(nurseVect.at(i).getAge());
                forageVect.push_back(f);
                nurseVect.erase(nurseVect.begin()+i);

                i--;
            }


        }
    }//need this for workers

    if(workerVect.size()!=0){
        for(int i=0;i<workerVect.size();i++){
            if(broodVect.size()>(nurseVect.size()*3/2)){
                // make nurse
                Nurse w;
                w.setAge(workerVect.at(i).getAge());
                nurseVect.push_back(w);
                workerVect.erase(workerVect.begin()+i);
                i--;
            }
            else if (forageVect.size()>.3*(forageVect.size()+nurseVect.size()+workerVect.size()+juviVect.size()+broodVect.size())) {
            }
            else{
                Forager f;
                f.setAge(nurseVect.at(i).getAge());
                forageVect.push_back(f);
                workerVect.erase(workerVect.begin()+i);// this could have problems
                i--;
            }
        }
    }
    initrun=false;
}

//set the temperature
void Beehive::setWeather(double x){
    temperature=x;
}

// nurse young brood, or the brood die
void Beehive::nurseBees(){
    if(broodVect.size()>=0){
        if(broodVect.size()>(nurseVect.size()*3/2)){
            double x = broodVect.size()-(nurseVect.size()*3/2);
            for(int i=0;i<x;i++){
                broodVect.erase(broodVect.end());
            }
        }
    }
}

// update state machine for a single forager
void Beehive::forageTech(Forager *h){

    if((TOD<=21600||TOD>=72000)||temperature<50 && temperature >=100){
        if (h->getFor()==true) {

            forageStep(h);
        }
        else if (h->getNest() == true) {

            returnToNest(h);
        }
        else if (h->getSearch()==true) {

            searchForThing(h);
        }
        else if (h->getEx()==true) {

            explore(h);
        }
        else if (h->getDanceB() == true) {

            beginDance(h);
        }

        else if (h->getEnter() == true) {

            enterStates(h);
        }
    }
    else{
        if(h->getinit() == true){

            hasTarget(h);
        }
        else if (h->getFor()==true) {

            forageStep(h);
        }
        else if (h->getNest() == true) {

            returnToNest(h);
        }
        else if (h->getSearch()==true) {

            searchForThing(h);
        }
        else if (h->getEx()==true) {

            explore(h);
        }
        else if (h->getDanceB() == true) {

            beginDance(h);
        }
        else if (h->getEat()== true ){

            restOrEat(h);
        }
        else if (h->getEnter() == true) {

            enterStates(h);
        }
        else if (h->getExit()== true) {


            exitStates(h);

        }
        else {
        }
    }
}

//state for when bee tries to enter the hive
void Beehive::enterStates(Forager *f){
    if(f->getEN2()== false){
        boardVect.at(boardcycle).addToEnterLine(f);
        if(changenow>4){
            changenow =0;
            boardcycle++;
            if(boardcycle == boardVect.size()){
                boardcycle =0;
            }
        }
        changenow++;
     }
    else if(f->getEX2() == false){}
    else if (f->getEN1() == false) {}
    else if(f->getEx1() == false){ }
    else {
        BeeCounter++;
        BeeCounter2++;
        f->setEnter(false);
        f->setEN2(false);
        f->setEN1(false);
        f->setEX2(false);
        f->setEX1(false);
        if(f->getDance()){
            f->setDanceB(true);
            f->setNest(false);
            f->setTime(0);
        }
        else{
            f->setEat(true);
            pollenGen+=.016;
            pollenAmmount+=.016;
            foodAmount+=.03;
            f->setNest(false);
            f->setTime(0);
        }
    }
}

// state for when bee exits the hive
void Beehive::exitStates(Forager *f){
    if(f->getEN1()== false){
        boardVect.at(boardcycle).addToLine(f);
        if(changenow>4){
            changenow =0;
            boardcycle++;
            if(boardcycle == boardVect.size()){
                boardcycle =0;
            }
        }
        changenow++;
    }
    else if(f->getEx1() == false){}
    else if (f->getEN2() == false){}
    else if(f->getEX2() == false){}
    else {
        exitCounter++;
        exitCounter2++;
        f->setExit(false);
        f->setEN2(false);
        f->setEN1(false);
        f->setEX2(false);
        f->setEX1(false);
        f->setInit(true);
    }
}

//checks whether or not bee has a defined target
bool Beehive::hasTarget(Forager *f){
    if(f->getTarget()){
        f->setInit(false);
        f->setSearch(true);
        f->setTime(0);

        return true;
    }
    else {
        f->setInit(false);
        f->setEX(true);
        f->setTime(0);
        return false;
    }
}

//checks if bee is tired
bool Beehive::isTired(Forager *f){
    if(f->getTime() >= 1200+ randNumGen){
        f->setEX(false);
        f->setSearch(false);
        f->setNest(true);

        randNumGen = (rand() % 10) + 1;
        return true;
    }
    else{
        return false;
    }

}

// checks if bee found food
bool Beehive::foundFood(Forager *f){
    isTired(f);
    if(f->getTarget() &&f->getTime() > 900+randNumGen){
        f->setEX(false);
        f->setSearch(false);
        f->setFoundFood(true);
        f->setFor(true);
        f->setTime(0);
        randNumGen = (rand() % 10) + 1;
        return true;
    }
    else if(f->getTime() > 1200+randNumGen){
        f->setEX(false);
        f->setSearch(false);
        f->setFoundFood(true);
        f->setTarget(true);
        f->setFor(true);
        f->setTime(0);
        randNumGen = (rand() % 10) + 1;
        return true;
    }
    else {
        return false;
    }
}

// state where bee gathers food
void Beehive::Beehive::forageStep(Forager *f){
    if(f->getFull() == false){
    }
    else{
        f->setFor(false);
        f->setNest(true);
        f->setDance(dance(f));
        f->setTime(0);
    }
    if(f->getTime() >= 100+randNumGen){
        f->setFull(true);
        randNumGen = (rand() % 10) + 1;
    }
    f->setTime(f->getTime()+1);
}

// make 1 drone in hive swarm
void Beehive::SwarmTech(Bee *b){
    boardVect.at(boardcycle).addToLine(b);
    if(changenow>4){
        changenow =0;
        boardcycle++;
        if(boardcycle == boardVect.size()){
            boardcycle =0;
        }
    }
    changenow++;
    SWRMC++;
    SWRMC2++;

}

//make 1 drone out of hive attack
void Beehive::attackTech(Bee *b){
    boardVect.at(boardcycle).addToEnterLine(b);
    if(changenow>4){
        changenow =0;
        boardcycle++;
        if(boardcycle == boardVect.size()){
            boardcycle =0;
        }
    }
    atkC++;
    atkC2++;
    changenow++;
}

// state for returning to the nest
void Beehive::returnToNest(Forager *f){

    if(f->getTime() >= 600+randNumGen){
        f->setNest(false);
        f->setEnter(true);
        randNumGen = (rand() % 10) + 1;
        return;
    }
    f->setTime(f->getTime()+1);
}

// state for exploring
void Beehive::explore(Forager *f){
    f->setTime(f->getTime()+1);
    foundFood(f);
}

// state for bee heading toward a known food location
void Beehive::searchForThing(Forager *f){
    f->setTime(f->getTime()+1);
    foundFood(f);
}

// decide of bee will dance or not
bool Beehive::dance(Forager *f){
    if(f->getTarget()){
        return true;
    }
    else{
        return false;
    }
}

// dance to tell 1 other bee where food is
void Beehive::beginDance(Forager *f){
    for (int var = 0; var < forageVect.size(); ++var) {
        if(forageVect.at(var).getTarget() == false){
            forageVect.at(var).setTarget(true);
            f->setEat( true);
            pollenGen+=.016;
            pollenAmmount+=.016;
            foodAmount+=.03;
            f->setDance(false);
            f->setDanceB(false);
            f->setTime(0);
            return;
        }
    }
    f->setEat( true);
    pollenGen+=.016;
    pollenAmmount+=.016;
    foodAmount+=.03;
    f->setDance(false);
    f->setDanceB(false);
    f->setTime(0);

}

//state for resting in the hive
void Beehive::restOrEat(Forager *f){
    if(f->getTime() > 3600+randNumGen){
        f->setEat( false);
        f->setTime(0);
        f->setFull(true);
        f->setTired(false);
        f->setExit(true);
        randNumGen = (rand() % 10) + 1;
        f->setTime(0);
    }
    else {
        f->setTime(f->getTime()+1);
    }
}

//gets the current time for the udp message
string Beehive::parseTime(int t){
    string s;

    int year =2019+(t / 29030400);
    int temp = t % 29030400;
    int month = 1+(temp / 2419200);
    temp = temp % 2419200;
    int day = 1+(temp / 86400) ;

    int hour = (t % 86400)/3600 ;

    int minute = (t % 3600)/60;

    int second = t % 60;
    int mill = milliCounter;

    s.append("D");
    s.append(to_string(day));
    s.append(".");
    s.append(to_string(month));
    s.append(".");
    s.append(to_string(year));


    s.append("T");
    s.append(to_string(hour));
    s.append(".");
    s.append(to_string(minute));
    s.append(".");
    s.append(to_string(second));
    if(mill <10){
        string temp ="00";
        temp.append(to_string(mill));

        s.append(temp);
    }

    else if(mill<100){
        string temp ="0";
        temp.append(to_string(mill));

        s.append(temp);
    }
    else{
        s.append(to_string(mill));
    }
    return s;
}

// gets all the strings from the boards from the udp message
string Beehive::boardString(){
    string s;
    s.append("-");
    for(int i=0;i<numOfBoards;i++){
        s.append("B");
        s.append(to_string(boardVect.at(i).calculateBool()));
    }
    ////cout<<"s - "<<s<<endl;
    return s;
}

// run the simulation normally for a year
void Beehive::run(){
    setup();
    for (int i=0;i<numofyears;i++) {
        // OneWeekTimeStep();
        OneYearTimeStep();
        // OneDayTimeStep();
        // OneHourTimeStep();
        // OneMonthTimeStep();
    }

}
// run the simulation for a day  with the hiveID as an imput
void Beehive::run(string ID){
    hiveID=ID;

  //  setWeather(//make things here);

   //PROVIDES FULL PATH
//    std::string abs_path = "/Users/ricdonati/desktop/build-qtrepo_grp00_may-Desktop_Qt_5_12_0_clang_64bit-Debug/CustomerGUI/";
//    std::cout << "Creating file at " << abs_path + ID + ".txt" << std::endl;

    std::string path = "../../../";
    std::string file_name = path + ID + ".txt";

    myfile.open(file_name);
    setup();

    for (int i=0;i<numofyears;i++) {
        // OneWeekTimeStep();
        // OneYearTimeStep();
        OneDayTimeStep();
        //OneHourTimeStep();
        // OneMonthTimeStep();
    }
    myfile.close();
}
