#include <string>
#include "Flight.hpp"

Flight::Flight(string originAirportCode, string destinationAirportCode, string airline, int price, int duration) {

    this->originAirportCode = originAirportCode;
    this->destinationAirportCode = destinationAirportCode;
    this->airline = airline;
    this->price = price;
    this->duration = duration;
}

string Flight::getOriginAirportCode() {

    return originAirportCode;
}

string Flight::getDestinationAirportCode() {

    return destinationAirportCode;
}

string Flight::getAirline() {

    return airline;
}

int Flight::getPrice() {

    return price;
}

int Flight::getDuration() {

    return duration;
}
