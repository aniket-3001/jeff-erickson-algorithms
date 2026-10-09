#include <bits/stdc++.h>
using namespace std;

vector <int> dijkstra(int src, vector <vector <pair <int, int>>> &adj, int V) {
    vector <int> dist(V + 1, INT_MAX);
    dist[src] = 0;

    priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto x : adj[u]) {
            int v = x.first;
            int weight = x.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int numPaths(int node, int t, vector <vector <pair <int, int>>> &adj, int V, vector <int> &dp) {
    if (node == t) {
        return 1;
    }

    if (dp[node] != -1) {
        return dp[node];
    }

    int ans = 0;

    for (auto it: adj[node]) {
        int adjNode = it.first;
        ans += numPaths(adjNode, t, adj, V, dp);
    }

    return dp[node] = ans;
}

int main() {
    int V, E;

    vector <vector <pair <int, int>>> adj(V + 1);
    vector <vector <int>> edges(E + 1);

    for (int i = 1; i <= E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        adj[u].push_back({v, w});
    }

    int s, t;
    cin >> s >> t;

    vector <int> dist = dijkstra(s, adj, V);

    // Now, we find all the tight edges so that we can obtain the shortest path tree

    vector <vector <int>> tree(V + 1);

    for (int i = 1; i <= E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if (dist[v] == dist[u] + w) {
            tree[u].push_back(v);
        }
    }

    return 0;
}