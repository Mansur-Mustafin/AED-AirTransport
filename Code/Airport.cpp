//
// Created by musta on 20.12.2022.
//

#include "Airport.h"


Airport::Airport() : name(""), code(""), city(""), country(""), latitude(""), longitude("") {}

Airport::Airport(const string& in) {

    string feel;
    istringstream input(in);
    getline(input, feel, ','); // name
    code = feel;
    getline(input, feel, ','); // name
    name = feel;
    getline(input, feel, ','); // city
    city = feel;
    getline(input, feel, ','); // country
    country = feel;
    getline(input, feel, ','); // latitude
    latitude = feel;
    getline(input, feel, ','); // city
    longitude = feel;

    /*
    vector <string> temp = Help::Split(in);
    name = temp[0], city = temp[1], country = temp[2];
    latitude = temp[3], longitude = temp[4];
     */
}

string Airport::getName() const {
    return name;
}

string Airport::getCity() const {
    return city;
}

string Airport::getCode() const {
    return code;
}

string Airport::getCountry() const {
    return country;
}

string Airport::getLatitude() const {
    return latitude;
}

string Airport::getLongitude() const {
    return longitude;
}
