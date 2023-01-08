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
#include <list>
#include <set>
#include "Target.h"
#include "Airport.h"
#include "Airline.h"

using namespace std;

typedef pair <vector <string>, vector<string> > ss;
typedef pair <string, string> pss;
typedef vector <pair <vector <string>, vector<string> > , pair<int,int>> vp;

#define um unordered_map

class Graph {

private:

    vector <vector <pss> > Combine(vector <vector <pss> > p1, vector <vector <pss> > p2);

    void Update(string v, um <string, int>& d, string& curComp, int dist, string start, queue <string>& q, um <string, vector <string> >& p, um <string, vector <string> >& pAir, string par, string parAir);

    /**
     * @brief Gets path with lowest flight number between two Airports
     * @param v -> Origin airport
     * @param to -> Destination airport
     * @param cur -> Current result (function is recursive)
     * @param ans -> Pointer to final result
     */
    void getPath(string v, string to, vector <vector <pss> > cur, vector <vector <pss> >& ans);

    /// @brief Cities that have the same name in different countries
    unordered_set<string> strangeCities;

    /// @brief Map with an airport as key and vector with all possible flights from it
    unordered_map <string, vector<Target>> g;
    // ["asd"] = {"qwe", "sdf"}   g["any airport"].size() = количество вылетов из аэропорт

    /// @brief Map with airport code as key and its Airport object
    unordered_map <string, Airport> airports;
    // g["any airport"]  for => set (airline)

    /// @brief Map with city name as key and the code of all its airports in an unordered_set
    unordered_map <string, unordered_set<string> > cities;

    /// @brief Map with country name as key and the name of all its cities in an unordered_set
    unordered_map <string, unordered_set<string> > countries;

    /// @brief Complete data for cities that have the same name in different countries
    unordered_map <string, unordered_map <string, unordered_set<string> > > dataForStrangeCities;


    /// @brief Map with airline code as key and it Airline object
    unordered_map<string, Airline> airlines;

    /// @brief Total number of flights
    int n_of_flights = 0;

    set <string> t;

    um <string, string> used;

    um <string, vector <string> > parent;

    um <string, vector<string> > air;

public:
    ///@brief Empty Constructor
    Graph();

    /**
     * @brief Checks if city is in city list
     * @param name -> Name of the city
     * @return Bool value
     */
    bool isCity(const string& name);

    /**
     * @brief Checks if country is in country list
     * @param name -> Name of the Country
     * @return Bool value
     */
    bool isCountry(const string& name);

    /**
     * @brief Gets path with lowest flight n between two coordinates
     * @param lat -> Latitude
     * @param lon -> Longitude
     * @param dist -> Distance between points
     * @return Vector with airport codes as strings
     */
    vector <pair< vector<pss>, pair<int,int>> > getPathByPointsNOfFlights(double lat1, double lon1, double lat2, double lon2, double dist, double dist2,set <string> Comp = {});  // FALTA AQUIIIIIIIIIIIIIIIIIIII

    /**
     * @brief Gets path with lowest flight number between two airports.
     * @param from -> Origin airport
     * @param to -> Destination airport
     * @param Comp -> Airline companies to use
     * @param others -> Pointer to empty list vector that stores all other options with same flight number
     * @return -> Vector with airport codes as strings
     * O(n + m) n - number of airports, m - number of flights between airports
     */
    ss getPathAirports(const string& from, const string& to, set <string> Comp = {}, vector <vector <pss> >* others = nullptr);

    /**
     * @brief Gets path with lowest flight number between places
     * @param from -> Origin reference(can be name, airport code, coordinate)
     * @param to -> Destination reference(can be name or airport code)
     * @param Comp -> Airline companies to use
     * @param others -> Pointer to empty list vector that stores all other options with same flight number
     * @return Vector with airports names as strings
     * O(num1 * num2 * (n + m)) -
     */
    ss getUltimatePath(string from, string to, set <string> Comp = {}, vector <vector <pss> >* others = nullptr);

    /**
     * @brief Gets path with lowest flight number between airports
     * @param from -> Vector with origin airports
     * @param to -> Vector with destination airports
     * @param Comp -> Airline companies to use
     * @param others -> Pointer to empty list vector that stores all other options with same flight number
     * @return Vector with airports names as strings
     * O(num1 * num2 * (n + m))
     */
    ss getPathByVectors(vector <string> from, vector <string> to, set <string> Comp = {}, vector <vector <pss> >* others = nullptr);

    /**
     * @brief Gets all airports you can go to with n flight number
     * @param from -> Origin Airport
     * @param num -> Max flight number
     * @param Comp -> Set of airline codes to use as strings
     * @return Vector of airport codes as strings
     * O(n + m)
     */
    vector <string> targetAirports(const string& from, int num, set <string> Comp = {});   // todos aeroportos que podemos ir de um aeroporto para outro por n passos

    /// @brief Gets map with an airport as key and vector with all possible flights
    unordered_map <string, vector <Target> > getG();

    /// @brief Gets airport list
    unordered_map <string, Airport> getAirports();

    /// @brief Gets airline list
    unordered_map<string, Airline> getAirlines();

    /// @brief Gets city list
    unordered_map <string, unordered_set<string> > getCities();

    /// @brief Gets cities that have the same name in different countries
    unordered_set<string> getStrangeCities();

    /**
     * @brief Checks if a city is part of the strange cities group
     * @param name -> City name
     * @return bool value
     */
    bool isStrangeCity(string name);

    /// @brief Gets country list
    unordered_map <string, unordered_set<string> > getCountries();

    /// @brief Gets the number of flights in the network
    int get_global_n_flight();

    /**
     * @brief Gets number of flights in an airport
     * @param Airport -> Airport code
     * @return Number of flights in the Airport
     */
    unsigned getNumberOfFlights(const string& Airport);      // info about Airport number of flights

    /**
     * @brief Gets all airlines operating in given airport
     * @param Airport -> Airport code
     * @return Set of airlines as strings
     */
    unordered_set<string> getAirlinesFromAirport(const string& Airport);    // info Airport all companies

    /// @brief Function to get articulation points via DFS
    void dfsArticulationP(const string& airport, unordered_map <string, int>& num, unordered_map <string, int>& low, int& index, unordered_map<string, bool>& used, vector<string>& res,const set <string>& Comp);

    /**
     * @brief Gets the network's articulation points
     * @param Comp -> Set of airlines to compose the network
     * @return List of articulation points(airport codes) as strings
     */
    vector<string> getArticulationPoints(set <string> Comp = {});


    /**
     * @brief Gets the network diameter
     * @param Comp -> Set of airlines to compose the network
     * @return Integer value
     */
    int getDiameter( set <string> Comp = {});

    /**
     * @brief Gets the Network diameter using BFS
     * @param airport -> Airport to start
     * @param Comp -> Airlines to use in search
     * @return Integer value
     */
    int diameterBFS(string airport, set<string> Comp);

    /**
     * @brief Gets path between airports with fewest airline change in the way
     * @param from -> Origin Airport
     * @param to -> Destination Airport
     * @param Comp -> Airlines to use
     * @return Path
     * O(number of all airlines * (n + m))
     */
    vector <vector <pss> > getPathByAirportsAirlines(string from, string to, set <string> Comp = {});

    /**
     * @brief Gets flight number form a specific airline
     * @param code -> Airline code
     * @return Integer Value
     */
    int get_airline_flightN(string code);


    /**
     * @brief Checks which airports are inside the radius of a certain coordinate
     * @param lat -> Latitude
     * @param lon -> Longitude
     * @param r -> Radius
     * @return Vector with airport codes
     * O(n)
     */
    vector <string> Around(double lat, double lon, double r);

    /**
     * @brief Gets shortest path between two points
     * @param lat1 -> Origin Latitude
     * @param lon1 -> Origin Longitude
     * @param lat2 -> Destination Latitude
     * @param lon2 -> Destination Longitude
     * @param r -> Max radius
     * @param dist -> Pointer to total path distance
     * @return Shortest path
     * O((n^2 + m) * num1) num1 - from
     */
    ss getPathByPoints(double lat1, double lon1, double lat2, double lon2, double r, double& dist);

    /**
     * @brief Djikstra algorithm
     * O(n^2 + m)
     */
    ss Dijkstra(string start, vector <string> to, double& dist);

    /**
     * @brief Gets the distance from an airport to its target
     * @param from -> Airport code
     * @param to -> Target
     * @return Double value
     * O(1)
     */
    double Dist(string from, Target to);

    /// @brief Gets data for the group of cities that have the same name in different countries
    unordered_map <string, unordered_map <string, unordered_set<string> > > getDataStrangeCities() {return dataForStrangeCities;}

    /**
     * @brief Locks an airport
     * @param a -> Airport code
     */
    void switchToInvalid(string a);

    /**
     * @brief Unlocks an airport
     * @param a -> Airport code
     */
    void switchToValid(string a);

    /**
     * @brief Locks a city
     * @param city -> City name
     */
    void switchToInvalidCity(string city);

    /**
     * @brief Unlocks a city
     * @param city -> City name
     */
    void switchToValidCity(string city);

};

#endif // PROJECT_2_GRAPH_H