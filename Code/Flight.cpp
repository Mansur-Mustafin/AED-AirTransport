//
// Created by musta on 20.12.2022.
//

#include "Flight.h"

Flight::Flight(std::string in) {
    string feel, feel2;
    istringstream input(in);
    getline(input, feel, ','); // name
    source = feel;
    getline(input, feel, ','); // name
    getline(input, feel2, ','); // name
    target = Target(feel, feel2);
}

Target Flight::getTarget() {
    return target;
}

string Flight::getSource() {
    return source;
}