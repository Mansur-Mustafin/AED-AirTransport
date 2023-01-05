#include <string>
#include <iostream>
#include "Code/Graph.h"
#include "Code/Menu.h"
#include <fstream>
#include <chrono>

using namespace std;

int main() {


    Graph g;

    vector < vector<pss> > others ;

    ss qwe = g.getUltimatePath("KZN", "REC", {}, &others);


    for (int i = 0; i < others.size(); i++) {
        for(int j = 0; j < others[i].size(); j++){
            //cout << others[i][j].first << "--(" << others[i][j].second << ")-->";
        }
        //cout << endl;
    }




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