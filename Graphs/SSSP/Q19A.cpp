#include <bits/stdc++.h>
using namespace std;

vector <int> dijkstra(vector <vector <pair <int, int>>> &adj, int n, int src) {
    vector <int> dist(n + 1, INT_MAX);
    dist[src] = 0;
    priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto x : adj[u]) {
            int v = x.first;
            int wt = x.second;

            if (dist[v] > dist[u] + wt) {
                dist[v] = dist[u] + wt;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;

    int src, target;
    cin >> src >> target;

    int k;
    cin >> k;

    vector <vector <pair <int, int>>> adj(k*n + 1); // modified input graph

    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;

        for (int r = 0; r < k; r++) {
            adj[u + r*n].push_back({v + ((r + wt) % k)*n, wt});
            adj[v + r*n].push_back({u + ((r + wt) % k)*n, wt});
        }
    }

    vector <int> dist = dijkstra(adj, k*n, src);

    cout << dist[target] << endl;

    return 0;
}