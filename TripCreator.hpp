#pragma once
#include <vector>
#include <iostream>
#include "Date.hpp"
#include "FlightManager.hpp"
#include "Trip.hpp"

using namespace std;

class TripCreator {

    public:

        TripCreator(FlightManager &flightBooking);
		~TripCreator();
        void run();
    private:

        void requestOrigin();
        void requestDestination();
        void requestDate();
        void search();

        Trip* chosenTrip;
        vector<Trip*> possibleTrips;

        FlightManager &flightManager;

        string origin, destination;
        Date date;

    void selectTrip();

    bool confirmTicket();

    void printReceipt();

    void printTicketOptions();

    void printTripSelectionOptions();

    void displayPage(int page);
};