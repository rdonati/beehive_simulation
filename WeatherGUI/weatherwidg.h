#ifndef WEATHERWIDG_H
#define WEATHERWIDG_H

#include <QWidget>
#include <QtDebug>
#include <QObject>
#include <QObject>
#include <QString>
#include <iostream>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <sstream>
#include <ctime>
#include <chrono>

namespace Ui {
class WeatherWidg;
}

class WeatherWidg : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherWidg(QWidget *parent = nullptr);
    ~WeatherWidg();
    int get_temp_int();
    std::string get_content_between(std::string bigString, std::string str1, std::string str2);
signals:
    void backClicked(); // signal that back has been clicked

private:
    int tempInt;
    Ui::WeatherWidg *ui;
    QNetworkAccessManager *mng;
    QNetworkRequest request;
    std::string readBuffer;

private slots:
    void mng_finished(QNetworkReply * reply);
    void on_backButton_clicked(); // back button clicked
    void on_pushButton_clicked(); // refresh button clicked
};

#endif // WEATHERWIDG_H
