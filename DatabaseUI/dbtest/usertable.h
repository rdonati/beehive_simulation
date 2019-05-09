#ifndef USERTABLE_H
#define USERTABLE_H

#include <iostream>
#include <string>
//#include <sqlite3.h>
#include "../sqlite-amalgamation-3280000/sqlite3.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "dbtool.h"
#include "dbtable.h"
#include "../user.h"

class UserTable: public DBTable
 {
        protected:

            std::string sql_select_all;
        public:

            std::string globalUsername;
            std::string globalPasswordHash;
            void setGlobalPasswordHash(std::string n);
            User *u;

            UserTable();
            UserTable(DBTool     *db,
                      std::string name);

            ~UserTable();

            // An overloaded method to generate a new
            // create command for your child class.
            void store_create_sql();

            // An overloaded method to generate a new
            // insert command for your child class.
            virtual void store_add_row_sql();

            bool add_row(std::string email, std::string firstName, std::string lastName, std::string userName, std::string password);
            bool check_credentials(std::string username, std::string password);
            bool select_all();
            User* get_user(std::string userName);
            User* get_user(int id);
};

// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_add_row(void  *data,
               int    argc,
               char **argv,
               char **azColName);


// This is a callback function that is sent to the library and used
// to parse the sql request being sent to the database.
int cb_check_credentials(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

int cb_select_all(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

int cb_check_credentials(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

int cb_get_user(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName);

#endif // USERTABLE_H
