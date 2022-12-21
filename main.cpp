#include <vector>
#include <string>
#include <iostream>
#include "Code/Graph.h"

using namespace std;

int main() {

    Graph g;

    //vector <string> ans = g.getUltimatePath("OPO", "Russia");
    vector <string> ans = g.getPathAirports("PNZ", "LIS");
    //vector <string> ans = g.getPathCities("Green Bay", "Recife");
    //vector <string> ans = g.getPathCountries("United States","United Kingdom");
    //vector <string> ans = g.targetAirports("IOS", 1);
    //unordered_set<string> ans = g.getAirlinesFromAirport("IOS");
    //auto ans = g.getAirlines();
    //for(auto i : ans) cout << g.getAirlines()[i.first] << endl;

    for (auto i : ans) cout << i << endl;

    //cout << g.isCity("Porto");

    //for (int i = 0; i < ans.size(); i++) {  cout << ' ' << ans[i];  if (i != ans.size() - 1) cout << endl; }


    //cout << endl << g.getNumberOfFlights("IOS");
    return 0;

}

/*
 *
 */