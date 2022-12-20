#include <vector>
#include <string>
#include <iostream>
#include "Code/Graph.h"

using namespace std;

int main() {

    Graph g;
    vector <string> ans = g.getPathCountries("United States", "Papua New Guinea");

    for (int i = 0; i < ans.size(); i++) {
        cout << ' ' << ans[i];
        if (i != ans.size() - 1) cout << endl;
    }
    return 0;
}
