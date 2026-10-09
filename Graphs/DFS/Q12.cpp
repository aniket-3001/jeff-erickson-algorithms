#include <bits/stdc++.h>
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    vector <int> weight(V + 1);

    for (int i = 1; i <= V; i++) {
        cin >> weight[i];
    }

    vector <vector <int>> adj(V + 1);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    // a) Describe an algorithm to determine the shortest interval of time in which all jobs in G can be executed.

    return 0;
}