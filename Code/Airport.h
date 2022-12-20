//
// Created by musta on 20.12.2022.
//

#ifndef PROJECT_2_AIRPORT_H
#define PROJECT_2_AIRPORT_H
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <map>
#include <sstream>



using namespace std;

class Airport {

public:
    Airport();
    explicit Airport(const string& in);
    string getName() const;
    string getCode() const;
    string getCity() const;
    string getCountry() const;
    string getLatitude() const;
    string getLongitude() const;
private:
    string name, code, city, country, latitude, longitude;
};


#endif //PROJECT_2_AIRPORT_H
