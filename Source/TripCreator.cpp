#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "TripCreator.hpp"
#include "ConsoleHandler.hpp"

TripCreator::TripCreator(FlightManager &flightManager)
        :flightManager(flightManager), chosenTrip(nullptr), currentPage(1){
}

TripCreator::~TripCreator() {

	//Either of the possibleTrips vectors could have been used here
	//but I just chose this one.

	for (Trip *trip : possibleTripsSortedByPrice) {

		delete trip;
	}
}

void TripCreator::run() {
	
	requestOrigin();

	requestDestination();

	requestDate();

	search();

	selectTrip();

	if (chosenTrip != nullptr) {

		while (!confirmTicket()) {

			selectTrip();
		}
	}
}

void TripCreator::requestOrigin() {

	while(origin == "") {

		cout << "Enter Origin: " << flush;
		string input = getInput();
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (flightManager.getAirport(input) == nullptr) {

			cout << "Invalid airport code!" << endl;
			continue;
		}

		origin = input;
	}
}

void TripCreator::requestDestination() {

	while(destination == "") {

		cout << "Enter Destination: " << flush;
		string input = getInput();
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		if (flightManager.getAirport(input) == nullptr) {

			cout << "Invalid airport code!" << endl;
			continue;
		}

		destination = input;
	}
}

void TripCreator::requestDate() {

    cout << "Enter Journey Date (DD/MM/YYYY): " << flush;
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
				storeTrip(trip);
				currentTrip.clear();
                continue;
            } else {

                for(Flight *flight2 : flights) {

                    if(flight2->getOriginAirportCode() == flight1->getDestinationAirportCode()) {

                        if (flight2->getDestinationAirportCode() == destination) {

                            currentTrip.push_back(flight1);
                            currentTrip.push_back(flight2);
							Trip *trip = new Trip(flightManager, currentTrip);
							storeTrip(trip);
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
										storeTrip(trip);
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

void TripCreator::storeTrip(Trip *trip) {

	int price = trip->getPrice();
	int duration = trip->getDuration();

	int i = 0;

	for(Trip *tripComparison : possibleTripsSortedByPrice) {

		if(price < tripComparison->getPrice()) {

			break;
		}

		++i;
	}

	possibleTripsSortedByPrice.insert(possibleTripsSortedByPrice.begin() + i, trip);

	i = 0;

	for(Trip *tripComparison : possibleTripsSortedByDuration) {

		if(duration < tripComparison->getDuration()) {

			break;
		}

		++i;
	}

	possibleTripsSortedByDuration.insert(possibleTripsSortedByDuration.begin() + i, trip);
}

void TripCreator::selectTrip() {

	chosenTrip = nullptr;

	while (chosenTrip == nullptr) {

		if (possibleTripsSortedByPrice.empty()) {

			cout << endl << "No trips were found from the selected departure airport to the selected destination airport." << endl;

			waitForEnter("Press enter to continue...");
			return;
		}

		displayPage(1);

		int input = 0;

		printTripSelectionOptions();

		cout << endl << "Please enter your selection: ";

		while ((input = getInt()) != 4) {

			switch (input) {

			case 1:

				displayPage(++currentPage);
				break;
			case 2:

				displayPage(--currentPage);
				break;
			case 3:

				changeSortingType();
				displayPage(currentPage);
				break;
			default:

				cout << endl << "Unknown Selection." << endl;
				cout << endl << "Returning to menu." << endl;
			}

			printTripSelectionOptions();
			cout << endl << "Please enter your selection: ";
		}

		while (chosenTrip == nullptr) {

			cout << "Type the ID of the flight you would like to see: ";
			int selectedTrip = getInt();

			if (selectedTrip <= 0 || selectedTrip > possibleTripsSortedByPrice.size()) {

				cout << endl << "The trip you selected was not valid." << endl;
				continue;
			}
			else {

				chosenTrip = possibleTripsSortedByPrice[selectedTrip - 1];
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
}

void TripCreator::changeSortingType() {

	runVectorReverse();

	printTripSortingOptions();

	cout << endl << "Please enter your selection: ";

	int input = getInt();

	switch(input) {

		case 1:

			sortingMethod = PriceAscending;
			break;
			break;
		case 2:

			sortingMethod = PriceDescending;
			break;
		case 3:

			sortingMethod = DurationAscending;
			break;
		case 4:

			sortingMethod = DurationDescending;
			break;
		default:

			cout << "Unknown selection, returning to previous menu." << endl;
	}

	runVectorReverse();
}

void TripCreator::runVectorReverse() {

	switch(sortingMethod) {

		case PriceDescending:

			reverse(possibleTripsSortedByPrice.begin(), possibleTripsSortedByPrice.end());
		case DurationDescending:

			reverse(possibleTripsSortedByDuration.begin(), possibleTripsSortedByDuration.end());
	}
}

vector<Trip*>& TripCreator::getVectorBySortingType() {

	if(sortingMethod == PriceAscending || sortingMethod == PriceDescending) {

		return possibleTripsSortedByPrice;
	}

	return possibleTripsSortedByDuration;
}

void TripCreator::displayPage(int page) {

	int startPoint = (page - 1) * 10;
	int endPoint = (page * 10) - 1;

	if(startPoint > possibleTripsSortedByPrice.size() || startPoint < 0) {

		cout << "There are no more pages." << endl;
		return;
	}

	if(endPoint >= possibleTripsSortedByPrice.size()) {

		endPoint = (int) (possibleTripsSortedByPrice.size() - 1);
	}

	cout << endl << "Showing results " << startPoint + 1 << " to " << endPoint + 1 << " of " << possibleTripsSortedByPrice.size() << endl;

	cout << left << setfill(' ') << setw(10) << "ID" << setw(20) << "Duration (Minutes)" << setw(10) << "Price" << setw(15) << "Connections" << endl;

	vector<Trip*> &possibleTrips = getVectorBySortingType();

	for (int i = startPoint; i <= endPoint; ++i) {

		Trip *trip = possibleTrips.at(i);

		if(trip != nullptr) {

			string connections;

			if ((trip->getFlights().size() - 1) == 0) {

				connections = "Direct";
			} else {
				ostringstream string;
				string << trip->getFlights().size() - 1;
				connections = string.str();
			}

			cout << left << setw(10) << i + 1 << setw(20) << trip->getDuration() << setw(10) << trip->getPrice() << setw(15) << connections << endl;
		}
	}
}

void TripCreator::printTripSelectionOptions() {

	cout << endl << left << setw(5) << "1.)" << "Next Page." << endl;
	cout << left << setw(5) << "2.)" << "Previous Page." << endl;
	cout << left << setw(5) << "3.)" << "Change Sorting Method." << endl;
	cout << left << setw(5) << "4.)" << "Select Flight." << endl;
}

void TripCreator::printTripSortingOptions() {

	cout << endl << left << setw(5) << "1.)" << "Price Ascending." << endl;
	cout << left << setw(5) << "2.)" << "Price Descending." << endl;
	cout << left << setw(5) << "3.)" << "Duration Ascending." << endl;
	cout << left << setw(5) << "4.)" << "Duration Descending." << endl;
}

void TripCreator::printTicketOptions() {

	cout << endl << left << setw(5) << "1.)" << setw(30) << "Confirm Booking and Save Receipt." << endl;
	cout << left << setw(5) << "2.)" << setw(30) << "Select a Different Trip." << endl;
	cout << left << setw(5) << "3.)" << setw(30) << "Back to Main Menu." << endl;
}

bool TripCreator::confirmTicket() {

	int selection = 0;

	while(true) {

		printTicketOptions();
		cout << "Please enter your selection: ";

		selection = getInt();

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

	cout << "Please enter what you would like the receipt to be saved as: ";

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

	cout << "Thank you for booking your flights with us." << endl;
	cout << "Your receipt has been saved as " << name << ".txt" << endl;

	waitForEnter("Please press enter to continue...");
}