//
// Created by ianbe on 21/12/2022.
//

#include "Menu.h"

bool top_airports_flight(pair<Airport, pair<int, int>> p1, pair<Airport, pair<int, int>> p2) {
    return p1.second.first > p2.second.first;
}

bool top_airports_airline(pair<Airport, pair<int, int>> p1, pair<Airport, pair<int, int>> p2) {
    return p1.second.second > p2.second.second;
}

bool cmp_airline(pair<string, pair<int, double>> p1, pair<string, pair<int, double>> p2) {
    return p1.second.first < p2.second.first;
}

bool cmp_distance(pair<string, pair<int, double>> p1, pair<string, pair<int, double>> p2) {
    return p1.second.second < p2.second.second;
}

void Menu::printAirport_flightN(vector <string> airports) {


    sort(airports.begin(), airports.end(), [this](const string& a1, const string& a2) -> bool
    {
        return g.getNumberOfFlights(a1) > g.getNumberOfFlights(a2);
    });

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

        if (n_airlines == 0) {

            cout << "No path exists" << endl << endl;

            main_menu();
        }

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

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input" << endl << endl;
        get_path_flight();
    }

    string origin, dest;

    double lat, lon, dist;

    pair <vector <string>, vector<string> > output;

    vector<string> output_c;

    vector <vector<pair <string, string>>> others;

    switch (choice) {
        case 1:
            cout << "Please enter the origin data:";
            cin >> origin;
            cout << endl;

            cout << "Please enter destination data:";
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

            //output_c = g.getPathByPoint(lat, lon, dist, others);
            break;

        default:
            get_path_flight();
    }

    cout << endl << "Would you like to see all possible paths with the lowest flight number? (y/n)" << endl;

    string print_choice;
    cin >> print_choice;

    vector<pair<string, pair<int, double>>> airline_dis;


    if (output.first.size() > 0) {
        if (print_choice == "Y" || print_choice == "y") {

            for (int i = 0; i < others.size(); i++) {
                double distance = 0.0;
                pair<string, pair<int, double>> pair;
                list<string> airlines;
                string x;
                for (int j = 0; j < others[i].size(); j++) {
                    x += others[i][j].first;
                    if (j != others[i].size()-1) {
                        distance += g.getAirports()[others[i][j].first].getDistanceTo(g.getAirports()[others[i][j+1].first].getLatitude(), g.getAirports()[others[i][j+1].first].getLongitude());
                        x += "--(" + others[i][j].second + ")-->";
                        if (others[i][j].second != airlines.back()) {
                            airlines.push_back(others[i][j].second);
                        }
                    }
                }
                pair.first = x;
                pair.second.first = airlines.size()-1;
                pair.second.second = distance;

                airline_dis.push_back(pair);
            }

            cout << "How would you like to sort the list?" << endl;

            cout << "1 - Sort by airline change" << endl;
            cout << "2 - Sort by distance" << endl;

            cout << "Please enter your choice:" << endl;

            int choice_sort;
            cin >> choice_sort;
            cout << endl;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input" << endl << endl;
                get_path_flight();
            }

            switch (choice_sort) {
                case 1:
                    std::sort(airline_dis.begin(), airline_dis.end(), cmp_airline);
                    break;
                case 2:
                    std::sort(airline_dis.begin(), airline_dis.end(), cmp_distance);
                    break;
                default:
                    break;
            }

            for (auto i : airline_dis) {
                cout << i.first << " | " << i.second.second << " Km's total distance | " << i.second.first << " airline changes" << endl;
            }


        }else {
            for (int i = 0; i < output.first.size(); i++) {
                cout << output.first[i];
                if (i != output.first.size()-1) {
                    cout << "--(" << g.getAirlines()[output.second[i]].getName() << ")-->";
                }
            }
        }
    } else {
        cout << "No path exists" << endl;
    }
}



void Menu::get_airport_info() {

    cout << "Please enter airport code:";

    string code;
    cin >> code;

    if (g.getAirports().find(code) == g.getAirports().end()) {
        cout << "Airport does not exist" << endl;
        main_menu();
    }

    unordered_map<string, vector<Target>> a = g.getG();

    cout << endl << "What information do you want?" << endl;
    cout << "1 - Basic Airport information" << endl;
    cout << "2 - Flights from the airport" << endl;
    cout << "3 - Airlines operating in the airport" << endl;
    cout << "4 - Different destinations with max flight number" << endl;

    cout << "Please enter your choice:" << endl;

    int choice, flight_n;
    cin >> choice;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input" << endl << endl;
        get_airport_info();
    }

    Airport airport = g.getAirports()[code];

    set<string> countries, cities;

    switch (choice) {
        case 1:
            cout << "Airport name - " << airport.getName() << endl;
            cout << "Airport location - " << airport.getCity() << ", " << airport.getCountry() << endl;
            break;
        case 2:
            cout << endl << "Flights:" << endl;
            for (auto i : a[code]) {
                countries.insert(g.getAirports()[i.getAirport()].getCountry());
                cities.insert(g.getAirports()[i.getAirport()].getCity());

                cout << code << "-" << i.getAirport() << " operated by: " << g.getAirlines()[i.getAirline()].getName() << endl;
            }
            cout << endl << "Number of flights: " << a[code].size() << endl;
            cout << "Number of countries: " << countries.size() << endl;
            cout << "Number of cities: " << cities.size() << endl;
            break;
        case 3:
            cout << "Number of Airlines:" << g.getAirlinesFromAirport(code).size() << endl;
            cout << "Airlines:" << endl;
            for (auto i : g.getAirlinesFromAirport(code)) {
                cout << i << " - " << g.getAirlines()[i].getName() << endl;
            }
            break;
        case 4:
            cout << "Please enter max flight number:";
            cin >> flight_n;

            cout << endl << "Different destinations:" << endl;

            printAirport_flightN(g.targetAirports(code, flight_n));
            break;

        default:
            get_airport_info();
    }
}

void Menu::get_airline_info() {

    string airline_code;

    cout << "Please enter an airline code:";

    cin >> airline_code;
    cout << endl;

    Airline airline = g.getAirlines()[airline_code];

    if (g.getAirlines().find(airline_code) == g.getAirlines().end()) {
        cout << "Airline does not exist" << endl;
        main_menu();
    }

    cout << "Wich information do you want?" << endl;

    cout << "1 - Get basic Airline info" << endl;
    cout << "2 - Get all Airports an airline operates" << endl;

    cout << "Please enter your choice:" << endl;

    int choice;
    cin >> choice;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input" << endl << endl;
        get_airline_info();
    }

    switch (choice) {
        case 1:
            cout << "Airline name: " << airline.getName() << endl;
            cout << "Airline callsign: " << airline.getCallsign() << endl;
            cout << "Airline country: " << airline.getCountry() << endl;
            break;

        case 2:
            printAirport(airline.getAirlineairports());
            break;

        default:
            get_airline_info();
    }
}

void Menu::top_k_airports() {

    cout << "How many airports would you like to see?";

    int n;
    cin >> n;

    unordered_map<string, Airport> airports = g.getAirports();

    vector<pair<Airport, pair<int, int>>> vector_p;

    for (auto i : airports) {
        pair<Airport, pair<int, int>> flight_airline_n;

        flight_airline_n.first = i.second;
        flight_airline_n.second.first = g.getNumberOfFlights(i.first);
        flight_airline_n.second.second = g.getAirlinesFromAirport(i.first).size();

        vector_p.push_back(flight_airline_n);
    }

    cout << "How would you like to sort the list?" << endl;

    cout << "1 - Number of flights" << endl;
    cout << "2 - Number of Airlines" << endl;

    cout << "Please enter your choice:" << endl;

    int choice;
    cin >> choice;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input" << endl << endl;
        get_airline_info();
    }

    if (choice == 2) {
        std::sort(vector_p.begin(), vector_p.end(), top_airports_airline);
    }else {
        std::sort(vector_p.begin(), vector_p.end(), top_airports_flight);
    }

    for (int i = 0; i < n; i++) {
        cout << i+1 << " - "<< vector_p[i].first.getName() << " | " << vector_p[i].second.first << " flights | " << vector_p[i].second.second << " airlines" << endl;
    }



}

void Menu::get_network_info() {

    string airline_choice;

    set <string> airlines;


    cout << "What information do you want?" << endl;

    cout << "1 - Get global statistics" << endl;
    cout << "2 - Get articulation points" << endl;
    cout << "3 - Get Network diameter" << endl;
    cout << "4 - Get top K airports" << endl;

    cout << "Please enter your choice:" << endl;

    int choice;
    cin >> choice;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input" << endl << endl;
        get_network_info();
    }

    if (choice == 2 || choice == 3) {
        cout << "Do you want to use specific airlines to check the network? (y/n)" << endl;

        cin >> airline_choice;

        if (airline_choice == "Y" || airline_choice == "y") {
            int n_airlines;

            cout << "How many airlines do you want to use?" << endl;

            cin >> n_airlines;

            cout << endl;

            if (n_airlines == 0) {

                cout << "Input error" << endl;
                main_menu();
            }

            for (int i = 0; i < n_airlines; i++) {
                string al;

                cout << i+1 << " - " << "Please enter an airline code:" << endl;

                cin >> al;

                cout << endl;

                airlines.insert(al);
            }
        }
    }

    switch (choice) {
        case 1:
            cout << "Global number of Airports: " << g.getAirports().size() << endl;
            cout << "Global number of Airlines: " << g.getAirlines().size() << endl;
            cout << "Global number of flights: " << g.get_global_n_flight() << endl;
            break;
        case 2:
            cout << "Number of Articulation points: " << g.getArticulationPoints().size() << endl;

            cout << endl << "Articulation Points:" << endl;

            for (auto i : g.getArticulationPoints(airlines)) {
                cout << i << endl;
            }
            break;
        case 3:
            cout << g.getDiameter(airlines) << " is the network diameter" << endl;
            break;
        case 4:
            top_k_airports();
            break;
        default:
            get_network_info();
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
                "| Get Airline information                [31] | Get network info                       [41] |\n"
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
                get_network_info();
                break;

            default: cout << "Invalid input" << endl;

        }

    }


}