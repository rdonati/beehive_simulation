#include "robalertui.h"
#include "ui_robalertui.h"

/**
 * @brief RobAlertUI::RobAlertUI
 * Dialog that displays information about Rob
 *
 * @param parent
 */
RobAlertUI::RobAlertUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RobAlertUI)
{
    ui->setupUi(this);
    //stopped = false;
}

/**
 * @brief RobAlertUI::~RobAlertUI
 * Destructor for RobAlert Window
 */
RobAlertUI::~RobAlertUI()
{
    delete ui;
}

/**
 * @brief RobAlertUI::on_CloseButton_clicked
 * Close the window when the "close" button is clicked by user
 */
void RobAlertUI::on_CloseButton_clicked()
{
    close();
}

/**
 * @brief RobAlertUI::setHiveID
 * Sets the HiveID on the alert window
 *
 * @param _HiveID current HiveID
 */
void RobAlertUI::setHiveID(std::string _HiveID)
{
    ui->HiveID->setText(QString::fromStdString(_HiveID));
}

/**
 * @brief RobAlertUI::setDate
 * Sets the date of the rob on the alert window
 *
 * @param hd HiveDate that holds days, months, and years
 */
void RobAlertUI::setDate(HDate hd)
{
    std::string date;
    date += std::to_string(hd.get_month()) + "/" + std::to_string(hd.get_day()) + "/" + std::to_string(hd.get_year());
    ui->Date->setText(QString::fromStdString(date));
}

/**
 * @brief RobAlertUI::setTime
 * Sets the time of the rob on the alert window
 *
 * @param ht HiveTime that holds hours, minutes, and milliseconds
 */
void RobAlertUI::setTime(HTime ht)
{
    std::string time = ht.format();
    ui->Time->setText(QString::fromStdString(time));
}

void RobAlertUI::on_StopButton_clicked()
{
    stopped = true;
    close();
}

bool RobAlertUI::getStopped()
{
    return stopped;
}
