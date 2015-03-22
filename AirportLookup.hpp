#pragma once

#include "Data/Airport.hpp"

using namespace std;

class AirportLookup {

public:

    AirportLookup();
    Airport* getAirport(string airportCode);

private:

    void run();
};
