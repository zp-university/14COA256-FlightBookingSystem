#pragma once
#include <vector>
#include <iostream>
#include "Data/Flight.hpp"
#include "ConsoleHandler.hpp"
#include "Date.hpp"

using namespace std;

class TripCreator {

    public:

        TripCreator();
    private:

        void requestOrigin();
        void requestDestination();
        void requestDate();

        vector <Flight*> chosenTrip;

        string origin, destination;
        Date date;
};