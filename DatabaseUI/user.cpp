#include "user.h"

User::User(){

}

User::User(int i, std::string fn, std::string ln, std::string e, std::string un, long ph){
    id = i;
    firstName = fn;
    lastName = ln;
    email = e;
    userName = un;
    passwordHash = ph;
}

void User::toString(){
    std::string s = "";

    s += "ID: " + std::to_string(id) + "\n";
    s += "First Name: " + firstName + "\n";
    s += "Last Name: " + lastName + "\n";
    s += "User Name: " + userName + "\n";
    s += "Email: " + email + "\n";
    s += "PasswordHash: " + std::to_string(passwordHash) + "\n";

    std::cout << s;
}

//GETTERS
int User::getId(){
    return id;
}
std::string User::getFirstName(){
    return firstName;
}
std::string User::getLastName(){
    return lastName;
}
std::string User::getEmail(){
    return email;
}
std::string User::getUserName(){
    return userName;
}
long User::getPasswordHash(){
    return passwordHash;
}

//SETTERS
void User::setId(int i){
    id = i;
}
void User::setFirstName(std::string fn){
    firstName = fn;
}
void User::setLastName(std::string ln){
    lastName = ln;
}
void User::setEmail(std::string e){
    email = e;
}
void User::setUserName(std::string un){
    userName = un;
}
void User::setPasswordHash(long ph){
    passwordHash = ph;
}
