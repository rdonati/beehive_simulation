#include "messagetable.h"
#include "dbtableex.h"

MessageTable::MessageTable()
{

}

// Constructor for identying the dbtool and table name.
MessageTable::MessageTable(DBTool     *db,
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

MessageTable::~MessageTable() {
    std::cout << "Table name: " << table_name << std::endl;
    drop(); //since were testing, create a new DB every time
}


void MessageTable::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}


void MessageTable::store_create_sql() {

    //std::cerr << "calling store_create_sql from MessageTable\n";

    sql_create =  "CREATE TABLE IF NOT EXISTS ";
    sql_create += table_name;
    sql_create += "(";
    sql_create += "id INTEGER PRIMARY KEY AUTOINCREMENT, ";
    sql_create += "message TEXT NOT NULL";
    sql_create += ");";

}


bool MessageTable::add_row(std::string s) {
    int   retCode = 0;
    char *zErrMsg = 0;

    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " (id, message) ";
    sql_add_row += "VALUES (";

    sql_add_row += "null";
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += std::string(s);
    sql_add_row += "\"";

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


bool MessageTable::select_all() {

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

/**
 * @brief MessageTable::get_messages Retrieves the n most recent UDP messages from the DB
 * @param n Number of elements to retrieve
 * @return A vector of the most recent n UDP messages
 */
std::vector<std::string> MessageTable::get_messages(int n){
    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += " ORDER BY id DESC LIMIT ";
    sql_select_all += std::to_string(n);
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           cb_get_messages,
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
    return this->selectedMessages;
}

void MessageTable::populate(std::string fName){
    std::ifstream file(fName);
    for(std::string line; getline(file, line);){
        this->add_row(line);
    }
}

//-------------------CALLBACKS--------------------

int cb_get_messages(void *data, int argc, char **argv, char **azColName){
    std::cerr << "cb_select_all being called\n";
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }
    MessageTable *obj = (MessageTable *) data;
    int i;
    for(i = 1; i < argc; i+=2){
        if(argv[i]){
            obj->selectedMessages.push_back(argv[i]);
            std::cout << "Message " << + atoi(argv[i - 1]) << ": " << argv[i] << std::endl;
        }
    }
    return 0;
}
