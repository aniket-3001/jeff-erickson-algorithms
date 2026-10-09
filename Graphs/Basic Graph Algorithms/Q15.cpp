#include <bits/stdc++.h>
using namespace std;

vector <int> BFS(vector <vector <int>> &adj, int src, int V) {
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

    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;

    int k; // number of red edges
    cin >> k;

    int src, target;
    cin >> src >> target;

    vector <pair <int, int>> red(m), blue(m - k);

    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;

        if (c == 'R') {
            red[i] = {u, v};
        } else {
            blue[i - k] = {u, v};
        }
    }

    vector <vector <int>> adj(4*n + 1);

    /*
    vertex types:
    1) reachable from 2 consecutive red edges
    2) reachable from 2 consecutive blue edges
    3) reachable from 1 red edge
    4) reachable from 1 blue edge

    for some vertex u,
    (u, red1) is represented as u
    (u, red2) is represented as u + n
    (u, blue1) is represented as u + 2*n
    (u, blue2) is represented as u + 3*n
    */

    // add red edges
    for (int i = 0; i < k; i++) {
        int u = red[i].first, v = red[i].second;
        
        if (u == src) {
            adj[u].push_back(v);
        }
        else {
            adj[u].push_back(v + n);
            adj[u + 2*n].push_back(v);
            adj[u + 3*n].push_back(v);
        }
    }

    for (int i = 0; i < m - k; i++) {
        int u = blue[i].first, v = blue[i].second;

        if (u == src) {
            adj[u].push_back(v + 2*n);
        }
        else {
            adj[u].push_back(v + 2*n);
            adj[u + n].push_back(v + 2*n);
            adj[u + 2*n].push_back(v + 3*n);
        }
    }

    // We need to find the shortest path from src to all versions of target, i.e. target, target + n, target + 2*n, target + 3*n

    vector <int> dist = BFS(adj, src, 4*n);

    int ans = min(min(dist[target], dist[target + n]), min(dist[target + 2*n], dist[target + 3*n]));

    cout << (ans == INT_MAX ? -1 : ans) << endl;

    return 0;
}