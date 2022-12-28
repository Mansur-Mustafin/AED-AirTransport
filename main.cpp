#include <string>
#include <iostream>
#include "Code/Graph.h"
#include "Code/Menu.h"
#include <fstream>

using namespace std;


int main() {

    //ofstream cout("output.txt");
    //set<string> t ;
    //t.insert("KLM");

    Graph g;

    vector <vector <pss> > qwe;

    //ss asd = g.getPathAirports("KZN", "REC", {}, &qwe);
    ss asd = g.getUltimatePath("RDC", "KZN", {}, &qwe);
    //ss asd = g.getPathByVectors({"KZN"}, {"LIS", "OPO"}, {}, &qwe);
    for (int i = 0; i < asd.first.size(); i++)
      cout << asd.first[i]  << "--(" << asd.second[i]<< ")-->" ;

    cout<< endl << "------------------------------------------" << endl;

    for (int i = 0; i < qwe.size(); i++) {
        for (int j = 0; j < qwe[i].size(); j++)
            cout << qwe[i][j].first << "--(" << qwe[i][j].second << ")-->";
        cout << endl;
    }

    /*

        vector <vector <string> > qwe;
        vector <string> zxc = g.getPathAirports("KZN", "THU", t, &qwe);

        for(auto i : zxc) cout << i << "-->";
        cout << endl;
        for (auto & i : qwe) {
            for (int j = 0; j < i.size(); j++)
                cout << i[j] << "->";
            cout << endl;
        }

        cout << endl;
    */

    //auto l = g.getArticulationPoints();
    //cout << "------------" << endl;
    //for(auto e : l) cout << e << endl;

    //for(auto e : g.getG()){
    //cout << e.first << endl;
    //  break;
    //}


    //vector <string> ans = g.getUltimatePath("KZN", "THU");
    //vector <string> ans = g.getUltimatePath("Brazil", "LIS");
    //vector <string> ans = g.getPathAirports("IOS", "HNL");
    //vector <string> ans = g.getUltimatePath("RDC", "FLW");
    //vector <string> ans = g.getPathAirports("RDC", "FLW");
    //vector <string> ans = g.getPathCities("Recife", "London");
    //vector <string> ans = g.getPathCountries("Brazil","Portugal");
    //unordered_set<string> ans = g.getAirlinesFromAirport("IOS");
    //auto ans = g.getAirlines();
    //for(auto i : ans) cout << g.getAirlines()[i.first] << endl;
    //unordered_map <string, Airport> ans = g.getAirports();
    //unordered_map <string, unordered_set<string> > ans = g.getCountries();

    //for (auto i : ans) cout << i << endl;

    /*for (auto i : ans) {

        cout << i.first << endl;

        for (auto j : i.second) {
            cout << j << endl;
        }

        cout << endl;
        cout << endl;

    }*/

    // PERGUNTAR AQUI

    //try {
    //    Menu menu;
    //    //menu.main_menu();
    //}
    //catch (exception& e) {
    //    cout << e.what() << '\n';
    //}



    //cout << g.isCity("Porto");

    //for (int i = 0; i < ans.size(); i++) {  cout << ' ' << ans[i];  if (i != ans.size() - 1) cout << endl; }


    //cout << endl << g.getNumberOfFlights("IOS");
    return 0;

}