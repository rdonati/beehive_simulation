#ifndef CREATEUSERSCREEN_H
#define CREATEUSERSCREEN_H

#include <QDialog>
#include "./dbtest/dbtable.h"
#include "./dbtest/dbtableex.h"
#include "./dbtest/dbtool.h"
#include "./dbtest/usertable.h"
#include "sqlite-amalgamation-3280000/sqlite3.h"

namespace Ui {
class CreateUserScreen;
}

class CreateUserScreen : public QDialog
{
    Q_OBJECT

public:
    explicit CreateUserScreen(QWidget *parent = nullptr);
    ~CreateUserScreen();

private slots:
    void on_create_clicked();

    void on_show_clicked();

    void on_pushButton_clicked();

    void on_get_user_clicked();

private:
    // generate database object
    DBTool *dbtool;
    // generate a new table
    UserTable *utable;
    Ui::CreateUserScreen *ui;
};

#endif // CREATEUSERSCREEN_H
