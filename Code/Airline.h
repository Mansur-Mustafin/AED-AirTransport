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
    Airline();
    explicit Airline(const string& in);
    string getName() const;
    string getCode() const;
    string getCallsign() const;
    string getCountry() const;
    friend ostream& operator<< (ostream& out, const Airline& s1);
};


#endif //PROJECT_2_AIRLINE_H
