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
    unordered_map <string, unordered_set<string> > cities;
    unordered_map <string, unordered_set<string> > countries;


public:
    Graph();

    bool isCity(const string& name);

    bool isCountry(const string& name);

    vector <string> getPathCities(const string& from, const string& to);

    vector <string> getPathCountries(const string& from, const string& to);

    vector <string> getPathByPoint(double lat, double lon, double dist);

    vector <string> getPathAirports(const string& from, const string& to);

    vector <string> getUltimatePath(string from, string to);

    vector <string> getPathByVectors(vector <string> from, vector <string> to);

    vector <string> targetAirports(const string& from, int num);                // todos aeroportos que podemos ir de um aeroporto para outro por n passos

    unordered_map <string, vector <Target> > getG();

    unordered_map <string, Airport> getAirports();

    unordered_map <string, unordered_set<string> > getCities();

    unordered_map <string, unordered_set<string> > getCountries();

    unsigned getNumberOfFlights(const string& Airport);

    unordered_set<string> getAirlinesFromAirport(const string& Airport);
};


#endif //PROJECT_2_GRAPH_H