#pragma once

#include "FlightManager.hpp"

using namespace std;

class Selector {

public:

    Selector(FlightManager &flightManager);

    void printOptions();
    int getSelection();

private:

    FlightManager &flightManager;
    void run();
};