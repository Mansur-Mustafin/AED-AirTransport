#include <string>
#include <iostream>
#include "Code/Graph.h"
#include "Code/Menu.h"
#include <cmath>
#include <fstream>
#include <chrono>

using namespace std;



int main() {

    Graph g;
    double d;
    ss ans = g.getPathByPoints(48.858460646662465, 2.2944919807354034, 48.858460646662465, 2.9 ,12, d);

    for(auto i : ans.first){
        cout << i << ' ';
    }
    cout << "distance: " << round(d) << endl;


    /*Graph g;

    vector < vector<pss> > others ;


    vector <vector <pss> > qwe;
    set<string> t;

    g.getAirports()["IST"].toInvalid();


    g.getUltimatePath("KZN", "REC", t, &qwe);

    for (int i = 0; i < qwe.size(); i++) {
        for (int j = 0; j < qwe[i].size(); j++)
            cout << qwe[i][j].first << "--(" << qwe[i][j].second << ")-->";
        cout << endl;
    }



    //ofstream cout("output.txt");
    //set<string> t ;
    //t.insert("KLM");

*/
    /*


    //cout << g.isStrangeCity("Kazan");




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