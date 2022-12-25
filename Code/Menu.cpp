//
// Created by ianbe on 21/12/2022.
//

#include "Menu.h"

void Menu::get_path_flight() {

    cout << "Wich kind of data do you have?" << endl;
    cout << "1 - City names" << endl;
    cout << "2 - Country names" << endl;
    cout << "3 - Coordinates " << endl;
    cout << "4 - Airport codes" << endl;
    cout << "5 - Mix of data (not coordinates)" << endl;

    cout << "Please enter your choice:" << endl;

    int choice;
    cin >> choice;
    cout << endl;

    string origin, dest;

    double lat, lon, dist;

    vector<string> output;

    switch (choice) {
        case 1:
            cout << "Please enter the origin city name:";
            cin >> origin;
            cout << endl;

            cout << "Please enter destination city name:";
            cin >> dest;

            output = g.getPathCities(origin, dest);
            break;

        case 2:
            cout << "Please enter the origin country name:";
            cin >> origin;
            cout << endl;
            cout << "Please enter destination country name:";
            cin >> dest;
            cout << endl;

            output = g.getPathCountries(origin, dest);
            break;

        case 3:
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

        case 4:
            cout << "Please enter the origin airport code:";
            cin >> origin;
            cout << endl;
            cout << "Please enter destination airport code:";
            cin >> dest;
            cout << endl;

            output = g.getPathAirports(origin, dest);
            break;

        case 5:
            cout << "Please enter the data from origin:";
            cin >> origin;
            cout << endl;
            cout << "Please enter data from destination:";
            cin >> dest;
            cout << endl;

            output = g.getUltimatePath(origin, dest);
            break;

        default:
            get_path_flight();
            break;
    }

    cout << endl << "Your path is:" << endl;

    for (auto i : output) {
        cout << i << endl;
    }

}

void Menu::get_airport_info() {

    cout << "Please enter airport code:";

    string code;
    cin >> code;

    unordered_map<string, vector<Target>> a = g.getG();

    cout << endl << "What information do you want?" << endl;
    cout << "1 - Number of flights from the airport" << endl;
    cout << "2 - Flights from the airport" << endl;
    cout << "3 - Number of airlines operating in the airport" << endl;
    cout << "4 - Airlines operating in the airport" << endl;
    cout << "5 - Number of different destinations with max flight number" << endl;
    cout << "6 - Different destinations with max flight number" << endl;

    cout << "Please enter your choice:" << endl;

    int choice, flight_n;
    cin >> choice;
    cout << endl;

    switch (choice) {
        case 1:
            cout << "Number of flights:" << endl;
            cout << a[code].size() << endl;
            break;

        case 2:
            cout << "Flights:" << endl;
            for (auto i : a[code]) {
                cout << code << "-" << i.getAirport() << " operated by: " << g.getAirlines()[i.getAirline()].getName() << endl;
            }
            break;
        case 3:
            cout << "Number of Airlines:" << endl;
            cout << g.getAirlinesFromAirport(code).size() << endl;
            break;
        case 4:
            cout << "Airlines:" << endl;
            for (auto i : g.getAirlinesFromAirport(code)) {
                cout << i << endl;
            }
            break;
        case 5:
            cout << "Please enter max flight number:";
            cin >> flight_n;

            cout << endl << "Number of different destinations:" << endl;
            cout << g.targetAirports(code, flight_n).size() << endl;
            break;
        case 6:
            cout << "Please enter max flight number:";
            cin >> flight_n;

            cout << endl << "Different destinations:" << endl;
            for (auto i : g.targetAirports(code, flight_n)) {
                cout << g.getAirports()[i] << endl;
            }
            break;

        default:
            get_airport_info();
            break;
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
                "|                 Airlines                    |                                             |\n"
                "|=============================================|=============================================|\n"
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

            default: cout << "Invalid input" << endl;

        }

    }


}