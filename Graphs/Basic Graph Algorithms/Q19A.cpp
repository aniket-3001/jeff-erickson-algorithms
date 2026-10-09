#include <bits/stdc++.h>
using namespace std;

int BFS(vector <vector <int>> &adj, int V, int src, int target) {
    vector <int> dist(V + 1, INT_MAX);
    dist[src] = 0;
    queue <int> q;
    q.push(src);

    while (!q.empty()) {
        int node = q.front();
        int d = dist[node];
        q.pop();

        for (int adjNode: adj[node]) {
            if (dist[adjNode] > d + 1) {
                dist[adjNode] = d + 1;
                q.push(adjNode);
            }
        }
    }

    return dist[target];
}

int main() {
    int n, m;
    cin >> n >> m;

    vector <vector <int>> adj(2*n + 1); // adjacency list

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        // parity graph construction
        adj[u].push_back(v + n);
        adj[u + n].push_back(v);
        adj[v + n].push_back(u);
        adj[v].push_back(u + n);
    }

    int s, t; // Initial positions of the 2 coins
    cin >> s >> t;

    int ans = BFS(adj, 2*n, s, t);
    cout << (ans == INT_MAX ? -1 : ans/2) << endl;
}