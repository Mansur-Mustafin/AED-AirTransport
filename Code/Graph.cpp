//
// Created by musta on 20.12.2022.
//

#include "Graph.h"
#include "Flight.h"

Graph::Graph() {
    string temp;


    ifstream in("airlines.csv");
    getline(in, temp);

    while (getline(in, temp)) {
        Airline a(temp);
        string code = temp.substr(0, 3);
        airlines[code] = a;
        t.insert(a.getCode());
    }


    in.close(); in.open("flights.csv");
    getline(in, temp);

    while (getline(in, temp)) {
        n_of_flights++;
        Flight f = Flight(temp);
        g[f.getSource()].push_back(f.getTarget());
        airlines[f.getTarget().getAirline()].addAirport(f.getTarget().getAirport());
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


bool Graph::isCity(const string& name) {
    auto p = cities.find(name);
    if (p == cities.end()) {
        return false;
    }
    return true;
}

bool Graph::isCountry(const string& name) {
    auto p = countries.find(name);
    if (p == countries.end()) {
        return false;
    }
    return true;
}

int Graph::get_global_n_flight() { return n_of_flights;}

unordered_map<string, Airline> Graph::getAirlines() { return airlines; }

unordered_map<string, vector<Target>> Graph::getG() { return g; }

unordered_map<string, Airport> Graph::getAirports() { return airports; }

unordered_map<string, unordered_set<string>> Graph::getCities() { return cities; }

unordered_map<string, unordered_set<string>> Graph::getCountries() { return countries; }

ss Graph::getUltimatePath(string from, string to, set <string> Comp, vector < vector<pss> >* others) {
    Comp = Comp.empty() ? t : Comp;
    vector <string> fromV;
    vector <string> toV;
    bool isCountryF = isCountry(from);
    bool isCountryT = isCountry(to);
    bool isCityF = isCity(from);
    bool isCityT = isCity(to);

    if (isCountryF) {
        for (const auto& city : countries[from]) {
            for (const auto& airport : cities[city]) {
                fromV.push_back(airport);
            }
        }
    }

    if (isCountryT) {
        for (const auto& city : countries[to]) {
            for (const auto& airport : cities[city]) {
                toV.push_back(airport);
            }
        }
    }

    if (isCityF) {
        for (const auto& i : cities[from]) fromV.push_back(i);
    }

    if (isCityT) {
        for (const auto& i : cities[to]) toV.push_back(i);
    }

    if (!isCityF && !isCountryF) {
        fromV.push_back(from);
    }
    if (!isCityT && !isCountryT) {
        toV.push_back(to);
    }

    ss ans = getPathByVectors(fromV, toV, Comp, others);

    return ans;

}

vector <vector <pss> > fill(const string& from, const string& to, unordered_map <string, vector <string> >& p, unordered_map <string, vector <string> >& pAir, int d) {

    vector <vector <string> > ans = { {to} }, ansAir = { {"No airport"} };

    for (int i = 0; i < d; i++) {
        vector <vector <string> > temp, temp2;
        int pos = 0;
        for (auto elem : ans) {
            int j = 0;
            for (auto path : p[elem.back()]) {
                vector <string> tt = elem, tt2 = ansAir[pos];
                tt.push_back(path);
                tt2.push_back(pAir[elem.back()][j]);
                temp.push_back(tt);
                temp2.push_back(tt2);
                j++;
            }
            pos++;
        }
        ans = temp;
        ansAir = temp2;
    }

    vector < vector <pss> > result(ans.size());

    for (int i = 0; i < ans.size(); i++) {
        result[i].resize(ans[i].size());
        for (int j = 0; j < ans[i].size(); j++)
            result[i][j] = { ans[i][j], ansAir[i][j] };
        reverse(result[i].begin(), result[i].end());
    }
    return result;
}

ss Graph::getPathAirports(const string& from, const string& to, set <string> Comp, vector < vector<pss> >* others) {

    Comp = Comp.empty() ? t : Comp;

    unordered_map <string, bool> used;
    unordered_map <string, vector <string > > p, pAirlane;
    unordered_map <string, int> d;
    queue <string> q;
    q.push(from);
    d[q.front()] = 0;
    used[q.front()] = true;

    while (!q.empty()) {

        string cur = q.front();
        q.pop();

        for (auto i = 0; i < g[cur].size(); i++) {
            string target = g[cur][i].getAirport(), air = g[cur][i].getAirline();
            if ((!used[target] || d[cur] + 1 == d[target]) && Comp.find(air) != Comp.end()) {
                if (!used[target])
                    q.push(target);
                d[target] = d[cur] + 1;
                p[target].push_back(cur);
                pAirlane[target].push_back(air);
                used[target] = true;
            }
        }
    }

    if (!used[to])
        return { {"No path exist"}, {} };

    string pass = to;
    vector <string> ans, ansAir;
    while (pass != from) {
        ans.push_back(pass);
        ans.back() = airports[ans.back()].getName();
        ansAir.push_back(pAirlane[pass][0]);
        pass = p[pass][0];
    }

    ans.push_back(airports[from].getName());

    reverse(ans.begin(), ans.end());
    reverse(ansAir.begin(), ansAir.end());
    ansAir.push_back("No airline");

    if (others != nullptr) 
        *others = fill(from, to, p, pAirlane, d[to]);
    return { ans, ansAir };
}

vector<string> Graph::targetAirports(const string& from, int num,  set <string> Comp) {

    Comp = Comp.empty() ? t : Comp;

    unordered_set <string> t;
    unordered_map <string, bool> used;
    queue <pair <string, int> > q;
    q.push({ from, 0 });

    while (!q.empty()) {

        pair <string, int> cur = q.front();
        q.pop();

        for (auto i = 0; i < g[cur.first].size(); i++) {
            string target = g[cur.first][i].getAirport(), air = g[cur.first][i].getAirline();
            if (!used[target] && cur.second < num && Comp.find(air) != Comp.end()) {
                t.insert(target);
                q.push({ target, cur.second + 1 });
                used[target] = true;
            }
        }
    }

    vector <string> ans;
    for (const auto& i : t)
        ans.push_back(i);
    return ans;
}

ss Graph::getPathByVectors(vector <string> from, vector <string> to, set <string> Comp, vector < vector<pss> >* others) {

    int best = -1;
    ss ans;
    ss temp;
    vector < vector<pss> > tempOthers;

    for (int i = 0; i < from.size(); i++) {
        for (int j = 0; j < to.size(); j++) {

            string fromA = from[i];
            string toA = to[j];

            temp = getPathAirports(fromA, toA, Comp, &tempOthers);

            if (temp.first.size() != 1 && (best == -1 || best > temp.first.size())) {
                best = temp.first.size();
                *others = tempOthers;
                ans = temp;
            }
        }
    }

    return ans;
}

vector<string> Graph::getPathByPoint(string from, double lat, double lon, double dist) /* FALTA ACABAR AQUIIIIIIIIIIIIIIIIIIIIIIII */ {

    vector <string> toV;
    for (auto e : airports) {
        if (e.second.getDistanceTo(lat, lon) < dist) {
            toV.push_back(e.first);
        }
    }
    return {};
}

unsigned int Graph::getNumberOfFlights(const std::string& Airport) {
    return g[Airport].size();
}

unordered_set<string> Graph::getAirlinesFromAirport(const std::string& Airport) {
    unordered_set<string> res;
    vector<Target> targets = g[Airport];
    for (auto t : targets) {
        res.insert(t.getAirline());
    }
    return res;
}

list<string> Graph::getArticulationPoints(set <string> Comp) {
    unordered_map <string, bool> used;
    unordered_map <string, int> num, low;
    int index = 1;
    list<string> res;
    for (const auto& a : g) {
        if (!used[a.first]) {
            dfsArtificialP(a.first, num, low, index, used, res, Comp);
        }
    }
    return res;
}

void Graph::dfsArtificialP(const string& airport, unordered_map <string, int>& num, unordered_map <string, int>& low, int& index, unordered_map <string, bool>& used, list<string>& res, const set <string>& Comp) {

    bool a = false;
    int children = 0;
    num[airport] = low[airport] = index++; used[airport] = true;

    for (auto e : g[airport]) {
        string w = e.getAirport(), air = e.getAirline();
        if (!used[w] && Comp.find(air) != Comp.end()) {
            children++;
            dfsArtificialP(w, num, low, index, used, res, Comp);
            low[airport] = min(low[airport], low[w]);
            if (low[w] >= num[airport] && num[airport] > 1) {
                a = true;
            }
        }
        else {
            low[airport] = min(low[airport], num[w]);
        }
    }
    if ((num[airport] == 1 && children > 1) || (num[airport] > 1 && a)) {
        res.push_back(airport);
    }

}

int Graph::diameterBFS(string airport, set<string> Comp){
    int max = -1;
    unordered_map <string, bool> used;
    unordered_map <string, int> d;
    queue <string> q;
    q.push(airport);
    d[airport] = 0;

    while (!q.empty()) {

        string cur = q.front(); q.pop();

        for (auto i = 0; i < g[cur].size(); i++) {
            string target = g[cur][i].getAirport(), air = g[cur][i].getAirline();
            if (!used[target] && Comp.find(air) != Comp.end()) {
                    q.push(target);
                    d[target] = d[cur] + 1;
                    if(d[target] > max){
                        max = d[target];
                    }
                    used[target] = true;
            }
        }
    }
    return max; // temos que verificar se for -1???????????????????
}

// for(auto i : airports){ ou nao?
int Graph::getDiameter( set<string> Comp) {
    int max = -1;
    for(auto i : airports){
        int temp = diameterBFS(i.first, Comp);
        if(temp > max){
            max = temp;
        }
    }
    return max;
}

