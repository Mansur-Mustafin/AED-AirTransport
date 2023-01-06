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

    /*vector < vector<pss> > others ;

    ss qwe = g.getUltimatePath("KZN", "REC", {}, &others);

    vector <pair< vector<pss>, pair<int,int>> > qwe = g.getPathByPointsNOfFlights(48.858460646662465, 2.2944919807354034,40.68942019761322, -74.0444682077782,30,30,{});

    sort(qwe.begin(), qwe.end(), cmpF);

    for (int i = 0; i < qwe.size(); i++) {
        for(int j = 0; j < qwe[i].first.size(); j++){
            cout << qwe[i].first[j].first << "--(" << qwe[i].first[j].second << ")-->";
        }
        cout << endl << "   ";
        cout << "place1 to: " << qwe[i].first[0].first << "+/-" << qwe[i].second.first << "km; ";
        cout << qwe[i].first[qwe[i].first.size() - 1].first << " to place 2 +/-" << qwe[i].second.second << "km;";
        cout << endl;
    }*/




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