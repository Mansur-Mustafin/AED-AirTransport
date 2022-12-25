//
// Created by musta on 25.12.2022.
//

#include "Airlines.h"


Airlines::Airlines(string file_nem) {
    string temp;

    ifstream in("airlines.csv");
    getline(in, temp);

    while (getline(in, temp)) {
        Airline a(temp);
        string code = temp.substr(0, 3);
        airlines[code] = a;
        companies.insert(a.getCode());
    }
}

unordered_set<string> Airlines::getCompanies() {
    return companies;
}

unordered_map<string, Airline> Airlines::getAirlines() {
    return airlines;
}

void Airlines::addAirport(const string& airline, const string& airport) {
    airlines[airline].addAirport(airport);
}
