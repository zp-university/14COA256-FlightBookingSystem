//
// Created by zack on 22/03/15.
//

#include <iostream>
#include <iomanip>
#include "AirportLookup.hpp"
#include "ConsoleHandler.hpp"

AirportLookup::AirportLookup(FlightManager &flightManager)
        :flightManager(flightManager) {
}

void AirportLookup::run() {

    while(selectedAirport == nullptr) {

        selectAirport();
    }
}

void AirportLookup::selectAirport() {

    cout << "Please type the code of the airport you want to view: ";

    Airport* airport = flightManager.getAirport(getInput());

    if(airport != nullptr) {

        selectedAirport = airport;
    } else {

        cout << "The airport you specified could not be found." << endl;
    }
}

int AirportLookup::getAirportView() {

    int selection = 0;

    while((selection = getSelection()) != 3) {

        switch(selection) {

            case 1: {
                TripCreator tripCreator(flightManager);
                tripCreator.run();
                break;
            }
            case 2: {
                AirportLookup airportLookup();
                airportLookup().run();
                break;
            }
            default:

                cout << "Unknown Selection." << endl;
        }

        cout << endl << "Returning to menu." << endl;
    }

    cout << endl << "Exiting!";
}

void AirportLookup::printOptions() {

    cout << left << setw(5) << "1.)" << setw(30) << "Book a Flight." << endl;
    cout << left << setw(5) << "2.)" << setw(30) << "View Airport Information." << endl;
    cout << left << setw(5) << "3.)" << setw(30) << "Quit." << endl;
}

int AirportLookup::getSelection() {

    printOptions();
    cout << "Please enter your selection: ";
    return getInt();
}

void AirportLookup::displayAirportInfo() {


}