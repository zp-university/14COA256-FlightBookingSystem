#pragma once
#include <string>

using namespace std;

class Flight {

    public:

        Flight(string originAirportCode, string destinationAirportCode, string airline, int price, int duration);

        string getOriginAirportCode();
        string getDestinationAirportCode();
        string getAirline();
        int getPrice();
        int getDuration();
    private:

        string originAirportCode;
        string destinationAirportCode;
        string airline;
        int price;
        int duration;
};