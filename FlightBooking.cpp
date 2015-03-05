#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "FlightBooking.hpp"
#include "TripCreator.hpp"

FlightBooking::FlightBooking() {

    loadFlights();
    loadAirports();

    TripCreator();

    /**

    for(Airport &airport : airports) {

        cout << airport.getAirportCode() << "\t\t" << airport.getAirportName() << "\t\t" << airport.getDepartureTax() << "\t\t" << airport.getConnectionTime() << endl;
    }

    for(Flight &flight : flights) {

        cout << flight.getOriginAirportCode() << "\t\t" << flight.getDestinationAirportCode() << "\t\t" << flight.getAirline() << "\t\t" << flight.getPrice() << "\t\t" << flight.getDuration() << endl;
    }

    **/
}

void FlightBooking::addFlight(Flight flight) {

    flights.push_back(flight);
}

void FlightBooking::addAirport(Airport airport) {

    airports.push_back(airport);
}

void FlightBooking::loadFlights() {

    ifstream file("flights.txt");
    string line;

    while (getline(file, line, '\n')) {

        istringstream lineStream(line);
        string element;
        vector<string> elements;

        while (getline(lineStream, element, ' ')) {

            elements.push_back(element);
        }

        if(elements.size() != 5) {

            cout << "Line only had " << elements.size() << " elements!" << endl;
            cout << "The line data was: " << line << endl;
            cout << "The line number was: " << flights.size() + 1 << endl;
            break;
        }

        try {

            int price = stoi(elements[3]);
            int duration = stoi(elements[4]);

            Flight flight(elements[0], elements[1], elements[2], price, duration);
            addFlight(flight);
        } catch (invalid_argument &e) {

            cout << "Either price or duration was not an integer in the flights.txt file, omitting entry!" << endl;
            cout << "The line data was: " << line << endl;
            cout << "The line number was: " << flights.size() + 1 << endl;
            break;
        } catch (out_of_range &e) {

            cout << "Either price or duration was out of range in the flights.txt file, omitting entry!" << endl;
            cout << "The line data was: " << line << endl;
            cout << "The line number was: " << flights.size() + 1 << endl;
            break;
        }
    }

    cout << "Loaded " << flights.size() << " flights!" << endl;
}

void FlightBooking::loadAirports() {

    ifstream file("airports.txt");
    string line;

    while (getline(file, line, '\n')) {

        istringstream lineStream(line);
        string element;
        vector<string> elements;

        while (getline(lineStream, element, ' ')) {

            elements.push_back(element);
        }

        if(elements.size() != 4) {

            cout << "Line only had " << elements.size() << " elements!" << endl;
            cout << "The line data was: " << line << endl;
            cout << "The line number was: " << airports.size() + 1 << endl;
            break;
        }

        try {

            int departureTax = stoi(elements[2]);
            int connectionTime = stoi(elements[3]);

            Airport airport(elements[0], elements[1], departureTax, connectionTime);
            addAirport(airport);
        } catch (invalid_argument &e) {

            cout << "Either departureTime or connectionTime was not an integer in the airports.txt file, omitting entry!" << endl;
            cout << "The line data was: " << line << endl;
            cout << "The line number was: " << airports.size() + 1 << endl;
            break;
        } catch (out_of_range &e) {

            cout << "Either departureTime or connectionTime was out of range in the airports.txt file, omitting entry!" << endl;
            cout << "The line data was: " << line << endl;
            cout << "The line number was: " << airports.size() + 1 << endl;
            break;
        }
    }

    cout << "Loaded " << airports.size() << " airports!" << endl;
}