//
// Created by musta on 20.12.2022.
//

#ifndef PROJECT_2_FLIGHT_H
#define PROJECT_2_FLIGHT_H

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "Target.h"


using namespace std;



class Flight {
private:

    /// @brief Flight origin
    string  source;

    /// @brief Flight destination
    Target target;
public:

    /// @brief Empty constructor
    Flight() : target(Target()), source("") {}

    /**
     * @brief Constructor that receives input line from csv file
     * @param in -> input line from csv file
     */
    Flight(string in);

    /// @brief Gets flight destination
    Target getTarget();

    /// @brief gets flight origin
    string getSource();
};


#endif //PROJECT_2_FLIGHT_H
