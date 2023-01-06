#include <string>
#include <iostream>
#include "Code/Graph.h"
#include "Code/Menu.h"
#include <cmath>
#include <fstream>
#include <chrono>

using namespace std;


bool cmpF(pair< vector<pss>, pair<int,int>> p1, pair< vector<pss>, pair<int,int>> p2){
    return p1.second.first + p1.second.second < p2.second.first + p2.second.second;
}


int main() {



    Graph g;


    vector <vector <pss> > qwe;
    set<string> t;


    g.getUltimatePath("PMI", "KIR", t, &qwe);

    for (int i = 0; i < qwe.size(); i++) {
        for (int j = 0; j < qwe[i].size(); j++)
            cout << qwe[i][j].first << "--(" << qwe[i][j].second << ")-->";
        cout << endl;
    }


    //ofstream cout("output.txt");
    //set<string> t ;
    //t.insert("KLM");


    /*


    //cout << g.isStarageCiti("Kazan");




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
        //menu.main_menu();
    }
    catch (exception& e) {
        cout << e.what() << '\n';
    }

    return 0;

}