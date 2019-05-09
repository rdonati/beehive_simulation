#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "./dbtest/dbtable.h"
#include "./dbtest/dbtableex.h"
#include "./dbtest/dbtool.h"
#include "./dbtest/messagetable.h"
#include "createuserscreen.h"
#include "sqlite-amalgamation-3280000/sqlite3.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_clicked();

    void on_actionAdd_New_User_triggered();

    void on_view_database_clicked();

    void on_get_clicked();

private:
    // generate database object
    DBTool *dbtool;
    // generate a new table
    MessageTable *mtable;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
