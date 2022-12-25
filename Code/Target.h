//
// Created by musta on 20.12.2022.
//

#ifndef PROJECT_2_TARGET_H
#define PROJECT_2_TARGET_H
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "Target.h"
#include "Airport.h"

using namespace std;

class Target {
private:

    /// @brief Flight destination
    string airport;

    /// @brief Airline operating the flight
    string airline;
public:

    /// @brief Empty constructor
    Target() : airport(""), airline("") {}

    /**
     * @brief Constructor
     * @param target_ -> Flight destination
     * @param airline_ -> Airline operating the flight
     */
    Target(string airport_, string airline_) : airport(airport_), airline(airline_) {}

    /// @brief Gets flight destination
    string getAirport();

    /// @brief Gets flight airline
    string getAirline();
};


#endif //PROJECT_2_TARGET_H
