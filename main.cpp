#include <string>
#include <iostream>
#include "Code/Graph.h"
#include "Code/Menu.h"

using namespace std;

int main() {

    Graph g;

    unordered_set <string> t;
    vector <vector <string> > qwe;
    t.insert("TOK");
    vector <string> zxc = g.getPathAirports("HGU", "TBG",  t,&qwe);



    for (auto & i : qwe) {
        for (auto & j : i)
            cout << j << "->";
        cout << endl;
    }

    cout << endl;

    //auto l = g.getArticulationPoints();
    //cout << "------------" << endl;
    //for(auto e : l) cout << e << endl;

    //for(auto e : g.getG()){
        //cout << e.first << endl;
      //  break;
    //}


    //vector <string> ans = g.getUltimatePath("CMP", "Russia");


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

    //Menu menu;
    //menu.main_menu();

    //cout << g.isCity("Porto");

    //for (int i = 0; i < ans.size(); i++) {  cout << ' ' << ans[i];  if (i != ans.size() - 1) cout << endl; }


    //cout << endl << g.getNumberOfFlights("IOS");
    return 0;

}