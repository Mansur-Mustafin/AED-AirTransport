//
// Created by musta on 20.12.2022.
//

#ifndef PROJECT_2_GRAPH_H
#define PROJECT_2_GRAPH_H
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "Target.h"
#include "Airport.h"

using namespace std;

class Graph {

private:
    unordered_map <string, vector <Target> > g; // ["asd"] = {"qwe", "sdf"}   g["any airport"].size() = количество вылетов из аэропорт
    unordered_map <string, Airport> airports; // g["any airport"]  for => set (airline)
    unordered_map <string, vector <string> > cities;
    unordered_map <string, vector <string> > countries;

public:
    Graph();

    vector <string> getPathCities(string from, string to);

    vector <string> getPath(string from, string to);

    vector <string> targetAirports(string from, int num);                // todos aeroportos que podemos ir de um aeroporto para outro por n passos

    unordered_map <string, vector <Target> > getG();

    unordered_map <string, Airport> getAirports();

    unordered_map <string, vector <string> > getCities();

    unordered_map <string, vector <string> > getCountries();
};


#endif //PROJECT_2_GRAPH_H
