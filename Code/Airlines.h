//
// Created by musta on 25.12.2022.
//

#ifndef PROJECT_2_AIRLINES_H
#define PROJECT_2_AIRLINES_H
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <list>
#include <set>
#include "Airline.h"

using namespace std;

class Airlines {

private:
    unordered_set<string> companies;
    unordered_map<string, Airline> airlines;

public:
    Airlines() {};
    explicit Airlines(string file_nem);
    unordered_set<string> getCompanies();
    unordered_map<string, Airline> getAirlines();
    void addAirport(const string& airline, const string& airport);
};


#endif //PROJECT_2_AIRLINES_H
