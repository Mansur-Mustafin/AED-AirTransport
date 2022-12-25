//
// Created by musta on 21.12.2022.
//

#include "Airline.h"

Airline::Airline(const std::string &in){
        string feel;
        istringstream input(in);

        getline(input, feel, ','); // name
        code = feel;

        getline(input, feel, ','); // name
        name = feel;

        getline(input, feel, ','); // city
        if(feel == "_"){
            callsign = "";
        }else{
            callsign = feel;
        }
        getline(input, feel, ','); // country
        country = feel;
}

Airline::Airline() : name(""), code(""), country(""), callsign("") {}

string Airline::getCountry() const {
    return country;
}
string Airline::getCode() const {
    return code;
}
string Airline::getName() const {
    return name;
}
string Airline::getCallsign() const {
    return callsign;
}

ostream& operator<< (ostream& out, const Airline& s1){
    out << s1.code << ' ' << s1.name << ' ' << s1.callsign << ' ' << s1.country;
    return out;
}

unordered_set<string> Airline::getAirlineairports(){
    return targetsAirports;
}

void Airline::addAirport(const string& airportCode) {
    targetsAirports.insert(airportCode);
}

