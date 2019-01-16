#include "DBentry.h"

DBentry::DBentry() {
    //the default constructor
}

//constructor with data passed in
DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active) {
    this -> name = _name;
    this -> IPaddress = _IPaddress;
    this -> active = _active;
}

DBentry::~DBentry() {
    //destructor
}

// sets the domain name, which we will use as a key.
void DBentry::setName(string _name) {
    this -> name = _name;
}

// sets the IPaddress data.
void DBentry::setIPaddress (unsigned int _IPaddress) {
    this -> IPaddress = _IPaddress;
}

// sets whether or not this entry is active.
void DBentry::setActive(bool _active) {
    this -> active = _active;
}

// returns the name.
string DBentry::getName() const {
    return name;
}

// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const {
    return IPaddress;
}

// returns whether or not this entry is active.
bool DBentry::getActive() const {
    return active;
}

// prints the entry in the format 
// name : IPaddress : active  followed by newline
// active is printed as a string (active or inactive)
ostream& operator<< (ostream& out, const DBentry& rhs) {
    if (rhs.active)
        out << rhs.name << " : " << rhs.IPaddress << " : active" << endl;
    else
        out << rhs.name << " : " << rhs.IPaddress << " : inactive" << endl;
    return (out);
}