#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int src, vector<vector<int>> &adj, int V, vector<int> &weight, int target) {
    vector<int> dist(V + 1, INT_MAX), parent(V + 1);

    for (int i = 1; i <= V; i++) {
        parent[i] = i;
    }

    dist[src] = weight[src];

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({dist[src], src});

    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        for (int adjNode : adj[node]) {
            int adjNodeWeight = weight[adjNode];

            if (dist[adjNode] > dist[node] + adjNodeWeight) {
                dist[adjNode] = dist[node] + adjNodeWeight;
                pq.push({dist[adjNode], adjNode});
                parent[adjNode] = node;
            }
        }
    }

    vector <int> path;
    int temp = target;

    if (dist[target] == INT_MAX) {
        return {-1};
    }
    else {
        while (parent[temp] != temp) {
            path.push_back(temp);
            temp = parent[temp];
        }

        path.push_back(src);
        reverse(path.begin(), path.end());
    }

    return path;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V + 1);
    vector<int> weights(V + 1);

    // adjacency list
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // weight array
    for (int i = 1; i <= V; i++) {
        cin >> weights[i];
    }

    int s, t;
    cin >> s >> t;

    // Find shortest path from s to t
    vector<int> shortestPath = dijkstra(s, adj, V, weights, t);

    for (int i = 0; i < shortestPath.size(); i++) {
        cout << shortestPath[i] << " ";
    }

    cout << "\n";

    return 0;
}
