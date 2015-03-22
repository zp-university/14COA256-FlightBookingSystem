#include <iomanip>
#include <sstream>
#include "TripCreator.hpp"

TripCreator::TripCreator(FlightBooking *flightBooking)
        :flightBooking(*flightBooking) {

    requestOrigin();
    requestDestination();
    requestDate();
    search();
	while (chosenTrip.empty()) {

		selectTrip();
	}
}

void TripCreator::requestOrigin() {

    cout << "Enter Origin: " << flush;
    string input = getInput();
    if(input.length() != 3) {

        cout << "Invalid airport code!" << endl;
        requestOrigin();
    }

    origin = input;
}

void TripCreator::requestDestination() {

    cout << "Enter Destination: " << flush;
    string input = getInput();
    if(input.length() != 3) {

        cout << "Invalid airport code!" << endl;
        requestDestination();
    }

    destination = input;
}

void TripCreator::requestDate() {

    cout << "Enter Journey Date: " << flush;
    date = getDate();
}

void TripCreator::search() {

    vector<Flight*> &flights = flightBooking.getFlights();

    for(Flight *flight1 : flights) {

        if(flight1->getOriginAirportCode() == origin) {

            vector<Flight*> currentTrip;

            if(flight1->getDestinationAirportCode() == destination) {

                currentTrip.push_back(flight1);
                possibleTrips.push_back(currentTrip);
				currentTrip.clear();
                continue;
            } else {

                for(Flight *flight2 : flights) {

                    if(flight2->getOriginAirportCode() == flight1->getDestinationAirportCode()) {

                        if (flight2->getDestinationAirportCode() == destination) {

                            currentTrip.push_back(flight1);
                            currentTrip.push_back(flight2);
                            possibleTrips.push_back(currentTrip);
							currentTrip.clear();
                            continue;
                        } else {

                            for(Flight *flight3 : flights) {

                                if(flight3->getOriginAirportCode() == flight2->getDestinationAirportCode()) {

                                    if(flight3->getDestinationAirportCode() == destination) {

                                        currentTrip.push_back(flight1);
                                        currentTrip.push_back(flight2);
                                        currentTrip.push_back(flight3);
                                        possibleTrips.push_back(currentTrip);
										currentTrip.clear();
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void TripCreator::selectTrip() {

	cout << endl << setfill(' ') << "ID" << setw(20) << "Duration" << setw(20) << "Price" << setw(20) << "Connections" << endl;
	int i = 0;
	for (vector<Flight*> trip : possibleTrips) {

		int id = 1;
		int duration = 0;
		int price = 0;

		for (Flight *flight : trip) {

			duration += flight->getDuration();
			price += flight->getPrice();

			if (id < trip.size()) {

				Airport* airport = flightBooking.getAirport(flight->getDestinationAirportCode());

				duration += airport->getConnectionTime();
				price += airport->getDepartureTax();
			}

			++id;
		}

		string connections;

		if ((trip.size() - 1) == 0) {

			connections = "Direct";
		}
		else {
			ostringstream string;
			string << trip.size() - 1;
			connections = string.str();
		}

		cout << setw(2) << i + 1 << setw(20) << duration << setw(20) << price << setw(20) << connections << endl;
		++i;
	}

	cout << endl;

	cout << "Select the flight you would like to see: ";
	int selectedTrip = getInt();

	if (selectedTrip <= 0 || selectedTrip > possibleTrips.size()) {

		cout << endl << "The trip you selected was not valid." << endl;
		exit(0);
	} else {

		chosenTrip = possibleTrips[selectedTrip - 1];
	}

	cout << endl << "You have selected the following trip" << endl;

	cout << left << setw(20) << "Origin: " << setw(30) << origin << endl;
	cout << left << setw(20) << "Destination: " << setw(30) << destination << endl;
	cout << left << setw(20) << "Date: " << setw(30) << date.getDateString().c_str() << endl;

	cout << endl << left << setfill(' ') << setw(15) << "" << setw(5) << "From" << setw(5) << "To" << setw(30) << "Airline/Airport Name" << setw(22) << "Duration (Minutes)" << setw(5) << "Price" << endl;

	int id = 1;
	int duration = 0;
	int price = 0;

	for (Flight *flight : chosenTrip) {

		string flightID = "Flight #" + to_string(id);
		
		cout << left << setfill(' ') << setw(15)
			<< flightID << setw(5)
			<< flight->getOriginAirportCode() << setw(5)
			<< flight->getDestinationAirportCode() << setw(30)
			<< flight->getAirline() << setw(22)
			<< flight->getDuration() << setw(5)
			<< flight->getPrice() << endl;

		duration += flight->getDuration();
		price += flight->getPrice();

		if (id < chosenTrip.size()) {

			Airport* airport = flightBooking.getAirport(flight->getDestinationAirportCode());
			string connection = "Connection #" + to_string(id);

			cout << left << setfill(' ') << setw(15)
				<< connection << setw(5)
				<< airport->getAirportCode() << setw(5)
				<< airport->getAirportCode() << setw(30)
				<< airport->getAirportName() << setw(22)
				<< airport->getConnectionTime() << setw(5)
				<< airport->getDepartureTax() << endl;

			duration += airport->getConnectionTime();
			price += airport->getDepartureTax();
		}

		++id;
	}

	cout << left << setfill(' ') << setw(15) <<
		"Total: " << setw(40) << "" << setw(22)
		<< duration << setw(5)
		<< price << endl;
}