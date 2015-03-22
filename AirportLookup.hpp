#pragma once

#include "Data/Airport.hpp"
#include "FlightManager.hpp"

using namespace std;

class AirportLookup {

public:

    AirportLookup(FlightManager &flightManager);
    void run();
private:

    FlightManager &flightManager;
    Airport *selectedAirport;
    void selectAirport();

    int getAirportView();
    int getSelection();
    void displayAirportInfo();
    void printOptions();
};