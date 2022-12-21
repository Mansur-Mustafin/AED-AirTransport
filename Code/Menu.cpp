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
    cout << "5 - Mix of data" << endl;

    int choice;
    cin >> choice;
    cout << endl;

    switch (choice) {
        case 1:
            string origin, dest;
            cout << "Please enter the origin city name:";
            cin >> origin;
            cout << endl;
            cout << "Please enter destination city name:";
            cin >> dest;

            vector<string> output = g.getPathCities(origin, dest);

            cout << "Your path is:" << endl;

            for (auto i : output) {
                cout << i << endl;
            }
    }

}

void Menu::main_menu() {

    while (true) {
        cout << endl;
        cout << "|===========================================================================================|\n"
                "|                   Path                      |                   Airports                  |\n"
                "|=============================================|=============================================|\n"
                "| Get path with lowest flight number     [11] |                                             |\n"
                "|                                             |                                             |\n"
                "|=============================================|=============================================|\n"
                "|                  Flights                    |                                             |\n"
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


            default: cout << "Invalid input" << endl;

        }

    }


}