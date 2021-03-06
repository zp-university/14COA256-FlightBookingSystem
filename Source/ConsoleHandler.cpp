#include <iostream>
#include <stdexcept>
#include <sstream>
#include "ConsoleHandler.hpp"

using namespace std;

string getInput() {

    string input;
    getline(cin, input);
    return input;
}

Date getDate() {

    string input = getInput();
    istringstream stringStream(input);

    string day;
    string month;
    string year;

    getline(stringStream, day, '/');
    getline(stringStream, month, '/');
    getline(stringStream, year);

    if(day == "-1" || month == "-1" || year == "-1") {

        cout << "There were not enough parts to your date! You must enter your date as DD/MM/YYYY" << endl;
        cout << "Enter a valid date: " << flush;
        return getDate();
    }

    int dayInt;
    int monthInt;
    int yearInt;

    try {

        dayInt = stoi(day);
        monthInt = stoi(month);
        yearInt = stoi(year);
    } catch (invalid_argument &e) {

        cout << "Day, Month or Year contained a non-integer value or no value at all, was your formatting wrong?" << endl;
        cout << "Enter a valid date: " << flush;
        return getDate();
    } catch (out_of_range &e) {

        cout << "Day, Month or Year is out of range of an integer!" << endl;
        cout << "Enter a valid date: " << flush;
        return getDate();
    }

    if(dayInt > 30) {

        cout << "Inputted day was greater than 30 which is invalid!" << endl;
        cout << "Enter a valid date: " << flush;
        return getDate();
    } else if(dayInt <= 0) {

        cout << "Inputted day was less than 1 which is invalid!" << endl;
        cout << "Enter a valid date: " << flush;
		return getDate();
    }

    if(monthInt > 12) {

        cout << "Inputted month was greater than 12 which is invalid!" << endl;
        cout << "Enter a valid date: " << flush;
        return getDate();
    } else if(monthInt <= 0) {

        cout << "Inputted month was less than 1 which is invalid!" << endl;
        cout << "Enter a valid date: " << flush;
		return getDate();
    }

    if(getIntLength(yearInt) != 4) {

        cout << "Inputted year was not 4 digits which is invalid!" << endl;
        cout << "Enter a valid date: " << flush;
        return getDate();
	} else if (yearInt <= 2014) {

		cout << "Inputted year was less than 2015 which is invalid!" << endl;
		cout << "Enter a valid date: " << flush;
		return getDate();
	}

    return Date(dayInt, monthInt, yearInt);
}

int getInt() {

    string input = getInput();
    int output;

    try {

        output = stoi(input);

        if(getIntLength(output) != input.length()) {

            cout << "Input contained some non-numeric characters!" << endl;
            return -1;
        }
    } catch (invalid_argument &e) {

        cout << "Input contains no integers!" << endl;
        return -1;
    } catch (out_of_range &e) {

        cout << "Input is out of range of an integer!" << endl;
        return -1;
    }

    return output;
}

int getIntLength(int integer) {

    unsigned int length(0);

    do {

        ++length;
        integer /= 10;
    } while(integer);

    return length;
}

void waitForEnter(string message) {

    cout << endl << message;

    cin.get();
}