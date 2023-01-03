//
// Created by ianbe on 21/12/2022.
//

#ifndef PROJECT_2_MENU_H
#define PROJECT_2_MENU_H


#include "Graph.h"

class Menu {
public:


void main_menu();

void get_path_flight();

void get_path_airline();

void get_airport_info();

void printAirport_flightN(const vector <string>& inputAirports);

void printAirport(unordered_set<string> airports);

void get_airline_info();

void get_articulation_points();

void get_network_info();

void top_k_airports();

private:
    Graph g;
};


#endif //PROJECT_2_MENU_H
