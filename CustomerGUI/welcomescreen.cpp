#include "welcomescreen.h"
#include "ui_welcomescreen.h"

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);
    ui->label_2->setText(" \n Created by Chloe Dorward, Jack Krase, Ric Donati, Sean Trezza, and Seth Markarian \n \n Instructions: \n 1. Create a new user and log in. Creating a user will take about five seconds because it is generating data. \n 2. The alert option analyzes the data and pops up an alert each time an event (a swarm or a raid) is detected. \n 3. The weather button shows the current weather. \n 4. The hive chimes will play a musical interpretation of the data. \n \n This interface was made for Circle of Bees, a company which makes a product called HiveChimes. HiveChimes tracks movement of bees in and out of the hive. We have catered to hive owners and artists. Once logged in, a user can receive alerts about when their bees swarmed out of their hive, or were robbed by another colony. The user can also listen to a musical interpretation of the bees moving in and out of the hive.\nSources:\nMusic: University of Iow Electronic Music Studios\nWeather: Dark Sky API");
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}
