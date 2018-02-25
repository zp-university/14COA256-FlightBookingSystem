#pragma once
#include <string>

using namespace std;

class Date {

    public:

        Date();

        Date(int day, int month, int year);

        int getDay();
        int getMonth();
        int getYear();

        string getDateString();
    private:

        int day;
        int month;
        int year;
};