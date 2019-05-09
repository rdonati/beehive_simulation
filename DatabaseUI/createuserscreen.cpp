#include "createuserscreen.h"
#include "ui_createuserscreen.h"

CreateUserScreen::CreateUserScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUserScreen)
{
    // print its state
    dbtool = new DBTool("hiveDB");
    utable = new UserTable(dbtool, "users");
    dbtool->print(std::cout);
    ui->setupUi(this);
}

CreateUserScreen::~CreateUserScreen()
{
    delete ui;
    utable->drop();
}

void CreateUserScreen::on_create_clicked()
{
    std::string firstName = ui->firstName->text().toStdString();
    std::string lastName = ui->lastName->text().toStdString();
    std::string userName = ui->userName->text().toStdString();
    std::string email = ui->email->text().toStdString();
    std::string password = ui->passwordHash->text().toStdString();
    utable->add_row(email, firstName, lastName, userName, password);
    ui->firstName->setText("");
    ui->lastName->setText("");
    ui->userName->setText("");
    ui->email->setText("");
    ui->passwordHash->setText("");
}

void CreateUserScreen::on_show_clicked()
{
    utable->select_all();
}

void CreateUserScreen::on_pushButton_clicked()
{
    utable->check_credentials("username", "mypassword");
}

void CreateUserScreen::on_get_user_clicked()
{
    std::string name = ui->userNameToFind->text().toStdString();
    User *temp = utable->get_user(name);
    temp->toString();
}
