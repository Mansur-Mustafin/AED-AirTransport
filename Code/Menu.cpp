//
// Created by ianbe on 21/12/2022.
//

#include <iomanip>
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

bool cmp_dis_airport(pair<string, pair<int, double>> p1, pair<string, pair<int, double>> p2) {
    if (p1.second.first == p2.second.first) {
        return p1.second.second < p2.second.second;
    }
    return p1.second.first < p2.second.first;
}

template <class T>
T findFunc( T start, T end, const Airport& airport) {
    while(start != end){
        if(start->first == airport.getCountry()){
            return start;
        }
        start++;
    }
    return end;
}

void Push(vector<string> &v, string s){
    if(find(v.begin(), v.end(), s) == v.end()){
        v.push_back(s);
    }
}

void Menu::printAirport_flightN(const vector <string>& inputAirports) {

    list<Airport> lstAirports;
    for(auto a : inputAirports){
        lstAirports.push_back(g.getAirports()[a]);
    }

    cout << "How would you like to sort the list?" << endl;

    cout << "1 - Sort by more popularity" << endl;
    cout << "2 - Sort by alphabetic order" << endl;

    cout << "Please enter your choice:" << endl;

    int choice_sort;
    cin >> choice_sort;
    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input" << endl << endl;
        main_menu();
    }

    switch (choice_sort) {
        case 1:
            lstAirports.sort([this](Airport a1, const Airport& a2) -> bool
                             {
                                 if(g.getNumberOfFlights(a1.getCode()) > g.getNumberOfFlights(a2.getCode())) return true;
                                 else if(g.getNumberOfFlights(a1.getCode()) < g.getNumberOfFlights(a2.getCode())) return false;
                                 else return a1.getCountry() < a2.getCountry();
                             });
            break;
        case 2:
            lstAirports.sort([this](Airport a1, const Airport& a2) -> bool{
                if(a1.getCountry() < a2.getCountry()) return true;
                else if(a1.getCountry() > a2.getCountry())return false;
                else if(a1.getCity() < a2.getCity())return true;
                else return false;
            });
            break;
        default:
            break;
    }


    unordered_map<string, vector<string>> countries;
    unordered_map<string, list<Airport>> cities;
    list<string> restCountries;


    for(auto a : lstAirports){
        if(countries.find(a.getCountry()) == countries.end()){
            restCountries.push_back(a.getCountry());
        }
        Push(countries[a.getCountry()], a.getCity());
        cities[a.getCity()].push_back(a);
    }

    int n_cities = 0;

    cout  << "Different destinations:" << endl;

    for(auto it = restCountries.begin(); it != restCountries.end(); it++){
        cout << *it << endl;

        for(auto city : countries[*it]){
            cout << "|-----" << city << endl;
            n_cities++;
            for(auto air: cities[city]){
                cout << "      |------" << air.getCode() << endl;
            }
        }
        cout << endl;
    }



    cout << "Number of Airports: " << inputAirports.size() << endl;
    cout << "Number of countries: " << restCountries.size() << endl;
    cout << "Number of cities: " << n_cities << endl;

}

void Menu::printAirport(unordered_set<string> airports, string code) {
    unordered_map <string, unordered_map <string, vector<Airport>>> by_country;

    for (auto i : airports) {
        Airport a = g.getAirports()[i];
        by_country[a.getCountry()][a.getCity()].push_back(a);
    }

    int city_n = 0;

    for (auto i : by_country) {
        if (i.first.size() != 0) {
            cout << i.first << endl;
            city_n += i.second.size();
            for (auto j : i.second) {
                cout << " |-----" << j.first << endl;
                for (auto c : j.second) {
                    cout << "         |-----" << c.getName()<< ": ("  << c.getCode() << ')' << endl;
            }
        }
        cout << endl;
    }}

    cout << "Number of flights: " << g.get_airline_flightN(code) << endl;
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

    cout << "Which kind of data do you have?" << endl;
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
        main_menu();
    }

    string origin, dest;

    double lat1, lon1, lat2, lon2, dist1, dist2;

    pair <vector <string>, vector<string> > output;

    vector <pair< vector<pss>, pair<int,int>> > output_c;

    vector <vector<pair <string, string>>> others;

    switch (choice) {
        case 1:
            cout << "Please enter the origin data:";
            cin.ignore();
            getline(cin, origin);
            cout << endl;

            cout << "Please enter destination data:";
            getline(cin, dest);
            cout << endl;


            output = g.getUltimatePath(origin, dest, airlines, &others);
            break;


        case 2:
            cout << "Please enter the origin latitude:";
            cin >> lat1;
            cout << endl;

            cout << "Please enter origin longitude:";
            cin >> lon1;
            cout << endl;

            cout << "Please enter the destination latitude:";
            cin >> lat2;
            cout << endl;

            cout << "Please enter destination longitude:";
            cin >> lon2;
            cout << endl;

            cout  << "Please enter max distance to origin airport:";
            cin >> dist1;
            cout << endl;

            cout << "Please enter max distance to destination airport:";
            cin >> dist2;
            cout << endl;

            output_c = g.getPathByPointsNOfFlights(lat1,lon1,lat2,lon2, dist1, dist2, airlines);

            for (int i = 0; i < output_c.size(); i++) {
                for(int j = 0; j < output_c[i].first.size(); j++){
                    cout << output_c[i].first[j].first;
                    if (j != output_c[i].first.size()-1) cout << "--(" << output_c[i].first[j].second << ")-->";
                }
                cout << endl << "   ";
                cout << "Origin to: " << output_c[i].first[0].first << " +/- " << output_c[i].second.first << "Km; ";
                cout << output_c[i].first[output_c[i].first.size() - 1].first << " to destination +/- " << output_c[i].second.second << "Km;";
                cout << endl;
            }

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

            cout << endl << "How would you like to sort the list?" << endl;

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
                main_menu();
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

            int n = (int) others.size();

            if (n >= 20) {
                cout << "Output is long. How many lines would you like to display?" << endl;
                cout << "Enter 0 for all lines." << endl;

                int lines;

                cin >> lines;

                if (lines != 0) n = lines;
            }


            int counter = 0;

            for (auto i : airline_dis) {
                if(counter < n) cout << i.first << " | " << i.second.second << "Km total distance | " << i.second.first << " airline changes" << endl;
                else break;
                counter++;
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

void Menu::get_path_airline(){



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

    string origin, dest;

    cout << "Please enter origin airport code: ";
    cin >> origin;



    cout << endl << "Please enter destination airport code: ";
    cin >> dest;
    cout << endl;


    vector <vector <pss> > others = g.getPathByAirportsAirlines(origin, dest, airlines);

    vector<pair<string, pair<int, double>>> airline_dis;



    for (int i = 0; i < others.size(); i++) {
        double distance = 0.0;
        pair<string, pair<int, double>> pair;
        list<string> airports;
        string x;
        for (int j = 0; j < others[i].size(); j++) {
            x += others[i][j].first;
            airports.push_back(x);
            if (j != others[i].size()-1) {
                distance += g.getAirports()[others[i][j].first].getDistanceTo(g.getAirports()[others[i][j+1].first].getLatitude(), g.getAirports()[others[i][j+1].first].getLongitude());
                x += "--(" + others[i][j].second + ")-->";
            }
        }
        pair.first = x;
        pair.second.first = airports.size();
        pair.second.second = distance;

        airline_dis.push_back(pair);
    }


    std::sort(airline_dis.begin(), airline_dis.end(), cmp_dis_airport);

    int n = (int) airline_dis.size();

    if (n >= 20) {
        cout << "Output is long. How many lines would you like to display?" << endl;
        cout << "Enter 0 for all lines." << endl;

        int lines;

        cin >> lines;

        if (lines != 0) n = lines;
    }


    int counter = 0;

    for (auto i : airline_dis) {
        if(counter < n) cout << i.first << " | " << i.second.second << "Km total distance" << endl;
        else break;
        counter++;
    }


}


void Menu::settings() {

    cout << "Which setting would you like to change?" << endl;

    cout << "1 - Lock place" << endl;
    cout << "2 - Unlock place" << endl;

    cout << "Please choose one:" << endl;

    int settings_choice;

    cin >> settings_choice;

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input" << endl << endl;
        main_menu();
    }

    cout << "1 - City" << endl;
    cout << "2 - Airport" << endl;

    cout << "Please choose one:" << endl;

    int block_choice;

    cin >> block_choice;

    cout << endl;

    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input" << endl << endl;
        main_menu();
    }

    cout << "How many places would you like to change?" << endl;

    int n_places;

    cin >> n_places;

    if (block_choice == 1) {
        for (int i = 0; i < n_places; i++) {
            cout << "Please enter a city name: ";

            string city_name;

            cin.ignore();
            getline(cin, city_name);

            if (settings_choice == 1) g.swithToInvalidCity(city_name);
            else g.swithToValidCity(city_name);
        }
    }else if (block_choice == 2) {
        for (int i = 0; i < n_places; i++) {
            cout << "Please enter a airport code: ";

            string airport_code;

            cin >> airport_code;

            if (settings_choice == 1) g.switchToInvalid(airport_code);
            else g.switchToValid(airport_code);
        }
    }else {
        cout << "Invalid input";
        main_menu();
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
        main_menu();
    }

    Airport airport = g.getAirports()[code];

    set<string> countries, cities;

    switch (choice) {
        case 1:
            cout << "Airport name - " << airport.getName() << endl;
            cout << "Airport location - " << airport.getCity() << ", " << airport.getCountry() << endl;
            cout << "(latitude, longitude) = (" << airport.getLatitude() << " ," << airport.getLongitude() << ")" << endl;
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
            cout << "Airlines:" << endl;
            for (auto i : g.getAirlinesFromAirport(code)) {
                cout << i << " - " << g.getAirlines()[i].getName() << endl;
            }
            cout << "Number of Airlines:" << g.getAirlinesFromAirport(code).size() << endl;
            break;
        case 4:
            cout << "Please enter max flight number:";
            cin >> flight_n;

            cout << endl;

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

    cout << "Which information do you want?" << endl;

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
        main_menu();
    }

    switch (choice) {
        case 1:
            cout << "Airline name: " << airline.getName() << endl;
            cout << "Airline call sign: " << airline.getCallsign() << endl;
            cout << "Airline country: " << airline.getCountry() << endl;
            break;

        case 2:
            printAirport(airline.getAirlineairports(), airline_code);
            break;

        default:
            get_airline_info();
    }
}

void Menu::top_k_airports() {

    cout << "How many airports would you like to see? " ;

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
        main_menu();
    }

    if (choice == 2) {
        std::sort(vector_p.begin(), vector_p.end(), top_airports_airline);
    }else {
        std::sort(vector_p.begin(), vector_p.end(), top_airports_flight);
    }

    for (int i = 1; i <= n; i++) {
        if(i > 9){
            cout << i;
        }else{
            cout << setfill(' ')  << left << setw(2) << i;
        }

         cout  << " - "<< setfill(' ')  << left << setw(35) << vector_p[i].first.getName() << " | " << vector_p[i].second.first << " flights | " << vector_p[i].second.second << " airlines" << endl;
    }



}

void Menu::get_network_info() {

    string airline_choice;

    set <string> airlines;

    int c = 0;

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
        main_menu();
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

            cout << endl << "Articulation Points:" << endl;

            for (auto i : g.getArticulationPoints(airlines)) {
                c++;
                cout << i << endl;
            }

            cout << "Number of Articulation points: " << c << endl;
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

void Menu::get_country_statistics() {

    string country;

    cout << "Please enter country name: ";

    cin.ignore();
    getline(cin, country);

    cout << endl;

    int flight_from = 0;

    /*
    for (auto a : g.getAirports()) {
        if (a.second.getCountry() == country) {
            airport_n++;
            flight_from += g.getNumberOfFlights(a.first);
        }
    }
*/

    int airport_n = 0;
    unordered_map <string, unordered_set<string> > countries = g.getCountries();
    unordered_map <string, unordered_map <string, unordered_set<string> > > data = g.getDataStrangeCities();

    for(const auto& city : countries[country]){
        unordered_set<string> airports = g.getCities()[city];
        airport_n += airports.size();
        for(auto a : airports){
            flight_from += g.getNumberOfFlights(a);
        }
    }

    for(const auto& city: data[country]){
        airport_n += city.second.size();
        for(auto i : city.second){
            flight_from += g.getNumberOfFlights(i);
        }
    }



    int n_cuties = g.getCountries()[country].size() + g.getDataStrangeCities()[country].size();

    cout << "Number of cities: " << n_cuties << endl;
    cout << "Number of airports: " << airport_n << endl;
    cout << "Number of flights originating in the country: " << flight_from << endl;
}

void Menu::main_menu() {

    while (true) {
        cout << endl;
        cout << "|===========================================================================================|\n"
                "|                   Path                      |                   Airports                  |\n"
                "|=============================================|=============================================|\n"
                "| Get path with lowest flight number     [11] | Get information from specific Airport  [21] |\n"
                "| Get path with fewest airline change    [12] |                                             |\n"
                "| Change searching settings              [13] |                                             |\n"
                "|                                             |                                             |\n"
                "|=============================================|=============================================|\n"
                "|                 Airlines                    |                   Network                   |\n"
                "|=============================================|=============================================|\n"
                "| Get Airline information                [31] | Get network info                       [41] |\n"
                "|                                             | Get country statistics                 [42] |\n"
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

            case 12:
                get_path_airline();
                break;

            case 13:
                settings();
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

            case 42:
                get_country_statistics();
                break;

            default: cout << "Invalid input" << endl;

        }

    }


}