#include "usertable.h"

UserTable::UserTable()
{
}

// Constructor for identying the dbtool and table name.
UserTable::UserTable(DBTool     *db,
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

UserTable::~UserTable() {
    drop(); //since were testing, create a new DB every time
}

void UserTable::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}

void UserTable::store_create_sql() {

    //std::cerr << "calling store_create_sql from UserTable\n";

    sql_create =  "CREATE TABLE IF NOT EXISTS ";
    sql_create += table_name;
    sql_create += "(";
    sql_create += "userID INTEGER PRIMARY KEY AUTOINCREMENT, ";
    sql_create += "email TEXT NOT NULL UNIQUE, ";
    sql_create += "firstName TEXT NOT NULL, ";
    sql_create += "lastName TEXT NOT NULL, ";
    sql_create += "userName TEXT NOT NULL UNIQUE, ";
    sql_create += "passwordHash INTEGER NOT NULL";
    sql_create += ");";

}

/**
 * @brief UserTable::add_row Adds a user to the table
 * @param email Email
 * @param firstName First Name
 * @param lastName  Last Name
 * @param userName  Username (must be unique)
 * @param password (will be converted to hash)
 * @return
 */
bool UserTable::add_row(std::string email, std::string firstName, std::string lastName, std::string userName, std::string password) {

    int   retCode = 0;
    char *zErrMsg = 0;

    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " (userID, email, firstName, lastName, userName, passwordHash) ";
    sql_add_row += "VALUES (";

    sql_add_row += "null";
    sql_add_row += ", ";
    sql_add_row += "\"";
    sql_add_row += std::string(email);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(firstName);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(lastName);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += std::string(userName);
    sql_add_row += "\", ";

    //Hashes that password
    std::hash<std::string> h;
    sql_add_row += std::to_string(h(password));
    sql_add_row += " );";

    retCode = sqlite3_exec(curr_db->db_ref(), sql_add_row.c_str(), cb_add_row, this, &zErrMsg);
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
 * @brief UserTable::check_credentials Checks whether a username and password match
 * @param username Username
 * @param password Password
 * @return True if they do, false if they don't
 */
bool UserTable::check_credentials(std::string username, std::string password){

    long   retCode = 0;
    char *zErrMsg = 0;

    std::string sql_get_username = "SELECT passwordHash FROM users WHERE username = \"" + username + "\";";
    retCode = sqlite3_exec(curr_db->db_ref(), sql_get_username.c_str(), cb_check_credentials, this, &zErrMsg);

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;
        sqlite3_free(zErrMsg);
        return false;
    }
    std::hash<std::string> h;
    if(this->globalPasswordHash == std::to_string(h(password))){
        globalPasswordHash = "";
        std::cout << "User Exists" << std::endl;
        return true;
    }else{
        globalPasswordHash = "";
        std::cout << "User Does NOT Exist" << std::endl;
        return false;
    }
}

bool UserTable::select_all() {
    int   retCode = 0;
    char *zErrMsg = 0;
    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";
    retCode = sqlite3_exec(curr_db->db_ref(), sql_select_all.c_str(), cb_select_all, this, &zErrMsg);
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

void UserTable::setGlobalPasswordHash(std::string n){
    globalPasswordHash = n;
}

User* UserTable::get_user(std::string userName){
    int   retCode = 0;
    char *zErrMsg = 0;
    sql_select_all  = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += " WHERE userName = \"";
    sql_select_all += userName;
    sql_select_all += "\";";

    retCode = sqlite3_exec(curr_db->db_ref(), sql_select_all.c_str(), cb_get_user, this, &zErrMsg);
    if( retCode != SQLITE_OK ){
        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }
    return this->u;
}

//--------------------------------CALLBACKS--------------------------------
int cb_add_row(void *data, int argc, char **argv, char **azColName){
    std::cerr << "cb_add_row being called\n";
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }
    int i;
    UserTable *obj = (UserTable *) data;
    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;
    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                  << " = "
                  <<  (argv[i] ? argv[i] : "NULL")
                  << std::endl;
    }
    return 0;
}

/**
 * @brief cb_check_credentials Sets the instance vatiable, globalPasswordHash, so that it can be accessed later
 * @param data
 * @param argc
 * @param argv
 * @param azColName
 * @return
 */
int cb_check_credentials(void *data, int argc, char **argv, char **azColName){
    std::cerr << "cb_select_all being called\n";
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }
    UserTable *obj = (UserTable *) data;
    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;
    obj->globalPasswordHash = argv[0];
    return 0;
}

int cb_check(void *data, int argc, char **argv, char **azColName){
    std::cerr << "cb_select_all being called\n";
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }
    int i;
    UserTable *obj = (UserTable *) data;
    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;
    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                  << " = "
                  <<  (argv[i] ? std::string(argv[i]) : "NULL")
                  << std::endl;
    }
    return 0;
}

int cb_select_all(void *data, int argc, char **argv, char **azColName){
    std::cerr << "cb_select_all being called\n";
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }
    int i;
    UserTable *obj = (UserTable *) data;
    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;
    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                  << " = "
                  <<  (argv[i] ? std::string(argv[i]) : "NULL")
                  << std::endl;
    }
    return 0;
}

int cb_get_user(void *data, int argc, char **argv, char **azColName){
    std::cerr << "cb_select_all being called\n";
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }
    int i;
    UserTable *obj = (UserTable *) data;
    std::cout << "------------------------------\n";
    for(i = 0; i < argc; i++){
        obj->u = new User(std::stoi(argv[0]), argv[2], argv[3], argv[1], argv[4], std::stol(argv[5]));
    }
    return 0;
}
