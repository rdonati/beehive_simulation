#include "beechimes.h"
#include "ui_beechimes.h"

BeeChimes::BeeChimes(QWidget *parent, QString _username, MessageTable * hDB, double _scale, int _incr, float _perc) :
    QWidget(parent),
    ui(new Ui::BeeChimes)
{
    ui->setupUi(this);

    // set instance variables
    hiveDataBase = hDB;
    incr = _incr;
    curr_time = 0;
    bee_time = 0;
    bee_scale = _scale;
    bee_incr = (int)(bee_scale * incr);
    max_vol = 100;
    vol_adjust = 0.5;
    events_ind = 0;
    username = _username;
    timer = new QTimer();
    perc_played = _perc;

    // instance variables for QMPs
    g1_plays = 0;
    g2_plays = 0;
    g3_plays = 0;
    g4_plays = 0;
    g5_plays = 0;
    g6_plays = 0;
    g7_plays = 0;
    g8_plays = 0;
    if(incr < 4000)
    {
        num_players = (4000 / incr) + 1;
    }
    else {
        num_players = 10;
    }
    std::cout << "Num Players" << num_players << std::endl;
    // title to display
    QString title = "Welcome to ";
    title += username;
    title += "'s BeeChimes";
    ui->l_title->setText(title);
    loadQMPs();
    loadEvents();
}

BeeChimes::~BeeChimes()
{
    for(int i = 0; i < g1_qmps.size(); i++)
    {
        delete g1_qmps[i];
        delete g2_qmps[i];
        delete g3_qmps[i];
        delete g4_qmps[i];
        delete g5_qmps[i];
        delete g6_qmps[i];
        delete g7_qmps[i];
        delete g8_qmps[i];
    }
    delete hiveDataBase;
    delete timer;
    delete ui;
}

void BeeChimes::loadQMPs()
{
    // creates a specified number of QMediaPlayer objects for each gate
    // this is necessary so that notes can be played multiple times before the sound file stops
    for(int i = 0; i < num_players; i++)
    {
        g1_qmps.push_back(new QMediaPlayer());
        g1_qmps[i]->setMedia(QUrl("qrc:/sounds/bells_c5.mp3"));
        g2_qmps.push_back(new QMediaPlayer());
        g2_qmps[i]->setMedia(QUrl("qrc:/sounds/bells_e5.mp3"));
        g3_qmps.push_back(new QMediaPlayer());
        g3_qmps[i]->setMedia(QUrl("qrc:/sounds/bells_g5.mp3"));
        g4_qmps.push_back(new QMediaPlayer());
        g4_qmps[i]->setMedia(QUrl("qrc:/sounds/bells_b5.mp3"));
        g5_qmps.push_back(new QMediaPlayer());
        g5_qmps[i]->setMedia(QUrl("qrc:/sounds/bells_b6.mp3"));
        g6_qmps.push_back(new QMediaPlayer());
        g6_qmps[i]->setMedia(QUrl("qrc:/sounds/bells_g6.mp3"));
        g7_qmps.push_back(new QMediaPlayer());
        g7_qmps[i]->setMedia(QUrl("qrc:/sounds/bells_e6.mp3"));
        g8_qmps.push_back(new QMediaPlayer());
        g8_qmps[i]->setMedia(QUrl("qrc:/sounds/bells_c6.mp3"));
    }
}

void BeeChimes::loadEvents()
{
    // loads in Event objects into events vector

    // the amount of messages to load from hiveDataBase based on percentage of simulation to play
    int num_messages = hiveDataBase->size() * perc_played;
    // int num_messages = 50; // hardcoded
    // gets messages from hiveDataBase as std::string's
    std::vector<std::string> tempMessages = hiveDataBase->get_messages(num_messages);
    // converts std::string's UDPMessageData objects, loads into a vector
    std::vector<UDPMessageData*> temp;
    for(int i = 0; i < tempMessages.size(); i++){
        temp.push_back(new UDPMessageData(tempMessages[i]));
    }
    // NOTE: our database has the UDP messages sorted based on time
    // insert first event into events with time set to 0
    std::vector<int> data = temp[0]->musicify();
    events.push_back(Event{0, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]});

    //NEEDS TO CONVERT TO Event STRUCTS
    for(int i = 1; i < temp.size(); i++){
        // gets appropriate gate active ints from UDP message
        std::vector<int> data = temp[i]->musicify();
        // NOTE: our method to compare HTime assumes comparision within a 24 hour period
        // for this reason, time is compared to the previous event then added to previous event's time to get correct time since first event
        // get the time between this event and last event
        long diff = temp[i- 1]->get_time().compare_to(temp[i]->get_time());
        // add to time of last event to find this event's time
        long e_time = events[i - 1].time + diff;
        // create event and pushback into events
        events.push_back(Event{e_time, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]});
    }

    /*
    // hard coded
    Event one = {1000, 1, 0, 0, 0, 0, 0, 0, 0};
    Event two = {1500, 0, 1, 0, 0, 0, 0, 0, 0};
    Event three = {2000, 0, 0, 1, 0, 0, 0, 0, 0};
    Event four = {2500, 0, 0, 0, 1, 0, 0, 0, 0};
    Event five = {3000, 0, 0, 0, 0, 1, 0, 0, 0};
    Event six = {3500, 0, 0, 0, 0, 0, 1, 0, 0};
    Event seven = {4000, 0, 0, 0, 0, 0, 0, 1, 0};
    Event eight = {4500, 0, 0, 0, 0, 0, 0, 0, 1};
    Event nine = {8003, 1, 0, 0, 0, 0, 0, 0, 0};
    Event ten = {8004, 0, 1, 0, 0, 0, 0, 0, 0};
    events.push_back(one);
    events.push_back(two);
    events.push_back(three);
    events.push_back(four);
    events.push_back(five);
    events.push_back(six);
    events.push_back(seven);
    events.push_back(eight);
    events.push_back(nine);
    events.push_back(ten);
    */

}

void BeeChimes::on_pb_play_clicked()
{
    // connect the timer to the proper function
    connect(timer, SIGNAL(timeout()), this, SLOT(play_events()));
    // start the timer based on time increment
    timer->start(incr);
    // set status
    ui->l_status->setText("Pressed Play");
}

void BeeChimes::play_events()
{
    // if index is greater than size of events (should not happen), return
    if(events_ind >= events.size())
        return;
    // instance variables for active gates of each type active during this time increment
    int g1s = 0;
    int g2s = 0;
    int g3s = 0;
    int g4s = 0;
    int g5s = 0;
    int g6s = 0;
    int g7s = 0;
    int g8s = 0;
    // NOTE: assumes sorted events vector
    // while index less than size of events, and time of event at index is between current bee time and the next bee time increment
    while(events_ind < events.size(), events[events_ind].time >= bee_time && events[events_ind].time <= (bee_time + bee_incr))
    {
        // add number of active gates for this event to appropriate variables
        g1s += events[events_ind].g1;
        g2s += events[events_ind].g2;
        g3s += events[events_ind].g3;
        g4s += events[events_ind].g4;
        g5s += events[events_ind].g5;
        g6s += events[events_ind].g6;
        g7s += events[events_ind].g7;
        g8s += events[events_ind].g8;
        events_ind++;
    }
    std::cout << "Bee Time: " << bee_time << std::endl;
    std::cout << "Events Index: " << events_ind << std::endl;
    // adjust so only 4 most busy gates are played at once
    int g1a = return_compare(g1s, g2s, g3s, g4s, g5s, g6s, g7s, g8s);
    int g2a = return_compare(g2s, g1s, g3s, g4s, g5s, g6s, g7s, g8s);
    int g3a = return_compare(g3s, g2s, g1s, g4s, g5s, g6s, g7s, g8s);
    int g4a = return_compare(g4s, g2s, g3s, g1s, g5s, g6s, g7s, g8s);
    int g5a = return_compare(g5s, g2s, g3s, g4s, g1s, g6s, g7s, g8s);
    int g6a = return_compare(g6s, g2s, g3s, g4s, g5s, g1s, g7s, g8s);
    int g7a = return_compare(g7s, g2s, g3s, g4s, g5s, g6s, g1s, g8s);
    int g8a = return_compare(g8s, g2s, g3s, g4s, g5s, g6s, g7s, g1s);
    // play_gates based on number of gates active within this time increment
    play_gates(g1a, g2a, g3a, g4a, g5a, g6a, g7a, g8a);
    // increment bee time (bee time scale)
    bee_time += bee_incr;
    // increment current time (real time scale)
    curr_time += incr;
    // if no more events to play
    if(events_ind >= events.size())
    {
        // stop timer
        timer->stop();
        // reset appropriate variables
        curr_time = 0;
        bee_time = 0;
        events_ind = 0;
        // set screen's status
        ui->l_status->setText("Played through all events");
    }
}

void BeeChimes::play_gates(int g1_a, int g2_a, int g3_a, int g4_a, int g5_a, int g6_a, int g7_a, int g8_a)
{
    // play appropriate methods based on respective parameters for active gates
    play_g1(g1_a);
    play_g2(g2_a);
    play_g3(g3_a);
    play_g4(g4_a);
    play_g5(g5_a);
    play_g6(g6_a);
    play_g7(g7_a);
    play_g8(g8_a);
}

void BeeChimes::play_g1(int active)
{
    // if no active gates, return
    if(active == 0)
        return;
    // volume based on number of gates active and maximum volume
    int vol = (100 - (100 * pow(vol_adjust, active))) / 100 * max_vol;
    // g1_plays % num_players cycles through the vector of qmps to ensure the qmp will play
    // set the volume of appropriate qmp
    g1_qmps[g1_plays % num_players]->setVolume(vol);
    // play the appropriate qmp
    g1_qmps[g1_plays % num_players]->play();
    g1_plays++;
}

void BeeChimes::play_g2(int active)
{
    // if no active gates, return
    if(active == 0)
        return;
    // volume based on number of gates active and maximum volume
    int vol = (100 - (100 * pow(vol_adjust, active))) / 100 * max_vol;
    // g2_plays % num_players cycles through the vector of qmps to ensure the qmp will play
    // set the volume of appropriate qmp
    g2_qmps[g2_plays % num_players]->setVolume(vol);
    // play the appropriate qmp
    g2_qmps[g2_plays % num_players]->play();
    g2_plays++;
}

void BeeChimes::play_g3(int active)
{
    // if no active gates, return
    if(active == 0)
        return;
    // volume based on number of gates active and maximum volume
    int vol = (100 - (100 * pow(vol_adjust, active))) / 100 * max_vol;
    // g3_plays % num_players cycles through the vector of qmps to ensure the qmp will play
    // set the volume of appropriate qmp
    g3_qmps[g3_plays % num_players]->setVolume(vol);
    // play appropriate media player
    g3_qmps[g3_plays % num_players]->play();
    g3_plays++;
}

void BeeChimes::play_g4(int active)
{
    // if no active gates, return
    if(active == 0)
        return;
    // volume based on number of gates active and maximum volume
    int vol = (100 - (100 * pow(vol_adjust, active))) / 100 * max_vol;
    // g4_plays % num_players cycles through the vector of qmps to ensure the qmp will play
    // set the volume of appropriate qmp
    g4_qmps[g4_plays % num_players]->setVolume(vol);
    // play the appropriate qmp
    g4_qmps[g4_plays % num_players]->play();
    g4_plays++;
}

void BeeChimes::play_g5(int active)
{
    // if no active gates, return
    if(active == 0)
        return;
    // volume based on number of gates active and maximum volume
    int vol = (100 - (100 * pow(vol_adjust, active))) / 100 * max_vol;
    // g5_plays % num_players cycles through the vector of qmps to ensure the qmp will play
    // set the volume of appropriate qmp
    g5_qmps[g5_plays % num_players]->setVolume(vol);
    // play the appropriate qmp
    g5_qmps[g5_plays % num_players]->play();
    g5_plays++;
}

void BeeChimes::play_g6(int active)
{
    // if no active gates, return
    if(active == 0)
        return;
    // volume based on number of gates active and maximum volume
    int vol = (100 - (100 * pow(vol_adjust, active))) / 100 * max_vol;
    // g6_plays % num_players cycles through the vector of qmps to ensure the qmp will play
    // set the volume of appropriate qmp
    g6_qmps[g6_plays % num_players]->setVolume(vol);
    // play the appropriate qmp
    g6_qmps[g6_plays % num_players]->play();
    g6_plays++;
}

void BeeChimes::play_g7(int active)
{
    // if no active gates, return
    if(active == 0)
        return;
    // volume based on number of gates active and maximum volume
    int vol = (100 - (100 * pow(vol_adjust, active))) / 100 * max_vol;
    // g7_plays % num_players cycles through the vector of qmps to ensure the qmp will play
    // set the volume of appropriate qmp
    g7_qmps[g7_plays % num_players]->setVolume(vol);
    // play the appropriate qmp
    g7_qmps[g7_plays % num_players]->play();
    g7_plays++;
}

void BeeChimes::play_g8(int active)
{
    // if no active gates, return
    if(active == 0)
        return;
    // volume based on number of gates active and maximum volume
    int vol = (100 - (100 * pow(vol_adjust, active))) / 100 * max_vol;
    // g8_plays % num_players cycles through the vector of qmps to ensure the qmp will play
    // set the volume of appropriate qmp
    g8_qmps[g8_plays % num_players]->setVolume(vol);
    // play the appropriate qmp
    g8_qmps[g8_plays % num_players]->play();
    g8_plays++;
}


void BeeChimes::on_vs_volume_sliderMoved(int position)
{
    // sets max_vol to positition (which is set from 0 to 100)
    max_vol = position;
}

void BeeChimes::on_pb_pause_clicked()
{
    // stops the timer, pauses simulation
    timer->stop();
}

void BeeChimes::on_pb_stop_clicked()
{
    // stops the timer
    timer->stop();
    // resets appropriate time and index variables
    curr_time = 0;
    bee_time = 0;
    events_ind = 0;
}

void BeeChimes::on_pb_back_clicked()
{
    // emit backClicked signal
    emit backClicked();
    // stop timer
    timer->stop();
    // close window
    this->close();
}

int BeeChimes::return_compare(int base, int a, int b, int c, int d, int e, int f, int g)
{
    int ret = 0;
    if(base > a)
        ret++;
    if(base > b)
        ret++;
    if(base > c)
        ret++;
    if(base > d)
        ret++;
    if(base > e)
        ret++;
    if(base > f)
        ret++;
    if(base > g)
        ret++;
    if(ret < 4)
        ret = 0;
    return ret;
}
