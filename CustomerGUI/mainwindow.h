#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

#include "beechimes.h"

// DB COMPONENTS
#include "../DatabaseUI/dbtest/dbtable.h"
#include "../DatabaseUI/dbtest/dbtool.h"
#include "../DatabaseUI/dbtest/messagetable.h"
#include "../DatabaseUI/dbtest/usertable.h"
#include "../DatabaseUI/user.h"
#include "../DatabaseUI/sqlite-amalgamation-3280000/sqlite3.h"
#include "../Beehive/bee.h"
#include "../Beehive/beehive.h"
#include "../Beehive/board.h"
#include "../Beehive/brood.h"
#include "../Beehive/drone.h"
#include "../Beehive/forager.h"
#include "../Beehive/juvinile.h"
#include "../Beehive/nurse.h"
#include "../Beehive/queen.h"
#include "../Beehive/worker.h"
#include "../AlertSystem/alert.h"
#include "../AlertSystem/rob.h"
#include "../AlertSystem/swarm.h"
#include "../AlertUI/robalertui.h"
#include "../AlertUI/swarmalertui.h"
#include "../UDPHandler/dataanalyzer.h"
#include "../UDPHandler/HBoard.h"
#include "../UDPHandler/HDate.h"
#include "../UDPHandler/HTime.h"
#include "../UDPHandler/realtimesimulator.h"
#include "../UDPHandler/udphandler.h"
#include "../UDPHandler/udpmessagedata.h"
#include "../WeatherGUI/weatherwidg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Beehive *generator;
    // generate database object
    DBTool *dbtool;
    // generate a new table
    UserTable *users;
    //MAYBE NOT NULL
    User *currentUser;
    MessageTable *hiveDB;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    /**
     * @brief on_s2_pb_reset_clicked resets the user's passwor
     */
    void on_s2_pb_reset_clicked();

    /**
     * @brief on_s0_pb_Login_clicked logs the user in if username and password are correct
     */
    void on_s0_pb_Login_clicked();

    /**
     * @brief on_s0_pb_NewUser_clicked brings the user to the new user page
     */
    void on_s0_pb_NewUser_clicked();

    /**
     * @brief on_s1_pb_CreateUser_clicked creates a new user
     */
    void on_s1_pb_CreateUser_clicked();

    /**
     * @brief on_s3_pb_logout_clicked brings the user back to the login page
     */
    void on_s3_pb_logout_clicked();

    /**
     * @brief on_s5_pb_home_clicked from the hive selection page, brings the user to the home page
     */
    void on_s5_pb_home_clicked();

    /**
     * @brief on_s4_pb_add_clicked adds hive to database
     */
    void on_s4_pb_add_clicked();

    /**
     * @brief on_s4_pb_cancel_clicked cancels adding a hive to the database, returns user to home page
     */
    void on_s4_pb_cancel_clicked();

    /**
     * @brief on_s5_pb_selectHive_clicked brings user to the hive screen page
     */
    void on_s5_pb_selectHive_clicked();

    /**
     * @brief on_s7_pb_submitChanges_clicked sumbits changes to the database from the edit hive page
     */
    void on_s7_pb_submitChanges_clicked();

    /**
     * @brief on_s8_pb_back_clicked brings the user back to the hive screen page from the hive data page
     */
    void on_s8_pb_back_clicked();

    /**
     * @brief on_s6_pb_viewData_clicked brings the user to the hive data screen
     */
    void on_s6_pb_viewData_clicked();

    /**
     * @brief on_s6_pb_editHive_clicked brings the user to the edit hive screen
     */
    void on_s6_pb_editHive_clicked();

    /**
     * @brief on_s6_pb_back_clicked from the hive screen page, brings user back to home page
     */
    void on_s6_pb_back_clicked();

    void on_s3_pb_beeChimes_clicked();

    void receivedBackClicked();

    void on_s1_pb_back_clicked();

    void on_s3_pb_beeAlerts_clicked();

    void on_s3_pb_viewCurrentWeather_clicked();

    void receivedBackClickedWeather();

private:
    Ui::MainWindow *ui;
    // pointer to BeeChimes widget object
    BeeChimes * bc;
    std::vector<BeeChimes *> old_bcs;
    WeatherWidg * ww;
    std::vector<WeatherWidg *> old_wws;

};

#endif // MAINWINDOW_H
