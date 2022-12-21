#include <vector>
#include <string>
#include <iostream>
#include "Code/Graph.h"

using namespace std;

int main() {

    Graph g;

    //vector <string> ans = g.getUltimatePath("Porto", "Kazan");
    //vector <string> ans = g.getPathAirports("IOS", "HNL");
    //vector <string> ans = g.getPathCities("Kazan", "Moscow");
    //vector <string> ans = g.getPathCountries("Kyrgyzstan","Kyrgyzstan");
    //vector <string> ans = g.targetAirports("IOS", 1);
    unordered_set<string> ans = g.getAirlinesFromAirport("IOS");
    for(auto i : ans) cout << g.getAirlines()[i] << endl;


    //for (int i = 0; i < ans.size(); i++) {  cout << ' ' << ans[i];  if (i != ans.size() - 1) cout << endl; }


    //cout << endl << g.getNumberOfFlights("IOS");
    return 0;

}

/*
 *
 */