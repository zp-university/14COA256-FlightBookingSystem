#include <string>
#include "Airport.hpp"

Airport::Airport(string &airportCode, string &airportName, int &departureTax, int &connectionTime) {

    this->airportCode = airportCode;
    this->airportName = airportName;
    this->departureTax = departureTax;
    this->connectionTime = connectionTime;
}

string Airport::getAirportCode() {

    return airportCode;
}

string Airport::getAirportName() {

    return airportName;
}

int Airport::getDepartureTax() {

    return departureTax;
}

int Airport::getConnectionTime() {

    return connectionTime;
}
