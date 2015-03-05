#pragma once
#include <string>

using namespace std;

class Airport {

    public:

        Airport(string &airportCode, string &airportName, int &departureTax, int &connectionTime);

        string getAirportCode();
        string getAirportName();
        int getDepartureTax();
        int getConnectionTime();
    private:

        string airportCode;
        string airportName;
        int departureTax;
        int connectionTime;
};