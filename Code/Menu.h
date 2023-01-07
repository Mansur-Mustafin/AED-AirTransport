//
// Created by ianbe on 21/12/2022.
//

#ifndef PROJECT_2_MENU_H
#define PROJECT_2_MENU_H


#include "Graph.h"

class Menu {
public:

    /// @brief Main menu function
    void main_menu();

    /// @brief Simple menu to get path with lowest flight number
    void get_path_flight();

    /// @brief Simple menu to get path with fewest airline change
    void get_path_airline();

    /// @brief Simple menu to get airport info
    void get_airport_info();

    /// @brief Prints all airports accessible from an origin airport
    void printAirport_flightN(const vector <string>& inputAirports);

    /// @brief Prints all airports that a certain airline operates in
    void printAirport(unordered_set<string> airports, string code);

    /// @brief Simple menu to get airline info
    void get_airline_info();

    /// @brief Simple menu to change searching settings
    void settings();

    /// @brief Simple menu to get statistics from a certain country
    void get_country_statistics();

    /// @brief Simple menu to get statistics from the entire network
    void get_network_info();

    /// @brief Gets top k airports according to user choice
    void top_k_airports();

private:
    Graph g;
};


#endif //PROJECT_2_MENU_H
