#ifndef BEECHIMES_H
#define BEECHIMES_H

#include <vector>
#include <math.h>

#include "../DatabaseUI/dbtest/dbtable.h"
#include "../DatabaseUI/dbtest/dbtool.h"
#include "../DatabaseUI/dbtest/messagetable.h"
#include "../DatabaseUI/dbtest/usertable.h"
#include "../DatabaseUI/user.h"
#include "../DatabaseUI/sqlite-amalgamation-3280000/sqlite3.h"
#include "../UDPHandler/udpmessagedata.h"

#include <QWidget>
#include <QMediaPlayer>
#include <QTimer>

// an Event is a representation of a HiveChimes system at a point in time given the active gates
struct Event
{   
    long time; // the time, in milliseconds, of the event (in comparision to start time)
    int g1; // the number of boards with gate 1 active
    int g2; // the number of boards with gate 2 active
    int g3; // the number of boards with gate 3 active
    int g4; // the number of boards with gate 4 active
    int g5; // the number of boards with gate 5 active
    int g6; // the number of boards with gate 6 active
    int g7; // the number of boards with gate 7 active
    int g8; // the number of boards with gate 8 active
};

namespace Ui {
class BeeChimes;
}

class BeeChimes : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief BeeChimes constructor to make BeeChimes with full functionality
     * @param parent QWidget parent
     * @param _username Username in database
     * @param hdb MessageTable pointer to the hive's database
     * @param _scale Scale of bee time in comparision to real time
     * @param _incr Minimum time increment between notes
     * @param _perc Percent of the simulation played
     */
    explicit BeeChimes(QWidget *parent = nullptr, QString _username = "user", MessageTable * hdb = nullptr, double _scale = 1, int _incr = 100, float _perc = 0.5);
    ~BeeChimes();

private slots:
    void play_events(); // plays through the events vector
    void on_pb_play_clicked(); // when play button is clicked
    void on_vs_volume_sliderMoved(int position); // when the volume slider is moved
    void on_pb_pause_clicked(); // when the pause button is clicked
    void on_pb_stop_clicked(); // when the stop button is clicked
    void on_pb_back_clicked(); // when the back button is clicked

signals:
    void backClicked(); // signal for when the back button is clicked

private:
    Ui::BeeChimes *ui;// ui
    // vector of events
    std::vector<Event> events;
    // instance variables related to events
    int events_ind;
    // instance variables related to timer
    QTimer * timer; // timer
    int startTime; // start time of simulation
    int curr_time; // current time, in relation to start of timer
    int incr; // time increment of timer
    double bee_scale; // scale of bee time compared to real time
    int bee_time; // current time for the beehive
    int bee_incr; // increment for bee time instead of real time
    // instance variables related to QMediaPlayers
    int num_players; // size of qmp vectors
    int max_vol; // maximum volume
    double vol_adjust; // affects the percent of max volume played per bee in a gate
    // QMediaPlayer * vectors for each gate
    std::vector<QMediaPlayer *> g1_qmps;
    std::vector<QMediaPlayer *> g2_qmps;
    std::vector<QMediaPlayer *> g3_qmps;
    std::vector<QMediaPlayer *> g4_qmps;
    std::vector<QMediaPlayer *> g5_qmps;
    std::vector<QMediaPlayer *> g6_qmps;
    std::vector<QMediaPlayer *> g7_qmps;
    std::vector<QMediaPlayer *> g8_qmps;
    // number of times each type of gate has been played
    // used for cycling through qmp objects in the appropriate vectors
    int g1_plays;
    int g2_plays;
    int g3_plays;
    int g4_plays;
    int g5_plays;
    int g6_plays;
    int g7_plays;
    int g8_plays;

    // methods for each gate's qmp vector
    void play_g1(int active);
    void play_g2(int active);
    void play_g3(int active);
    void play_g4(int active);
    void play_g5(int active);
    void play_g6(int active);
    void play_g7(int active);
    void play_g8(int active);
    // plays each appropriate gate method based on active gates
    void play_gates(int g1_a, int g2_a, int g3_a, int g4_a, int g5_a, int g6_a, int g7_a, int g8_a);
    void loadQMPs(); // creates new qmp objects in the appropriate vectors
    void loadEvents(); // loads in events to play

    QString username; // Username to display at top of screen
    MessageTable * hiveDataBase; // MessageTable in database for this hive
    float perc_played; // percentage of hiveDataBase read in

    int return_compare(int base, int a, int b, int c, int d, int e, int f, int g);

};

#endif // BEECHIMES_H
