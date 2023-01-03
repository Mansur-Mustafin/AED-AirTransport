#include <string>
#include <iostream>
#include "Code/Graph.h"
#include "Code/Menu.h"
#include <fstream>
#include <chrono>

using namespace std;

int main() {

    /*
    Graph g;

    auto begin = std::chrono::high_resolution_clock::now();

    vector <vector <pss> > qwe = g.getPathByAirportsAirlines("KZN", "CMP");

    for (int i = 0; i < qwe.size(); i++) {
        for (int j = 0; j < qwe[i].size(); j++)
            cout << qwe[i][j].first << "--(" << qwe[i][j].second << ")-->";
        cout << endl;
    }


    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);


    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
*/

    //ofstream cout("output.txt");
    //set<string> t ;
    //t.insert("KLM");
    /*


    //cout << g.isStarageCiti("Kazan");

    vector <vector <pss> > qwe;


    //ss asd = g.getPathAirports("RDC", "CMP", {}, &qwe);
    //ss asd = g.getUltimatePath("London", "REC", {}, &qwe);
    //ss asd = g.getPathByVectors({"KZN"}, {"LIS", "OPO"}, {}, &qwe);
    //for (int i = 0; i < asd.first.size(); i++)
      //cout << asd.first[i]  << "--(" << asd.second[i]<< ")-->" ;

   /* cout<< endl << "------------------------------------------" << endl;

    for (int i = 0; i < qwe.size(); i++) {
        for (int j = 0; j < qwe[i].size(); j++)
            cout << qwe[i][j].first << "--(" << qwe[i][j].second << ")-->";
        cout << endl;
    }*/






    // PERGUNTAR AQUI

    try {
        Menu menu;
        menu.main_menu();
    }
    catch (exception& e) {
        cout << e.what() << '\n';
    }


    return 0;

}