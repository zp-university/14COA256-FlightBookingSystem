#pragma once
#include <vector>
#include <iostream>
#include "Data/Flight.hpp"
#include "ConsoleHandler.hpp"
#include "Date.hpp"
#include "FlightBooking.hpp"

using namespace std;

class TripCreator {

    public:

        TripCreator(FlightBooking *flightBooking);
    private:

        void requestOrigin();
        void requestDestination();
        void requestDate();
        void search();

        vector <Flight*> chosenTrip;
        vector<vector<Flight*>> possibleTrips;

        FlightBooking &flightBooking;

        string origin, destination;
        Date date;

    void selectTrip();
};