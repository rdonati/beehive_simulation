#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // print its state
    dbtool = new DBTool("hiveDB");
    mtable = new MessageTable(dbtool, "messages");
    dbtool->print(std::cout);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    dbtool->detach();
    //mtable->drop();
}

void MainWindow::on_add_clicked()
{
    std::string message = ui->message->text().toStdString();
    mtable->add_row(message);
    ui->message->setText("");
}

void MainWindow::on_actionAdd_New_User_triggered()
{
    CreateUserScreen cus(this);
    cus.setModal(true);
    cus.exec();
}

void MainWindow::on_view_database_clicked()
{
    mtable->select_all();
}

void MainWindow::on_get_clicked()
{
    int numToGet = std::stoi(ui->num_to_retrieve->text().toStdString());
    mtable->get_messages(numToGet);
}
