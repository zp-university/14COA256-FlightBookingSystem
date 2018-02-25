#include "Trip.hpp"

Trip::Trip(FlightManager &flightManager, vector<Flight*> flights)
	:flightManager(flightManager), flights(flights), price(0), duration(0) {

	int id = 1;

	for (Flight *flight : flights) {

		duration += flight->getDuration();
		price += flight->getPrice();

		if (id < flights.size()) {

			Airport* airport = flightManager.getAirport(flight->getDestinationAirportCode());

			duration += airport->getConnectionTime();
			price += airport->getDepartureTax();
		}

		++id;
	}
}

vector<Flight*>& Trip::getFlights() {

	return flights;
}

int Trip::getPrice() {

	return price;
}

int Trip::getDuration() {

	return duration;
}