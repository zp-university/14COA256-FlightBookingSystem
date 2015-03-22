cmake_minimum_required(VERSION 2.8.4)
project(Flight_Booking_System)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
    FlightManager.cpp
    Data/Flight.cpp
    Data/Airport.cpp
    TripCreator.cpp
    ConsoleHandler.cpp
    Date.cpp)
add_executable(Flight_Booking_System ${SOURCE_FILES} Selector.cpp Selector.hpp AirportLookup.cpp AirportLookup.hpp)