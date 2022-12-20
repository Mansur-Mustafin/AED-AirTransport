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
    string  source;
    Target target;
public:

    Flight() : target(Target()), source("") {}

    Flight(string in);

    Target getTarget();

    string getSource();
};


#endif //PROJECT_2_FLIGHT_H
