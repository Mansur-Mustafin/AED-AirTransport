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

    /**
     * @brief Djikstra algorithm
     * O(N^2 + V)
     */
    ss Dijkstra(const string& start, const vector <string>& to, double& dist);

    /**
     * @brief Gets the distance from an airport to its target
     * @param from -> Airport code
     * @param to -> Target
     * @return Double value
     * O(1)
     */
    double Dist(const string& from, Target to);

    static vector <vector <pss> > Combine(vector <vector <pss> > p1, vector <vector <pss> > p2);

    /**
     * @brief Checks which airports are inside the radius of a certain coordinate
     * @param lat -> Latitude
     * @param lon -> Longitude
     * @param r -> Radius
     * @return Vector with airport codes
     * O(N)
     */
    vector <string> Around(double lat, double lon, double r);

    /// @brief Function to get articulation points via DFS
    void dfsArticulationP(string v, string root, vector <string>& ans, set <string> Comp, string p = "");

    void Update(string v, um <string, int>& d, string& curComp, int dist, string start, queue <string>& q, um <string, vector <string> >& p, um <string, vector <string> >& pAir, string par, string parAir);

    /**
     * @brief Gets path with lowest flight number between two Airports
     * @param v -> Origin airport
     * @param to -> Destination airport
     * @param cur -> Current result (function is recursive)
     * @param ans -> Pointer to final result
     */
    void getPath(const string& v, const string& to, const vector <vector <pss> >& cur, vector <vector <pss> >& ans);

    /// @brief Cities that have the same name in different countries
    unordered_set<string> strangeCities;

    /// @brief Map with an airport as key and vector with all possible flights from it
    um <string, vector<Target>> g;

    /// @brief Map with airport code as key and its Airport object
    um <string, Airport> airports;

    /// @brief Map with city name as key and the code of all its airports in an unordered_set
    um <string, unordered_set<string> > cities;

    /// @brief Map with country name as key and the name of all its cities in an unordered_set
    um <string, unordered_set<string> > countries;

    /// @brief Complete data for cities that have the same name in different countries
    um <string, um <string, unordered_set<string> > > dataForStrangeCities;


    /// @brief Map with airline code as key and it Airline object
    um<string, Airline> airlines;

    /// @brief Total number of flights
    int n_of_flights = 0;



    set <string> t;
    um <string, string> used;
    um <string, vector <string> > parent;
    um <string, vector<string> > air;
    um <string, int> num, low;
    int time;
    um <string, vector <string> > child;
    um <string, bool> visited;
    set <string> d;

public:
    ///@brief Empty Constructor
    Graph();

    /**
     * @brief Checks if city is in city list
     * @param name -> Name of the city
     * @return Bool value
     * O(1)
     */
    bool isCity(const string& name);

    /**
     * @brief Checks if country is in country list
     * @param name -> Name of the Country
     * @return Bool value
     * O(1)
     */
    bool isCountry(const string& name);

    /**
     * @brief Gets path with lowest flight n between two coordinates
     * @param lat -> Latitude
     * @param lon -> Longitude
     * @param dist -> Distance between points
     * @return Vector with airport codes as strings
     * O((E + V) * )
     */
    vector <pair< vector<pss>, pair<int,int>> > getPathByPointsNOfFlights(double lat1, double lon1, double lat2, double lon2, double dist, double dist2,set <string> Comp = {});

    /**
     * @brief Gets path with lowest flight number between two airports.
     * @param from -> Origin airport
     * @param to -> Destination airport
     * @param Comp -> Airline companies to use
     * @param others -> Pointer to empty list vector that stores all other options with same flight number
     * @return -> Vector with airport codes as strings
     * O(E + V)  where: V - number of airports, E - number of flights between airports
     */
    ss getPathAirports(const string& from, const string& to, set <string> Comp = {}, vector <vector <pss> >* others = nullptr);

    /**
     * @brief Gets path with lowest flight number between places
     * @param from -> Origin reference(can be name, airport code, coordinate)
     * @param to -> Destination reference(can be name or airport code)
     * @param Comp -> Airline companies to use
     * @param others -> Pointer to empty list vector that stores all other options with same flight number
     * @return Vector with airports names as strings
     * O(num1 * num2 * (E + V))  num1 number of airports from, num2 number of airports to
     */
    ss getUltimatePath(string from, string to, set <string> Comp = {}, vector <vector <pss> >* others = nullptr);

    /**
     * @brief Gets path with lowest flight number between airports
     * @param from -> Vector with origin airports
     * @param to -> Vector with destination airports
     * @param Comp -> Airline companies to use
     * @param others -> Pointer to empty list vector that stores all other options with same flight number
     * @return Vector with airports names as strings
     * O(num1 * num2 * (V + E)) num1 size of from, num2 size of to
     */
    ss getPathByVectors(vector <string> from, vector <string> to, set <string> Comp = {}, vector <vector <pss> >* others = nullptr);

    /**
     * @brief Gets all airports you can go to with n flight number
     * @param from -> Origin Airport
     * @param num -> Max flight number
     * @param Comp -> Set of airline codes to use as strings
     * @return Vector of airport codes as strings
     * O(V + E)
     */
    vector <string> targetAirports(const string& from, int num, set <string> Comp = {});

    /// @brief Gets map with an airport as key and vector with all possible flights
    um <string, vector <Target> > getG();

    /// @brief Gets airport list
    um <string, Airport> getAirports();

    /// @brief Gets airline list
    um<string, Airline> getAirlines();

    /// @brief Gets city list
    um <string, unordered_set<string> > getCities();

    /// @brief Gets cities that have the same name in different countries
    unordered_set<string> getStrangeCities();

    /**
     * @brief Checks if a city is part of the strange cities group
     * @param name -> City name
     * @return bool value
     */
    bool isStrangeCity(const string& name);

    /// @brief Gets country list
    um <string, unordered_set<string> > getCountries();

    /// @brief Gets the number of flights in the network
    int get_global_n_flight() const;

    /**
     * @brief Gets number of flights in an airport
     * @param Airport -> Airport code
     * @return Number of flights in the Airport
     */
    unsigned getNumberOfFlights(const string& Airport);

    /**
     * @brief Gets all airlines operating in given airport
     * @param Airport -> Airport code
     * @return Set of airlines as strings
     */
    unordered_set<string> getAirlinesFromAirport(const string& Airport);



    /**
     * @brief Gets the network's articulation points
     * @param Comp -> Set of airlines to compose the network
     * @return List of articulation points(airport codes) as strings
     * O(V * (E + V))
     */
    vector<string> getArticulationPoints(set <string> Comp = {});


    /**
     * @brief Gets the network diameter
     * @param Comp -> Set of airlines to compose the network
     * @return Integer value
     * O(V * (V + E))
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
     * O( num1 * (N + V)) where: num1 - number of all airlines
     */
    vector <vector <pss> > getPathByAirportsAirlines(string from, string to, set <string> Comp = {});

    /**
     * @brief Gets flight number form a specific airline
     * @param code -> Airline code
     * @return Integer Value
     */
    int get_airline_flightN(const string& code);


    /**
     * @brief Gets shortest path between two points
     * @param lat1 -> Origin Latitude
     * @param lon1 -> Origin Longitude
     * @param lat2 -> Destination Latitude
     * @param lon2 -> Destination Longitude
     * @param r -> Max radius
     * @param dist -> Pointer to total path distance
     * @return Shortest path
     * O((V^2 + N) * num1) where: num1 - from
     */
    ss getPathByPoints(double lat1, double lon1, double lat2, double lon2, double r, double& dist);



    /// @brief Gets data for the group of cities that have the same name in different countries
    um <string, um <string, unordered_set<string> > > getDataStrangeCities() {return dataForStrangeCities;}

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
    void switchToInvalidCity(const string& city);

    /**
     * @brief Unlocks a city
     * @param city -> City name
     */
    void switchToValidCity(const string& city);

    bool addFlight(string orig, string dest, string airline);
};

#endif // PROJECT_2_GRAPH_H