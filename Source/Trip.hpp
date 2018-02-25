#pragma once

#include <vector>
#include "FlightManager.hpp"


using namespace std;

class Trip {

	public:

		Trip(FlightManager &flightManager, vector<Flight*> flights);

		vector<Flight*> &getFlights();
		int getPrice();
		int getDuration();
	private:

		int price, duration;
		vector<Flight*> flights;
		FlightManager& flightManager;
};