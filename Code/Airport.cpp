//
// Created by musta on 20.12.2022.
//

#include <valarray>
#include "Airport.h"
#include <iomanip>

Airport::Airport() : name(""), code(""), city(""), country(""), latitude(0.0), longitude(0.0) {}

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
    latitude = stod(feel);
    getline(input, feel, ','); // city
    longitude = stod(feel);

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

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}

double Airport::getDistanceTo(double lat2, double lon2) const {
    double lat1 = latitude;
    double lon1 = longitude;


    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;

}

ostream& operator<< (ostream& out, const Airport& s1){
    out << s1.code << ' ' << s1.name << ' ' << s1.city << ' ' << s1.country;
    return out;
}
