#include <bits/stdc++.h>
using namespace std;

vector <int> BFS(int src, vector <vector <int>> &adj, int V) {
    vector <int> dist(V + 1, INT_MAX);
    dist[src] = 0;

    queue <int> q;
    q.push(src);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int adjNode: adj[node]) {
            if (dist[adjNode] == INT_MAX) {
                dist[adjNode] = dist[node] + 1;
                q.push(adjNode);
            }
        }
    }

    return dist;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector <vector <int>> adj(V + 1);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
    }

    int src;
    cin >> src;

    
}