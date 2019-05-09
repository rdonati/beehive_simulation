#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
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
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string get_string();
    int get_temp_int();
    std::string get_content_between(std::string bigString, std::string str1, std::string str2);
private:
    int tempInt;
    Ui::MainWindow *ui;
    QNetworkAccessManager *mng;
    QNetworkRequest request;
    std::string readBuffer;

private slots:
    void mng_finished(QNetworkReply *reply);
    void on_pushButton_clicked();
    void on_exitButton_clicked();
};

#endif // MAINWINDOW_H

