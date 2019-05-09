#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    generator = new Beehive();
    dbtool = new DBTool("beesknees");
    users = new UserTable(dbtool, "users");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < old_wws.size(); i++)
    {
        delete old_wws[i];
    }
    for(int i = 0; i < old_bcs.size(); i++)
    {
        delete old_bcs[i];
    }
    delete bc;
    delete ww;
    delete generator;
    delete users;
    delete dbtool;
    delete currentUser;
    delete hiveDB;
    delete ui;
}

void MainWindow::on_s2_pb_reset_clicked()
{
    // save user input in QStrings
    QString username = ui->s2_le_username->text();
    QString password = ui->s2_le_newPassword->text();
    QString conf_password = ui->s2_le_confPassword->text();
    // ADD FUNCTIONALITY
    // check if the username exists in the database
    if(username.compare("bees") != 0)
    {
        ui->s2_l_status->setText("Invalid username");
    }
    // check if new passwords match
    else if(password.compare(conf_password) != 0)
    {
        ui->s2_l_status->setText("Passwords do not match");
    }
    // if all good to reset username's password
    else
    {
        // this is where we would access the database
        // clear user input fields
        ui->s2_le_username->clear();
        ui->s2_le_newPassword->clear();
        ui->s2_le_confPassword->clear();
        // changes to s_login
        ui->stackedWidget->setCurrentIndex(0);
        ui->s0_l_status->setText("Currently not connected to a database, cannot change password. Please login with bees knees");
    }
}

void MainWindow::on_s0_pb_Login_clicked()
{
    // save user input in QStrings
    std::string username = ui->s0_le_username->text().toStdString();
    std::string password = ui->s0_le_password->text().toStdString();
    // ADD FUNCTIONALITY
    // this is where we'd check the database for login info
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    if(users->check_credentials(username, password))
    {
        // CREATES AND POPULATES A UDP MESSAGE DATABASE W/ USERNAME AS NAME
        //ui->s0_l_status->setText("Generating user data...\nShould take about 5 seconds");
        hiveDB = new MessageTable(dbtool, username);
        generator->run(username);

        // Absolute paths
//        std::string abs_path = "/Users/ricdonati/desktop/build-qtrepo_grp00_may-Desktop_Qt_5_12_0_clang_64bit-Debug/CustomerGUI/";
//        std::string file_name = abs_path + username + ".txt";

        std::string path = "../../../";
        std::string file_name = path + username + ".txt";

        hiveDB->populate(file_name);


        currentUser = users->get_user(username);
        // clear user input fields
        ui->s0_le_password->clear();
        ui->s0_le_username->clear();
        ui->s0_l_status->clear();
        // changes to s_homeScreen
        ui->stackedWidget->setCurrentIndex(3);
        QString message = QString::fromStdString("Welcome, " + currentUser->getFirstName() + "!");
        ui->s3_l_status->setText(message); // this would be adjusted based on the user name
    }
    else if(username.compare("bees") == 0) // if incorrect password for the username (username could still be wrong)
    {
        ui->s0_l_status->setText("Incorrect username or password");
    }
    else // if username does not exist in database
    {
        ui->s0_l_status->setText("Invalid username");
    }
}

void MainWindow::on_s0_pb_NewUser_clicked()
{
    // clear user input fields
    ui->s0_le_password->clear();
    ui->s0_le_username->clear();
    // change to s_newUser
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_s1_pb_CreateUser_clicked()
{
    std::string username = ui->s1_le_username->text().toStdString();
    std::string password = ui->s1_le_password->text().toStdString();
    std::string conf_password = ui->s1_le_confirmPassword->text().toStdString();
    std::string first_name = ui->s1_le_firstName->text().toStdString();
    std::string last_name = ui->s1_le_lastName->text().toStdString();
    std::string email = ui->s1_le_email->text().toStdString();

    if(username == "" || first_name == "" || last_name == "" || email == "")  // CHECKS THAT ALL THE FIELDS ARE FILLED OUT
    {
        ui->s1_l_status->setText("Please make sure ALL fields are filled out");
    }
    else if(password.compare(conf_password) != 0)  // CHECKS THAT PASSWORDS ARE THE SAME
    {
        ui->s1_l_status->setText("Passwords do not match!");
    }
    else
    {
        // CHECKS THAT USERNAME DOESN'T ALREADY EXIST
        if(users->add_row(email, first_name, last_name, username, password) != 0){
            ui->s1_l_status->setText("User already exists");
        }else{
            // CLEARS FIELDS
            ui->s1_le_password->clear();
            ui->s1_le_confirmPassword->clear();
            ui->s1_le_username->clear();
            ui->s1_le_email->clear();
            ui->s1_le_firstName->clear();
            ui->s1_le_lastName->clear();
            ui->s1_l_status->clear();
            // GOES BACK TO MAIN SCREEN
            ui->stackedWidget->setCurrentIndex(0);
            ui->s0_l_status->setText("User added successfully!");
        }
    }
}

void MainWindow::on_s3_pb_logout_clicked()
{
    // change to s_login
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_s5_pb_home_clicked()
{
    // change to s_homeScreen
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_s4_pb_add_clicked()
{
    // ADD FUNCTIONALITY
    // save user input as QString and int
    int HiveID = ui->s4_le_hiveID->text().toInt();
    QString location = ui->s4_le_hiveLocation->text();
    // we'd need to actually add to the database
    // clear user input fields
    ui->s4_le_hiveID->clear();
    ui->s4_le_hiveLocation->clear();
    // change to s_homeScreen
    ui->stackedWidget->setCurrentIndex(3);
    // display status of adding hive to database
    QString added = "Hive added. ID: ";
    added += QString::number(HiveID);
    added += " , Location: ";
    added += location;
    ui->s3_l_status->setText(added);
}

void MainWindow::on_s4_pb_cancel_clicked()
{
    // clear user input fields
    ui->s4_le_hiveID->clear();
    ui->s4_le_hiveLocation->clear();
    // change to s_homeScreen
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_s5_pb_selectHive_clicked()
{
    // change to s_hiveScreen
    ui->stackedWidget->setCurrentIndex(6);
    // ADD FUNCTIONALITY
    // this would display the current hive connected
    ui->s6_l_status->setText("no data connection, no hives");
}

void MainWindow::on_s7_pb_submitChanges_clicked()
{
    // ADD FUNCTIONALITY
    // would need to actually submit changes to the database
    // save user input as QString
    QString updatedLocation = ui->s7_le_updateLocation->text();
    ui->s7_le_updateLocation->clear();
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_s8_pb_back_clicked()
{
    // change to s_hiveScreen
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_s6_pb_viewData_clicked()
{
    // change to s_hiveData
    ui->stackedWidget->setCurrentIndex(8);
    // need to add beechimes(nullptr, hiveID) here
    // unsure what to do...
}

void MainWindow::on_s6_pb_editHive_clicked()
{
    // change to s_editHive
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_s6_pb_back_clicked()
{
    // change to s_findHive
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_s3_pb_beeChimes_clicked()
{
    int increment = 1000 * (pow(2, ui->s3_hs_increment->value()));
    double scale = pow(2, ui->s3_hs_scale->value());
    float pSimVal = ui->s3_hs_pSimPlayed->value();
    float pSimPlayed = pSimVal / 100;
    std::cout << "pSimPlayed: " << pSimPlayed << std::endl;
    // NEED TO CHANGE
    std::cout << "pSimPlayed: " << pSimPlayed << std::endl;
    bc = new BeeChimes(nullptr, QString::fromStdString(hiveDB->get_name()), hiveDB, scale, increment, pSimPlayed);
    connect(bc, SIGNAL(backClicked()), this, SLOT(receivedBackClicked()));
    ui->stackedWidget->insertWidget(4, bc);
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::receivedBackClicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->stackedWidget->removeWidget(bc);
    old_bcs.push_back(bc);
}

//CHLOE, PLEASE CHECK THIS
void MainWindow::on_s1_pb_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_s3_pb_beeAlerts_clicked()
{
    Alert al;
    // Absolute paths
//    std::string abs_path = "/Users/ricdonati/desktop/build-qtrepo_grp00_may-Desktop_Qt_5_12_0_clang_64bit-Debug/CustomerGUI/";
//    std::string file_name = abs_path + currentUser->getUserName() + ".txt";

    std::string path = "../../../";
    std::string file_name = path + currentUser->getUserName() + ".txt";

    ifstream file;
    file.open(file_name);

    std::string first;
    getline(file, first);
    al.da = new DataAnalyzer(new UDPMessageData(first)); //makes new data analyzer for first line
    getline(file, first);
    al.da = new DataAnalyzer(new UDPMessageData(first)); //makes new data analyzer for first line
    for(std::string line; getline(file, line);){ //read every other line
        if(!al.stopped) {
           al.addUDPMessage(line); //adds every udp message
        }

    }
}

void MainWindow::on_s3_pb_viewCurrentWeather_clicked()
{
    ww = new WeatherWidg();
    connect(ww, SIGNAL(backClicked()), this, SLOT(receivedBackClickedWeather()));
    ui->stackedWidget->insertWidget(5, ww);
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::receivedBackClickedWeather()
{
    old_wws.push_back(ww);
    ui->stackedWidget->removeWidget(ww);
    ui->stackedWidget->setCurrentIndex(3);
}
