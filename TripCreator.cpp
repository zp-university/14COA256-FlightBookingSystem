#include <iomanip>
#include <sstream>
#include <fstream>
#include "TripCreator.hpp"
#include "ConsoleHandler.hpp"

TripCreator::TripCreator(FlightManager &flightManager)
        :flightManager(flightManager), chosenTrip(nullptr){
}

TripCreator::~TripCreator() {

	for (Trip *trip : possibleTrips) {

		delete trip;
	}
}

void TripCreator::run() {

	while(origin == "") {

		requestOrigin();
	}

	requestDestination();

	requestDate();

	search();

	selectTrip();

	while(!confirmTicket()) {

		selectTrip();
	}
}

void TripCreator::requestOrigin() {

	while(origin == "") {

		cout << "Enter Origin: " << flush;
		string input = getInput();
		if (input.length() != 3) {

			cout << "Invalid airport code!" << endl;
			return;
		}

		origin = input;
	}
}

void TripCreator::requestDestination() {

	while(destination == "") {

		cout << "Enter Destination: " << flush;
		string input = getInput();
		if (input.length() != 3) {

			cout << "Invalid airport code!" << endl;
			return;
		}

		destination = input;
	}
}

void TripCreator::requestDate() {

    cout << "Enter Journey Date: " << flush;
    date = getDate();
}

void TripCreator::search() {

    vector<Flight*> &flights = flightManager.getFlights();

    for(Flight *flight1 : flights) {

        if(flight1->getOriginAirportCode() == origin) {

            vector<Flight*> currentTrip;

            if(flight1->getDestinationAirportCode() == destination) {

                currentTrip.push_back(flight1);
				Trip *trip = new Trip(flightManager, currentTrip);
				possibleTrips.push_back(trip);
				currentTrip.clear();
                continue;
            } else {

                for(Flight *flight2 : flights) {

                    if(flight2->getOriginAirportCode() == flight1->getDestinationAirportCode()) {

                        if (flight2->getDestinationAirportCode() == destination) {

                            currentTrip.push_back(flight1);
                            currentTrip.push_back(flight2);
							Trip *trip = new Trip(flightManager, currentTrip);
							possibleTrips.push_back(trip);
							currentTrip.clear();
                            continue;
                        } else {

                            for(Flight *flight3 : flights) {

                                if(flight3->getOriginAirportCode() == flight2->getDestinationAirportCode()) {

                                    if(flight3->getDestinationAirportCode() == destination) {

                                        currentTrip.push_back(flight1);
                                        currentTrip.push_back(flight2);
                                        currentTrip.push_back(flight3);
										Trip *trip = new Trip(flightManager, currentTrip);
										possibleTrips.push_back(trip);
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

	chosenTrip = nullptr;

	while(chosenTrip == nullptr) {

		if (possibleTrips.empty()) {

			cout << "No trips were found from the selected airport to the selected destination." << endl;
		}

		cout << endl << left << setfill(' ') << setw(5) << "ID" << setw(20) << "Duration" << setw(20) << "Price" << setw(20) << "Connections" << endl;
		int i = 0;
		for (Trip *trip : possibleTrips) {

			string connections;

			if ((trip->getFlights().size() - 1) == 0) {

				connections = "Direct";
			} else {
				ostringstream string;
				string << trip->getFlights().size() - 1;
				connections = string.str();
			}

			cout << left << setw(5) << i + 1 << setw(20) << trip->getDuration() << setw(20) << trip->getPrice() << setw(20) << connections << endl;
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

		cout << endl << left << setfill(' ') <<
				setw(15) << "" <<
				setw(5) << "From" <<
				setw(5) << "To" <<
				setw(30) << "Airline/Airport Name" <<
				setw(22) << "Duration (Minutes)" <<
				setw(5) << "Price" << endl;

		int id = 1;

		for (Flight *flight : chosenTrip->getFlights()) {

			string flightID = "Flight #" + to_string(id);

			cout << left << setfill(' ') << setw(15) <<
					flightID << setw(5) <<
					flight->getOriginAirportCode() << setw(5) <<
					flight->getDestinationAirportCode() << setw(30) <<
					flight->getAirline() << setw(22) <<
					flight->getDuration() << setw(5) <<
					flight->getPrice() << endl;

			if (id < chosenTrip->getFlights().size()) {

				Airport *airport = flightManager.getAirport(flight->getDestinationAirportCode());
				string connection = "Connection #" + to_string(id);

				cout << left << setfill(' ') << setw(15) <<
						connection << setw(5) <<
						airport->getAirportCode() << setw(5) <<
						airport->getAirportCode() << setw(30) <<
						airport->getAirportName() << setw(22) <<
						airport->getConnectionTime() << setw(5) <<
						airport->getDepartureTax() << endl;
			}

			++id;
		}

		cout << left << setfill(' ') << setw(15) <<
				"Total: " << setw(40) << "" << setw(22) <<
				chosenTrip->getDuration() << setw(5) <<
				chosenTrip->getPrice() << endl;
	}
}

void TripCreator::printTicketOptions() {

	cout << endl << left << setw(5) << "1.)" << setw(30) << "Confirm Booking and Save Receipt." << endl;
	cout << left << setw(5) << "2.)" << setw(30) << "Select a Different Trip." << endl;
	cout << left << setw(5) << "3.)" << setw(30) << "Back to Main Menu." << endl;
}

bool TripCreator::confirmTicket() {

	printTicketOptions();

	int selection = 0;

	while((selection = getInt()) != 3) {

		switch(selection) {

			case 1:

				printReceipt();
				return true;
			case 2:

				return false;
			case 3:

				return true;
			default:

				cout << endl << "Unknown selection." << endl;
		}
	}
}

void TripCreator::printReceipt() {

	cout << "Please enter the name you would like the receipt saved as: ";

	string name = getInput();

	ofstream file;
	file.open(name + ".txt");

	file << left << setw(20) << "Origin: " << setw(30) << origin << endl;
	file << left << setw(20) << "Destination: " << setw(30) << destination << endl;
	file << left << setw(20) << "Date: " << setw(30) << date.getDateString().c_str() << endl;

	file << endl << left << setfill(' ') <<
			setw(15) << "" <<
			setw(5) << "From" <<
			setw(5) << "To" <<
			setw(30) << "Airline/Airport Name" <<
			setw(22) << "Duration (Minutes)" <<
			setw(5) << "Price" << endl;

	int id = 1;

	for (Flight *flight : chosenTrip->getFlights()) {

		string flightID = "Flight #" + to_string(id);

		file << left << setfill(' ') << setw(15) <<
				flightID << setw(5) <<
				flight->getOriginAirportCode() << setw(5) <<
				flight->getDestinationAirportCode() << setw(30) <<
				flight->getAirline() << setw(22) <<
				flight->getDuration() << setw(5) <<
				flight->getPrice() << endl;

		if (id < chosenTrip->getFlights().size()) {

			Airport *airport = flightManager.getAirport(flight->getDestinationAirportCode());
			string connection = "Connection #" + to_string(id);

			file << left << setfill(' ') << setw(15) <<
					connection << setw(5) <<
					airport->getAirportCode() << setw(5) <<
					airport->getAirportCode() << setw(30) <<
					airport->getAirportName() << setw(22) <<
					airport->getConnectionTime() << setw(5) <<
					airport->getDepartureTax() << endl;
		}

		++id;
	}

	file << left << setfill(' ') << setw(15) <<
			"Total: " << setw(40) << "" << setw(22) <<
			chosenTrip->getDuration() << setw(5) <<
			chosenTrip->getPrice() << endl;
}