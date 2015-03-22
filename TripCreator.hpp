#pragma once
#include <vector>
#include <iostream>
#include "Data/Flight.hpp"
#include "ConsoleHandler.hpp"
#include "Date.hpp"
#include "FlightManager.hpp"

using namespace std;

class TripCreator {

    public:

        TripCreator(FlightManager &flightBooking);
        void run();
    private:

        void requestOrigin();
        void requestDestination();
        void requestDate();
        void search();

        vector <Flight*> chosenTrip;
        vector<vector<Flight*>> possibleTrips;

        FlightManager &flightBooking;

        string origin, destination;
        Date date;

    void selectTrip();
};