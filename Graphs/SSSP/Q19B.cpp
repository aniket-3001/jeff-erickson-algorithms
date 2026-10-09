#include <bits/stdc++.h>
using namespace std;

int dijkstra(vector <vector <pair <int, int>>> &adj, int src, int target, int n, int k) {
    vector <int> dist(2*k*n + 1, INT_MAX);
    dist[src] = 0;
    priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        for (auto it : adj[node]) {
            int adjNode = it.first;
            int wt = it.second;

            if (dist[adjNode] > dist[node] + wt) {
                dist[adjNode] = dist[node] + wt;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }

    return min(dist[target], dist[target + k*n]);
}

int main() {
    int n, m;
    cin >> n >> m;

    int src, target;
    cin >> src >> target;

    int k;
    cin >> k;

    vector <vector <pair <int, int>>> adj(2*k*n + 1); // modified input graph

    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;

        for (int r = 0; r < k; r++) {
            // in order to get the vertex (u, r, 1), simply add k*n to (u, r, 0)

            // edges from (u, r, 0) -> (v, (r + wt) % k, 0) with weight wt
            adj[u + r*n].push_back({v + ((r + wt) % k)*n, wt});
            adj[v + r*n].push_back({u + ((r + wt) % k)*n, wt});

            // edges from (u, r, 0) -> (v, r, 1) with weight 0 (indicates free teleport way, thus no weight is added)
            adj[u + r*n].push_back({(v + r*n) + k*n, 0});
            adj[v + r*n].push_back({(u + r*n) + k*n, 0});

            // edges from (u, r, 1) -> (v, (r + wt) % k, 1) with weight wt
            adj[(u + r*n) + k*n].push_back({(v + ((r + wt) % k)*n) + k*n, wt});
            adj[(v + r*n) + k*n].push_back({(u + ((r + wt) % k)*n) + k*n, wt});
        }
    }

    int ans = dijkstra(adj, src, target, n, k);
    cout << (ans == INT_MAX ? -1 : ans) << endl;

    return 0;
}
