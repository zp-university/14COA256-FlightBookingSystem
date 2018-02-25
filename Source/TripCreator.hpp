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

            PriceAscending,
            PriceDescending,
            DurationAscending,
            DurationDescending
        };

        void requestOrigin();
        void requestDestination();
        void requestDate();
        void search();
		void selectTrip();
		void printReceipt();
		void printTicketOptions();
		void printTripSelectionOptions();
		void printTripSortingOptions();
		void displayPage(int page);
		void storeTrip(Trip *trip);
		void changeSortingType();
		void runVectorReverse();
		bool confirmTicket();
		vector<Trip *> &getVectorBySortingType();

        Trip* chosenTrip;

        vector<Trip*> possibleTripsSortedByPrice;
        vector<Trip*> possibleTripsSortedByDuration;

        SortingMethod sortingMethod = SortingMethod::PriceAscending;

        FlightManager &flightManager;

        string origin, destination;

        Date date;

        int currentPage;
};