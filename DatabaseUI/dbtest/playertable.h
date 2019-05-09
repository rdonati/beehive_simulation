#ifndef PLAYERTABLE_H
#define PLAYERTABLE_H

#include <iostream>
#include <string>
#include <sqlite3.h>

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "dbtool.h"
#include "dbtable.h"

class PlayerTable: public DBTable
{
protected:

    std::string sql_select_all;

public:

    PlayerTable();
    PlayerTable(DBTool     *db,
              std::string name);

    ~PlayerTable();

    // An overloaded method to generate a new
    // create command for your child class.
    void store_create_sql();

    // An overloaded method to generate a new
    // insert command for your child class.
    virtual void store_add_row_sql();


    bool add_row(int, std::string, std::string, std::string, int);

    bool select_all();
};



#endif // PLAYERTABLE_H
