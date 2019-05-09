#include "swarmalertui.h"
#include "ui_swarmalertui.h"

/**
 * @brief SwarmAlertUI::SwarmAlertUI
 * Dialog that displays information about Swarm
 *
 * @param parent
 */
SwarmAlertUI::SwarmAlertUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SwarmAlertUI)
{
    ui->setupUi(this);
    stopped = false;
}

/**
 * @brief SwarmAlertUI::~SwarmAlertUI
 * Destructor for SwarmAlert Window
 */
SwarmAlertUI::~SwarmAlertUI()
{
    delete ui;
}

/**
 * @brief SwarmAlertUI::on_CloseButton_clicked
 * Close the window when the "close" button is clicked by user
 */
void SwarmAlertUI::on_CloseButton_clicked()
{
    close();
}

/**
 * @brief SwarmAlertUI::setHiveID
 * Sets the HiveID on the alert window
 *
 * @param _HiveID current HiveID
 */
void SwarmAlertUI::setHiveID(std::string _HiveID)
{
    ui->HiveID->setText(QString::fromStdString(_HiveID));
}

/**
 * @brief SwarmAlertUI::setDate
 * Sets the date of the swarm on the alert window
 *
 * @param hd HiveDate that holds days, months, and years
 */
void SwarmAlertUI::setDate(HDate hd)
{
    std::string date;
    date += std::to_string(hd.get_month()) + "/" + std::to_string(hd.get_day()) + "/" + std::to_string(hd.get_year());
    ui->Date->setText(QString::fromStdString(date));
}

/**
 * @brief SwarmAlertUI::setTime
 * Sets the time of the swarm on the alert window
 *
 * @param ht HiveTime that holds hours, minutes, and milliseconds
 */
void SwarmAlertUI::setTime(HTime ht)
{
    std::string time = ht.format();
    ui->Time->setText(QString::fromStdString(time));
}

bool SwarmAlertUI::getStopped()
{
    return stopped;
}

void SwarmAlertUI::on_StopButton_clicked()
{
    stopped = true;
    close();
}
