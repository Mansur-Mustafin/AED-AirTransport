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

    in.close(); in.open("airlines.csv");
    getline(in, temp);

    while (getline(in, temp)) {
        Airline a(temp);
        string code = temp.substr(0, 3);
        airlines[code] = a;

    }

}


bool Graph::isCity(const string& name) {
    auto p = cities.find(name);
    if(p == cities.end()){
        return false;
    }
    return true;
}

bool Graph::isCountry(const string& name) {
    auto p = countries.find(name);
    if(p == countries.end()){
        return false;
    }
    return true;
}

unordered_map<string, Airline> Graph::getAirlines() {return airlines;}

unordered_map<string, vector<Target>> Graph::getG() {return g;}

unordered_map<string, Airport> Graph::getAirports() {return airports;}

unordered_map<string, unordered_set<string>> Graph::getCities() {return cities;}

unordered_map<string, unordered_set<string>> Graph::getCountries() {return countries;}

vector<string> Graph::getUltimatePath(string from, string to){

    vector <string> fromV;
    vector <string> toV;
    bool isCountryF = isCountry(from);
    bool isCountryT = isCountry(to);
    bool isCityF = isCity(from);
    bool isCityT = isCity(to);

    if(isCountryF){
        for(auto city : countries[from]){
            for(auto airport : cities[city]){
                fromV.push_back(airport);
            }
        }
    }

    if(isCountryT){
        for(auto city : countries[to]){
            for(auto airport : cities[city]){
                toV.push_back(airport);
            }
        }
    }

    if(isCityF){
        for(auto i : cities[from]) fromV.push_back(i);
    }

    if(isCityT){
        for(auto i : cities[to]) toV.push_back(i);
    }

    if(!isCityF && !isCountryF){
        fromV.push_back(from);
    }
    if(!isCityT && !isCountryT){
        toV.push_back(to);
    }

    vector <string> ans = getPathByVectors(fromV, toV);

    return ans;

}

vector<string> Graph::getPathAirports(const string& from, const string& to) {

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

vector<string> Graph::getPathCities(const string& from, const string& to) {

    vector <string> fromV;
    vector <string> toV;
    for(auto i : cities[from]) fromV.push_back(i);
    for(auto i : cities[to]) toV.push_back(i);

    vector <string> ans = getPathByVectors(fromV, toV);
    return ans;
}

vector<string> Graph::getPathCountries(const string& from, const string& to) {
    int best = -1;

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

    vector <string> ans = getPathByVectors(fromV, toV);

    return ans;
}

vector<string> Graph::targetAirports(const string& from, int num) {
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

vector <string> Graph::getPathByVectors(vector <string> from, vector <string> to){

    int best = -1;
    vector <string> ans;
    vector <string> temp;

    for (int i = 0; i < from.size(); i++)
        for (int j = 0; j < to.size(); j++) {

            string fromA = from[i];
            string toA = to[j];

            temp = getPathAirports(fromA , toA );

            if (temp.size() != 1 && (best == -1 || best > temp.size())) {
                best = temp.size();
                ans = temp;
            }
            if(temp.size() == 1 && temp[0][1] != 'o'){
                return temp;
            }
        }
    if(temp[0][1] == 'o' && ans.empty()){
        return temp;
    }
    return ans;
}

vector<string> Graph::getPathByPoint(double lat, double lon, double dist) /* FALTA ACABAR AQUIIIIIIIIIIIIIIIIIIIIIIII */   {

    vector <string> toV;
    for(auto e : airports){
        if(e.second.getDistanceTo(lat,lon) < dist){
            toV.push_back(e.first);
        }
    }
    return {};
}

unsigned int Graph::getNumberOfFlights(const std::string &Airport) {
    return g[Airport].size();
}

unordered_set<string> Graph::getAirlinesFromAirport(const std::string &Airport) {
    unordered_set<string> res;
    vector<Target> targets = g[Airport];
    for(auto t : targets){
        res.insert(t.getAirline());
    }
    return res;
}



list<string> Graph::getArticulationPoints() {
    unordered_map <string, bool> used;
    unordered_map <string, int> num;
    unordered_map <string, int> low;
    int index = 1;
    list<string> res;
    for(const auto& a : g){
        if(!used[a.first]){
            dfsArtificialP(a.first, num, low, index, used, res);
        }
    }
    return res;
}

void Graph::dfsArtificialP(const string& airport, unordered_map <string, int>& num, unordered_map <string, int>& low, int& index, unordered_map <string, bool>& used, list<string>& res) {
    bool a = false;
    int children = 0;
    num[airport] = low[airport] = index++; used[airport] = true;

    for(auto e : g[airport]){
        string w = e.getTarget();
        if(!used[w]){
            children++;
            dfsArtificialP(w, num, low, index, used, res);
            low[airport] = min(low[airport], low[w]);
            if(low[w] >= num[airport] && num[airport] > 1){
                a = true;
            }
        }else{
            low[airport] = min(low[airport], num[w]);
        }
    }
    if((num[airport] == 1 && children > 1) || (num[airport] > 1 && a)){
        res.push_back(airport);
    }

}
