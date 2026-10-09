#include <bits/stdc++.h>
using namespace std;

// In this variant, suppose at a time, both "must" move from their current vertex to an adjacent vertex. We will solve this by parity graph construction. That is the only optimal approach afaik. Uses the concept of an even length walk in a graph.

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

int main() {
    int V, E;
    cin >> V >> E;

    vector <vector <pair <int, int>>> adj(V + 1);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    int s, t;
    cin >> s >> t;

    vector <int> dist1 = dijkstra(s, adj, V);
    vector <int> dist2 = dijkstra(t, adj, V);
    int ans = INT_MAX;

    for (int i = 1; i <= V; i++) {
        ans = min(ans, dist1[i] + dist2[i]);
    }

    cout << ans << endl;

    return 0;
}