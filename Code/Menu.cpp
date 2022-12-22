//
// Created by ianbe on 21/12/2022.
//

#include "Menu.h"

void Menu::main_menu() {

    while (true) {
        cout << endl;
        cout << "|===========================================================================================|\n"
                "|                  Flights                    |                   Airports                  |\n"
                "|=============================================|=============================================|\n"
                "|  See data from specific student        [11] |  See data from specific classes        [21] |\n"
                "|  Get number of students in a year      [12] |                                             |\n"
                "|  List Students with specific name      [13] |                                             |\n"
                "|  Show Students in year                 [14] |                                             |\n"
                "|=============================================|=============================================|\n"
                "|                    UC's                     |                   Requests                  |\n"
                "|=============================================|=============================================|\n"
                "|  See data from specific UC             [31] |  Request to change class               [41] |\n"
                "|  Show students with more than 'X' UCs  [32] |  Process requests (end of day)         [42] |\n"
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

        /*if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input" << endl;
            continue;
        }

       switch (option) {
            case 0: exit(0);
            case 11:
                students_operations();
                break;
            case 12:
                number_of_students_in_year_per_uc();
                break;
            case 13:
                students_with_name();
                break;
            case 14:
                show_students_in_year();
                break;
            case 21:
                classes_operations();
                break;
            case 31:
                uc_operations();
                break;
            case 32:
                students_with_more_uc();
                break;
            case 41:
                request_change_class();
                break;
            case 42:
                process_requests();
                break;

            default: cout << "Invalid input" << endl;

        }*/

    }


}