#ifndef USER_H
#define USER_H

#include <iostream>
#include "sqlite-amalgamation-3280000/sqlite3.h"

class User
{
private:
    int id;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string userName;
    long passwordHash;
public:
    User();
    User(int i, std::string fn, std::string ln, std::string e, std::string un, long ph);

    void toString();

    int getId();
    std::string getFirstName();
    std::string getLastName();
    std::string getEmail();
    std::string getUserName();
    long getPasswordHash();

    void setId(int i);
    void setFirstName(std::string fn);
    void setLastName(std::string ln);
    void setEmail(std::string e);
    void setUserName(std::string un);
    void setPasswordHash(long ph);
};

#endif // USER_H
