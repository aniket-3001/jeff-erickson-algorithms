#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int V, int src) {
    vector<int> dist(V + 1, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// Function to check if a node is reachable from the source node
bool reachabilityDFS(int node, vector <vector <pair <int, int>>> &adj, vector <int> &visited, int target) {
    if (node == target) {
        return true;
    }

    visited[node] = 1;

    for (auto it: adj[node]) {
        int adjNode = it.first;
        
        if (!visited[adjNode]) {
            if (reachabilityDFS(adjNode, adj, visited, target)) {
                return true;
            }
        
        }
    }

    return false;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int, int>>> adj1(V + 1); // G
    vector<vector<pair<int, int>>> adj2(V + 1); // G'
    // difference between G and G' is that G' has one less edge than G, and that edge is a negative edge, which we would call u -> v

    tuple<int, int, int> negativeEdge;
    cin >> get<0>(negativeEdge) >> get<1>(negativeEdge) >> get<2>(negativeEdge);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        if (u == get<0>(negativeEdge) && v == get<1>(negativeEdge) && w == get<2>(negativeEdge)) {
            adj1[u].push_back({v, w});
            continue;
        }

        adj1[u].push_back({v, w});
        adj2[u].push_back({v, w});
    }

    int s, t;
    cin >> s >> t;

    // First of all we check if there is a path from s to t
    vector<int> visited(V + 1, 0);
    
    if (!reachabilityDFS(s, adj1, visited, t)) {
        cout << "UNREACHABLE" << endl;
        return 0;
    }

    // Determine if G contains a negative cycle because of the negative edge
    // We can do this by applying Dijkstra algorithm on G', since we need to compute dist'(v, u) + wt(u, v)

    vector<int> dist1 = dijkstra(adj2, V, get<1>(negativeEdge));

    if (dist1[get<0>(negativeEdge)] == INT_MAX) {
        // means that u is not reachable from v, in this case, there is no cycle (forget about negative weight cycle), so we can just apply dijkstra on G with s as src
        vector<int> dist = dijkstra(adj1, V, s);
        cout << dist[t] << endl;
    }

    if (get<2>(negativeEdge) + dist1[get<0>(negativeEdge)] < 0) {
        // If we reach here, it means that there is a negative cycle in G

        vector<int> visited(V + 1, 0);

        // Now, we need to check if there is any path from s to t that would encounter a vertex present in the negative cycle

        bool res1 = reachabilityDFS(s, adj1, visited, get<0>(negativeEdge));
        visited.assign(V + 1, 0);
        bool res2 = reachabilityDFS(get<0>(negativeEdge), adj1, visited, t);

        if (res1 && res2) {
            // If there is a path from s to u and u to t, then the distance would be -INFINITY
            cout << "INFINITY" << endl;
        }
        else {
            // If there is no path from s to t such that it encounters any vertex of the negative cycle, then the minimum distance would be the distance from s to t
            vector<int> dist = dijkstra(adj2, V, s);
            cout << dist[t] << endl;
        }

    }
    else {
        // We wish to compute the minimum distance between s and t. Our recurrence in case of no negative cycle would be as follows.

        // dist(s, t) = min(dist'(s, t), dist'(s, u) + wt(u, v) + dist'(v, t))

        // apply dijkstra on G' with s as src
        vector<int> dist2 = dijkstra(adj2, V, s);

        int ans = min(dist2[t], dist2[get<0>(negativeEdge)] + get<2>(negativeEdge) + dist1[t]);

        cout << ans << endl;
    }

    return 0;
}