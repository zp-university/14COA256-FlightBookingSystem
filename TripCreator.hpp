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

        enum SortingMethod {

            PriceAscending = 1,
            PriceDescending = 2,
            DurationAscending = 3,
            DurationDescending = 4
        };

        void requestOrigin();
        void requestDestination();
        void requestDate();
        void search();

        Trip* chosenTrip;
        vector<Trip*> possibleTripsSortedByPrice;
        vector<Trip*> possibleTripsSortedByDuration;

        SortingMethod sortingMethod = SortingMethod::PriceAscending;

        FlightManager &flightManager;

        string origin, destination;
        Date date;

    void selectTrip();

    bool confirmTicket();

    void printReceipt();

    void printTicketOptions();

    void printTripSelectionOptions();

    void displayPage(int page);

    void storeTrip(Trip *trip);

    void printTripSortingOptions();
};