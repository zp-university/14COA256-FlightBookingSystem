#include <iostream>
#include <iomanip>
#include "Selector.hpp"
#include "FlightBooking.hpp"
#include "AirportLookup.hpp"
#include "ConsoleHandler.hpp"

Selector::Selector() {

    int selection = 0;

    while((selection = getSelection()) != 3) {

        switch(selection) {

            case 1:
                FlightBooking();
                break;
            case 2:
                AirportLookup();
                break;
            default:

                cout << "Unknown Selection." << endl;
        }

        cout << endl << "Returning to menu." << endl;
    }

    cout << endl << "Exiting!";
}

void Selector::printSelection() {

    cout << left << setw(5) << "1.)" << setw(30) << "Book a Flight." << endl;
    cout << left << setw(5) << "2.)" << setw(30) << "View Airport Information." << endl;
    cout << left << setw(5) << "3.)" << setw(30) << "Quit." << endl;
}

int Selector::getSelection() {

    printSelection();
    cout << "Please enter your selection: ";
    return getInt();
}