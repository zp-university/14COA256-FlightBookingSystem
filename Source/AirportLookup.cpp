#include <iostream>
#include <iomanip>
#include "AirportLookup.hpp"
#include "ConsoleHandler.hpp"

AirportLookup::AirportLookup(FlightManager &flightManager)
        :flightManager(flightManager) {
}

void AirportLookup::run() {

    selectAirport();

    selectAirportView();
}

void AirportLookup::selectAirport() {

    selectedAirport = nullptr;
	departures.clear();

    while(selectedAirport == nullptr) {

        cout << endl << "Please type the code of the airport you want to view: ";

        Airport *airport = flightManager.getAirport(getInput());

        if (airport != nullptr) {

            selectedAirport = airport;
        } else {

            cout << endl << "The airport you specified could not be found." << endl;
        }
    }
}

void AirportLookup::selectAirportView() {

    int selection = 0;

    while((selection = getSelection()) != 4) {

        switch(selection) {

            case 1:
                displayAirportInfo();
                continue;
            case 2:
                displayAirportFlights();
                continue;
            case 3:
                selectAirport();
                continue;
            default:

                cout << "Unknown Selection." << endl;
        }

        cout << endl << "Returning to menu." << endl;
    }

    cout << endl << "Exiting!";
}

void AirportLookup::printOptions() {

    cout << endl << left << "Currently Selected Airport: " << selectedAirport->getAirportName() << endl << endl;

    cout << left << setw(5) << "1.)" << setw(30) << "View Airport Info." << endl;
    cout << left << setw(5) << "2.)" << setw(30) << "View Flights From Airport." << endl;
    cout << left << setw(5) << "3.)" << setw(30) << "Select Different Airport." << endl;
    cout << left << setw(5) << "4.)" << setw(30) << "Back to Main Menu." << endl;
}

int AirportLookup::getSelection() {

    printOptions();
    cout << endl << "Please enter your selection: ";
    return getInt();
}

void AirportLookup::displayAirportInfo() {

    cout << endl << left << setw(30) << "Airport Name: " << selectedAirport->getAirportName() << endl;
    cout << left << setw(30) << "Airport Code: " << selectedAirport->getAirportCode() << endl;
    cout << left << setw(30) << "Airport Departure Tax: " << selectedAirport->getDepartureTax() << endl;
    cout << left << setw(30) << "Airport Connection Time: " << selectedAirport->getConnectionTime() << endl;

    waitForEnter("Press Enter to Continue...");
}

void AirportLookup::displayAirportFlights() {

    if(departures.empty()) {

        for(Flight *flight : flightManager.getFlights()) {

            if (flight->getOriginAirportCode() == selectedAirport->getAirportCode()) {

                departures.push_back(flight);
            }
        }
    }

    if(!departures.empty()) {

        cout << endl << left << setw(15) << "Destination" << setw(30) << "Airline" << setw(10) << "Price" << setw(15) << "Duration" << endl;

        for(Flight *flight : departures) {

            cout << left << setw(15) << flight->getDestinationAirportCode() << setw(30) << flight->getAirline() << setw(10) << flight->getPrice() << setw(15) << flight->getDuration() << endl;
        }
    } else {

        cout << "No flights were found departing from this airport.";
    }

    waitForEnter("Press enter to continue...");
}