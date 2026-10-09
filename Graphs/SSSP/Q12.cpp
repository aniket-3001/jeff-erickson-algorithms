#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int src, vector<vector<pair<int, int>>> &adj, int V) {
    vector<int> dist(V + 1, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
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

vector<vector<int>> shortestPath(int src, int V, int E, vector<vector<int>> &adj) {
    queue<pair<int, int>> q;
    vector<int> dist(V + 1, INT_MAX), parent(V + 1);

    for (int i = 1; i <= V; i++) {
        parent[i] = i;
    }

    dist[src] = 0;
    q.push({0, src});

    while (!q.empty()) {
        auto it = q.front();
        q.pop();
        int node = it.second;
        int distance = it.first;

        for (auto adjNode : adj[node]) {
            if (distance + 1 < dist[adjNode]) {
                dist[adjNode] = distance + 1;
                q.push({dist[adjNode], adjNode});
                parent[adjNode] = node;
            }
        }
    }

    vector<vector<int>> path(V + 1);

    for (int i = 1; i <= V; i++) {
        int node = i;

        if (dist[node] == INT_MAX) {
            path[node] = {-1};
        } else {
            int temp = node;

            while (parent[temp] != temp) {
                path[node].push_back(temp);
                temp = parent[temp];
            }

            path[node].push_back(src);
            reverse(path[node].begin(), path[node].end());
        }
    }

    return path;
}

int main() {
    int V, E;
    cin >> V >> E; // Read number of vertices and edges

    vector<vector<pair<int, int>>> adj(V + 1);
    vector<vector<int>> edges(E + 1);

    for (int i = 1; i <= E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        adj[u].push_back({v, w});
    }

    int src;
    cin >> src; // Read source vertex

    vector<int> dist = dijkstra(src, adj, V);

    // Now, we find all the tight edges so that we can obtain the shortest path tree

    vector<vector<int>> tree(V + 1);

    for (int i = 1; i <= E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if (dist[v] == dist[u] + w) {
            tree[u].push_back(v);
        }
    }

    vector<vector<int>> ans = shortestPath(src, V, E, tree);

    for (int i = 1; i <= V; i++) {
        cout << "Shortest path from node " << src << " to node " << i << ": ";

        for (int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";
        }
        
        cout << endl;
    }

    return 0;
}
