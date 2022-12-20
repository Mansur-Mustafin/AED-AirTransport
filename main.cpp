#include <vector>
#include <string>
#include <iostream>
#include "Code/Graph.h"

using namespace std;

/*
class Target {
    string target, airline;
public:
    Target() : target(""), airline("") {}
    Target(string target_, string airline_) : target(target_), airline(airline_) {}

    string getTarget() {
        return target;
    }

    string getAirline() {
        return airline;
    }
};
*/
/*
class Flight{
private:
    string  source;
    Target target;
public:

    Flight() : target(Target()), source("") {}

    Flight(string in){
        string feel, feel2;
        istringstream input(in);
        getline(input, feel, ','); // name
        source = feel;
        getline(input, feel, ','); // name
        getline(input, feel2, ','); // name
        target = Target(feel, feel2);

    }

    Target getTarget() {
        return target;
    }

    string getSource(){
        return source;
    }
};
*/
/*
class Help {

public:
    void static getFlight(string& source, Target& t, string in) {
        source = in.substr(0, 3);
        t = Target(in.substr(4, 3), in.substr(8, 3));
    }

    vector <string> static Split(string s) {
        s += ",";
        vector <string> ans;
        int start = 0;
        for (int i = 0; i < s.length(); i++)
            if (s[i] == ',') {
                ans.push_back(s.substr(start, i - start));
                start = i + 1;
            }
        return ans;
    }
};
*/
/*
class Graph {

public:
    unordered_map <string, vector <Target> > g; // ["asd"] = {"qwe", "sdf"}   g["any airport"].size() = количество вылетов из аэропорт
    unordered_map <string, Airport> Airports; // g["any airport"]  for => set (airline)
    unordered_map <string, vector <string> > cities;

public:

    Graph() {
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
            Airports[code] = a;
            cities[a.getCity()].push_back(code);
            // countries["country"].push_back("city")
        }
    }


    vector <string> getPathCities(string from, string to) {
        int best = -1;
        vector <string> ans;
        for (int i = 0; i < cities[from].size(); i++)
            for (int j = 0; j < cities[to].size(); j++) {
                vector <string> temp = getPath(cities[from][i], cities[to][j]);
                if (temp.size() != 1 && (best == -1 || best > temp.size())) {
                    best = temp.size();
                    ans = temp;
                }
            }
        return ans;
    }


    vector <string> getPath(string from, string to) {
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
            ans.back() = Airports[ans.back()].getName();
            pass = p[pass];
        }

        ans.push_back(Airports[from].getName());
        reverse(ans.begin(), ans.end());

        return ans;
    }

    vector <string> targetAirports(string from, int num) {                // todos aeroportos que podemos ir de um aeroporto para outro por n passos

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
};

*/

int main() {

    Graph g;
    vector <string> ans = g.getPath("JFK", "MAG");

    for (int i = 0; i < ans.size(); i++) {
        cout << ' ' << ans[i];
        if (i != ans.size() - 1) cout << endl;
    }

    return 0;
}
