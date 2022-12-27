//
// Created by ianbe on 21/12/2022.
//

#include "Menu.h"



void Menu::printAirport_flightN(vector <string> airports) {


    sort(airports.begin(), airports.end(), [this](const string& a1, const string& a2) -> bool
    {
        return g.getNumberOfFlights(a1) > g.getNumberOfFlights(a2);
    });


    unordered_map<string, list<string>> countries2cities;
    unordered_map<string, list<Airport>> cities2airports;
    list<Airport> listOfAiports;

    for (auto i : airports) {
        Airport a = g.getAirports()[i];
        countries2cities[a.getCountry()].push_back(a.getCity());
        cities2airports[a.getCity()].push_back(a);
        listOfAiports.push_back(a);
    }

    int city_n = 0;
    int countries_n = countries2cities.size();

    for(const auto& airport : listOfAiports){
        auto it = countries2cities.find(airport.getCountry());
        if(it == countries2cities.end()) continue;


        cout << airport.getCountry() << endl;
        for(auto city : countries2cities[airport.getCountry()]){

            if(cities2airports.find(city) == cities2airports.end()) continue;
            city_n++;
            cout << " |-----" << city << endl;
            for(auto air: cities2airports[city]){
                cout << "         |-----" << air.getName() << ": (" << air.getCode() << ')'<< endl;
            }
            cities2airports.erase(city);
        }
        countries2cities.erase(airport.getCountry());
    }




    cout << "Number of Airports: " << airports.size() << endl;
    cout << "Number of countries: " << countries_n  << " (incluindo o pais de aeroporto de pesquisa) "<< endl;
    cout << "Number of cities: " << city_n << endl;

}

void Menu::printAirport(unordered_set<string> airports) {
    unordered_map <string, unordered_map <string, vector<Airport>>> by_country;

    for (auto i : airports) {
        Airport a = g.getAirports()[i];
        by_country[a.getCountry()][a.getCity()].push_back(a);
    }

    int city_n = 0;

    for (auto i : by_country) {
        cout << i.first << endl;
        city_n += i.second.size();
        for (auto j : i.second) {
            cout << " |-----" << j.first << endl;
            for (auto c : j.second) {
                cout << "         |-----" << c.getName()<< ": ("  << c.getCode() << ')' << endl;
            }
        }
        cout << endl;
    }

    cout << "Number of Airports: " << airports.size() << endl;
    cout << "Number of countries: " << by_country.size() << endl;
    cout << "Number of cities: " << city_n << endl;
}

void Menu::get_path_flight() {

    string airline_choice;

    set <string> airlines;

    cout << "Do you want to use specific airlines? (y/n)" << endl;

    cin >> airline_choice;

    if (airline_choice == "Y" || airline_choice == "y") {
        int n_airlines;

        cout << "How many airlines do you want to use?" << endl;

        cin >> n_airlines;

        cout << endl;

        for (int i = 0; i < n_airlines; i++) {
            string al;

            cout << i+1 << " - " << "Please enter an airline code:" << endl;

            cin >> al;

            cout << endl;

            airlines.insert(al);
        }
    }

    cout << "Wich kind of data do you have?" << endl;
    cout << "1 - City and/or country names or Airport code" << endl;
    cout << "2 - Coordinates " << endl;

    cout << "Please enter your choice:" << endl;

    int choice;
    cin >> choice;
    cout << endl;

    string origin, dest;

    double lat, lon, dist;

    vector<string> output;

    vector <vector <string>> others;

    switch (choice) {
        case 1:
            cout << "Please enter the origin city name:";
            cin >> origin;
            cout << endl;

            cout << "Please enter destination city name:";
            cin >> dest;

            output = g.getUltimatePath(origin, dest, airlines, &others);
            break;


        case 2:
            cout << "Please enter the origin coordinates:";
            cin >> lat;
            cout << endl;
            cout << "Please enter destination country name:";
            cin >> lon;
            cout << endl << "Please enter max distance between points:";
            cin >> dist;
            cout << endl;

            output = g.getPathByPoint(lat, lon, dist);
            break;

        default:
            get_path_flight();
            break;
    }

    cout << "Would you like to see all possible paths with the lowest flight number? (y/n)" << endl;

    string print_choice;
    cin >> print_choice;

    if (print_choice == "Y" || print_choice == "y") {
        cout << endl << "Your path is:" << endl;

        for (auto i : others) {
            for (int j = 0; j < i.size(); j++) {
                cout << i[j];
                if (j != i.size()-1) {
                    cout << "->";
                }
            }
            cout << endl;
        }
    }else {
        for (auto i : output) {
            cout << i << endl;
        }
    }

}

void Menu::get_airport_info() {

    cout << "Please enter airport code:";

    string code;
    cin >> code;

    unordered_map<string, vector<Target>> a = g.getG();

    cout << endl << "What information do you want?" << endl;
    cout << "1 - Flights from the airport" << endl;
    cout << "2 - Airlines operating in the airport" << endl;
    cout << "3 - Different destinations with max flight number" << endl;

    cout << "Please enter your choice:" << endl;

    int choice, flight_n;
    cin >> choice;
    cout << endl;

    switch (choice) {
        case 1:
            cout << "Number of flights:" << a[code].size() << endl;
            cout << "Flights:" << endl;
            for (auto i : a[code]) {
                cout << code << "-" << i.getAirport() << " operated by: " << g.getAirlines()[i.getAirline()].getName() << endl;
            }
            break;
        case 2:
            cout << "Number of Airlines:" << g.getAirlinesFromAirport(code).size() << endl;
            cout << "Airlines:" << endl;
            for (auto i : g.getAirlinesFromAirport(code)) {
                cout << i << " - " << g.getAirlines()[i].getName() << endl;
            }
            break;
        case 3:
            cout << "Please enter max flight number:";
            cin >> flight_n;

            cout << endl << "Different destinations:" << endl;

            printAirport_flightN(g.targetAirports(code, flight_n));
            break;

        default:
            get_airport_info();
            break;
    }
}

void Menu::get_airline_info() {

    string airline_code;

    cout << "Please enter an airline code:";

    cin >> airline_code;
    cout << endl;

    Airline airline = g.getAirlines()[airline_code];

    cout << "Wich information do you want?" << endl;

    cout << "1 - Get all Airports an airline operates" << endl;

    cout << "Please enter your choice:" << endl;

    int choice;
    cin >> choice;
    cout << endl;

    switch (choice) {
        case 1:
            printAirport(airline.getAirlineairports());
    }
}

void Menu::get_articulation_points(){

    cout << "Number of Articulation points: " << g.getArticulationPoints().size() << endl;

    cout << "Articulation Points:" << endl;

    for (auto i : g.getArticulationPoints()) {
        cout << i << endl;
    }
}

void Menu::main_menu() {

    while (true) {
        cout << endl;
        cout << "|===========================================================================================|\n"
                "|                   Path                      |                   Airports                  |\n"
                "|=============================================|=============================================|\n"
                "| Get path with lowest flight number     [11] | Get information from specific Airport  [21] |\n"
                "|                                             |                                             |\n"
                "|=============================================|=============================================|\n"
                "|                 Airlines                    |                   Network                   |\n"
                "|=============================================|=============================================|\n"
                "| Get Airline information                [31] | Get articulation points                [41] |\n"
                "|                                             |                                             |\n"
                "|=============================================|=============================================|\n"
                "|               Other operations              |                                              \n"
                "|=============================================|                                              \n"
                "|  Exit                                   [0] |                                              \n"
                "|=============================================|\n";

        cout << endl;
        cout << "Please choose an option:";
        int option;
        cin >> option;
        cout << endl;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input" << endl;
            continue;
        }

       switch (option) {
            case 0: exit(0);
            case 11:
                get_path_flight();
                break;

           case 21:
               get_airport_info();
               break;


           case 31:
               get_airline_info();
               break;

           case 41:
               get_articulation_points();
               break;

            default: cout << "Invalid input" << endl;

        }

    }


}