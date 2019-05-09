#ifndef MESSAGETABLE_H
#define MESSAGETABLE_H

#include <iostream>
#include <string>
//#include <sqlite3.h>
#include "../sqlite-amalgamation-3280000/sqlite3.h"
#include <fstream>

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

#include "dbtool.h"
#include "dbtable.h"

class MessageTable: public DBTable
 {
        protected:

            std::string sql_select_all;

        public:
            std::vector<std::string> selectedMessages;
            MessageTable();
            MessageTable(DBTool     *db,
                      std::string name);
            ~MessageTable();

            // An overloaded method to generate a new
            // create command for your child class.
            void store_create_sql();

            // An overloaded method to generate a new
            // insert command for your child class.
            virtual void store_add_row_sql();

            bool add_row(std::string message);
            std::vector<std::string> get_messages(int n);
            bool select_all();
            void populate(std::string fName);
};

int cb_get_messages(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

#endif // MESSAGETABLE_H
