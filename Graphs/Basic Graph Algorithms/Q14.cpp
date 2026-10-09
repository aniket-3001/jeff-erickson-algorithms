#include <bits/stdc++.h>
using namespace std;

void DFS(vector <vector <int>> &adj, int node, vector <int> &visited) {
    visited[node] = 1;

    for (int adjNode: adj[node]) {
        if (!visited[adjNode]) {
            DFS(adj, adjNode, visited);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    int s, t;
    cin >> s >> t;

    vector <vector <int>> adj(3*n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v + n);
        adj[u + n].push_back(v + 2*n);
        adj[u + 2*n].push_back(v);
    }

    vector <int> visited(3*n + 1, 0);

    DFS(adj, s, visited);

    if (visited[t]) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}