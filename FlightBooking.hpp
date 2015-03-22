#pragma once
#include "Data/Flight.hpp"
#include "Data/Airport.hpp"
#include <vector>

using namespace std;

class FlightBooking {

    public:

        FlightBooking();

        void addFlight(Flight &flight);
        void addAirport(Airport &airport);
		Airport* getAirport(string airportCode);
        vector<Flight*>& getFlights();
        vector<Airport*>& getAirports();
    private:

        vector<Flight*> flights;
        vector<Airport*> airports;

        void loadFlights();
        void loadAirports();
};