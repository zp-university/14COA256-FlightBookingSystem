#include <sstream>
#include "Date.hpp"


Date::Date() {

    Date(0, 0, 1000);
}

Date::Date(int day, int month, int year) {

    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::getDay() {

    return day;
};

int Date::getMonth() {

    return month;
}

int Date::getYear() {

    return year;
}

string Date::getDateString() {

    ostringstream output;

    output << day << " ";

    switch(month) {

        case 1: output << "January"; break;
        case 2: output << "February"; break;
        case 3: output << "March"; break;
        case 4: output << "April"; break;
        case 5: output << "May"; break;
        case 6: output << "June"; break;
        case 7: output << "July"; break;
        case 8: output << "August"; break;
        case 9: output << "September"; break;
        case 10: output << "October"; break;
        case 11: output << "November"; break;
        case 12: output << "December"; break;
        default: output << "Unknown Month!"; break;
    }

    output << " " << year;

    return output.str();
}