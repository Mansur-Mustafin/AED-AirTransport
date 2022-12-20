//
// Created by musta on 20.12.2022.
//

#include "Graph.h"
#include "Flight.h"

Graph::Graph() {
    string temp;

    ifstream in("flights.csv");
    getline(in, temp);


    while (getline(in, temp)) {
        //string source; Target t;
        Flight f = Flight(temp);

        //Help::getFlight(source, t, temp);
        g[f.getSource()].push_back(f.getTarget());
    }


    in.close(); in.open("airports.csv");
    getline(in, temp);

    while (getline(in, temp)) {
        Airport a(temp);
        string code = temp.substr(0, 3);
        airports[code] = a;
        cities[a.getCity()].insert(code);
        countries[a.getCountry()].insert(a.getCity());
    }
}

unordered_map<string, vector<Target>> Graph::getG() {return g;}

unordered_map<string, Airport> Graph::getAirports() {return airports;}

unordered_map<string, unordered_set<string>> Graph::getCities() {return cities;}

unordered_map<string, unordered_set<string>> Graph::getCountries() {return countries;}

vector<string> Graph::getPath(std::string from, std::string to) {
    unordered_map <string, bool> used;
    unordered_map <string, string> p; // p["asd"] = "qwe"
    queue <string> q;
    q.push(from);
    while (!q.empty()) {

        string cur = q.front();
        q.pop();

        for (auto i = 0; i < g[cur].size(); i++) {
            string target = g[cur][i].getTarget();
            if (!used[target]) {
                q.push(target);
                used[target] = true;
                p[target] = cur;
            }
        }
    }
    if (used[to] == false)
        return {"No path exists"};
    string pass = to;
    vector <string> ans;
    while (pass != from) {
        ans.push_back(pass);
        ans.back() = airports[ans.back()].getName();
        pass = p[pass];
    }

    ans.push_back(airports[from].getName());
    reverse(ans.begin(), ans.end());

    return ans;
}

vector<string> Graph::getPathCities(std::string from, std::string to) {
    int best = -1;
    vector <string> ans;
    vector <string> fromV;
    vector <string> toV;
    for(auto i : cities[from]) fromV.push_back(i);
    for(auto i : cities[to]) toV.push_back(i);

    for (int i = 0; i < fromV.size(); i++)
        for (int j = 0; j < toV.size(); j++) {

            string from = fromV[i];
            string to = toV[j];

            vector <string> temp = getPath(from , to );

            if (temp.size() != 1 && (best == -1 || best > temp.size())) {
                best = temp.size();
                ans = temp;
            }
        }
    return ans;
}

vector<string> Graph::getPathCountries(std::string from, std::string to) {
    int best = -1;
    vector <string> ans;
    vector <string> fromV;
    vector <string> toV;

    for(auto city : countries[from]){
        for(auto airport : cities[city]){
            fromV.push_back(airport);
        }
    }

    for(auto city : countries[to]){
        for(auto airport : cities[city]){
            toV.push_back(airport);
        }
    }


    for (int i = 0; i < fromV.size(); i++)
        for (int j = 0; j < toV.size(); j++) {

            string from = fromV[i];
            string to = toV[j];

            vector <string> temp = getPath(from , to );

            if (temp.size() != 1 && (best == -1 || best > temp.size())) {
                best = temp.size();
                ans = temp;
            }
        }
    return ans;
}

vector<string> Graph::targetAirports(std::string from, int num) {
    unordered_set <string> t;
    unordered_map <string, bool> used;
    queue <pair <string, int> > q;
    q.push({ from, 0 });

    while (!q.empty()) {

        pair <string, int> cur = q.front();
        q.pop();

        for (auto i = 0; i < g[cur.first].size(); i++) {
            string target = g[cur.first][i].getTarget();
            if (!used[target] && cur.second < num) {
                t.insert(target);
                q.push({ target, cur.second + 1 });
                used[target] = true;
            }
        }
    }

    vector <string> ans;
    for (const auto & i : t)
        ans.push_back(i);

    return ans;
}

