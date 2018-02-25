#include <string>
#include "Airport.hpp"

Airport::Airport(string &airportCode, string &airportName, int &departureTax, int &connectionTime)
        : airportCode(airportCode), airportName(airportName), departureTax(departureTax), connectionTime(connectionTime) {
}

string& Airport::getAirportCode() {

    return airportCode;
}

string& Airport::getAirportName() {

    return airportName;
}

int& Airport::getDepartureTax() {

    return departureTax;
}

int& Airport::getConnectionTime() {

    return connectionTime;
}
