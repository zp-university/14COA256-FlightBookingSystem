//
// Created by zack on 22/03/15.
//

#include <bits/stringfwd.h>
#include "AirportLookup.hpp"
#include "Data/Airport.hpp"
#include "ConsoleHandler.hpp"

AirportLookup::AirportLookup() {

    run();
}

void AirportLookup::run() {

    Airport* airport = getAirport(getInput());

    if(airport != nullptr) {


    }
}

Airport* AirportLookup::getAirport(string airportCode) {



    return nullptr;
}