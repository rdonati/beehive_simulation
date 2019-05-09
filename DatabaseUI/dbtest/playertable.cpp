#include "playertable.h"
#include "dbtableex.h"

PlayerTable::PlayerTable()
{

}

// Constructor for identying the dbtool and table name.
PlayerTable::PlayerTable(DBTool     *db,
                     std::string name   ) :
    DBTable (db, name)
{

    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

PlayerTable::~PlayerTable() {
drop(); //since were testing, create a new DB every time
}

void PlayerTable::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}


void PlayerTable::store_create_sql() {

    //std::cerr << "calling store_create_sql from DBTableEx\n";

    sql_create =  "CREATE TABLE ";
    sql_create += table_name;
    sql_create += " ( ";
    sql_create += "  id INT PRIMARY KEY NOT NULL, ";
    sql_create += "  firstname TEXT NOT NULL, ";
    sql_create += "  lastname TEXT NOT NULL, ";
    sql_create += "  address TEXT NOT NULL, ";
    sql_create += "  gameid INT NOT NULL";
    sql_create += " );";

}


bool PlayerTable::add_row(int id, std::string firstname,
                        std::string lastname, std::string address,
                        int gameid) {
    int   retCode = 0;
    char *zErrMsg = 0;

    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " ( id, firstname, lastname, address, gameid ) ";
    sql_add_row += "VALUES (";

    sprintf (tempval, "%d", id);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += std::string(firstname);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(lastname);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(address);
    sql_add_row += "\", ";

    sprintf (tempval, "%d", gameid);
    sql_add_row += tempval;
    sql_add_row += "";

    sql_add_row += " );";

    //std::cout << sql_add_row << std::endl;

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_add_row.c_str(),
                           cb_add_row,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

bool PlayerTable::select_all() {

    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           cb_select_all,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}
