#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;
typedef long long ll;

ofstream cout("output.txt");

class Target {

    string target, airlane;

public:
    Target() : target(""), airlane("") {}
    Target(string target_, string airlane_) : target(target_), airlane(airlane_) {}

    string getTarget() {
        return target;
    }

    string getAirlane() {
        return airlane;
    }

};

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

class Airport {

public:
    string name, code, city, country, latitude, longitude;

    Airport() : name(""), code(""), city(""), country(""), latitude(""), longitude("") {}

    Airport(string in) {
        vector <string> temp = Help::Split(in);
        name = temp[0], city = temp[1], country = temp[2];
        latitude = temp[3], longitude = temp[4];
    }

};

class Graph {

public:
    unordered_map <string, vector <Target> > g; // ["asd"] = {"qwe", "sdf"}   g["any airport"].size() = количество вылетов из аэропорт
    unordered_map <string, Airport> Airports; // g["any airport"]  for => set (airline)
    unordered_map <string, vector <string> > cities;

public:

    Graph() {
        ifstream in("flights.csv");
        string temp;
        getline(in, temp);
        while (getline(in, temp)) {
            string source; Target t;
            Help::getFlight(source, t, temp);
            g[source].push_back(t);
        }

        in.close(); in.open("airports.csv");
        getline(in, temp);
        while (getline(in, temp)) {
            Airport a(temp.substr(4, temp.length() - 4));
            string code = temp.substr(0, 3);
            Airports[code] = a;
            cities[a.city].push_back(code);
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
            ans.back() = Airports[ans.back()].name;
            pass = p[pass];
        }

        ans.push_back(Airports[from].name);
        reverse(ans.begin(), ans.end());

        return ans;
    }

    vector <string> targetAirports(string from, int num) {

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
        for (auto i = t.begin(); i != t.end(); i++)
            ans.push_back(*i);

        return ans;

    }
};


int main() {

    Graph g;
    vector <string> ans = g.targetAirports("IOS", 1);

    cout << g.g["IOS"].size() << endl;

    for (int i = 0; i < ans.size(); i++) {
        cout << i + 1 << ' ' << ans[i];
        if (i != ans.size() - 1) cout << endl;
    }

    return 0;
}
