#include "TripCreator.hpp"

TripCreator::TripCreator() {

    requestOrigin();
    requestDestination();
    requestDate();

    cout << "Origin: " << "\t\t" << origin << endl;
    cout << "Destination: " << "\t\t" << destination << endl;
    cout << "Date: " << "\t\t" << date.getDateString().c_str() << endl;
}

void TripCreator::requestOrigin() {

    cout << "Enter Origin: " << flush;
    string input = getInput();
    if(input.length() != 3) {

        cout << "Invalid airport code!" << endl;
    }

    origin = input;
}

void TripCreator::requestDestination() {

    cout << "Enter Destination: " << flush;
    string input = getInput();
    if(input.length() != 3) {

        cout << "Invalid airport code!" << endl;
    }

    destination = input;
}

void TripCreator::requestDate() {

    cout << "Enter Journey Date: " << flush;
    date = getDate();
}