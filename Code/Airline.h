//
// Created by musta on 21.12.2022.
//

#ifndef PROJECT_2_AIRLINE_H
#define PROJECT_2_AIRLINE_H
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <map>
#include <sstream>
using namespace std;


class Airline {
private:
    string code,name,callsign,country;
    unordered_set<string> targetsAirports;
public:

    /// @brief Empty Constructor
    Airline();

    /**
     * @brief Constructor that receives input line from csv file
     * @param in -> input line from csv file
     */
    explicit Airline(const string& in);

    /// @brief Gets airline name
    string getName() const;

    /// @brief Gets airline code
    string getCode() const;

    /// @brief Gets airline call sign
    string getCallsign() const;

    /// @brief Gets airline country
    string getCountry() const;

    /// @brief Overload of <em>operator<< </em>
    friend ostream& operator<< (ostream& out, const Airline& s1);
};


#endif //PROJECT_2_AIRLINE_H
