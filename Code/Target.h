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
    string target, airline;
public:
    Target() : target(""), airline("") {}
    Target(string target_, string airline_) : target(target_), airline(airline_) {}
    string getTarget();
    string getAirline();
};


#endif //PROJECT_2_TARGET_H
