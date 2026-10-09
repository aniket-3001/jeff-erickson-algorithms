#include <bits/stdc++.h>
using namespace std;

vector<int> BFS(vector<vector<int>> &adj, int V, int src) {
    vector<int> dist(V + 1, INT_MAX);
    dist[src] = 0;
    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int node = q.front();
        int d = dist[node];
        q.pop();

        for (int adjNode : adj[node]) {
            if (dist[adjNode] > d + 1) {
                dist[adjNode] = d + 1;
                q.push(adjNode);
            }
        }
    }

    return dist;
}

bool checkPossibility(vector<int> &dist1, vector<int> &dist2, vector<int> &dist3, int x, int y, int z, int n) {
    return (dist1[x] != INT_MAX && dist2[y] != INT_MAX && dist3[z] != INT_MAX) ||
        (dist1[x] != INT_MAX && dist2[z] != INT_MAX && dist3[y] != INT_MAX) ||
        (dist1[y] != INT_MAX && dist2[x] != INT_MAX && dist3[z] != INT_MAX) ||
        (dist1[y] != INT_MAX && dist2[z] != INT_MAX && dist3[x] != INT_MAX) ||
        (dist1[z] != INT_MAX && dist2[x] != INT_MAX && dist3[y] != INT_MAX) ||
        (dist1[z] != INT_MAX && dist2[y] != INT_MAX && dist3[x] != INT_MAX) ||
        (dist1[x + n] != INT_MAX && dist2[y + n] != INT_MAX && dist3[z + n] != INT_MAX) ||
        (dist1[x + n] != INT_MAX && dist2[z + n] != INT_MAX && dist3[y + n] != INT_MAX) ||
        (dist1[y + n] != INT_MAX && dist2[x + n] != INT_MAX && dist3[z + n] != INT_MAX) ||
        (dist1[y + n] != INT_MAX && dist2[z + n] != INT_MAX && dist3[x + n] != INT_MAX) ||
        (dist1[z + n] != INT_MAX && dist2[x + n] != INT_MAX && dist3[y + n] != INT_MAX) ||
        (dist1[z + n] != INT_MAX && dist2[y + n] != INT_MAX && dist3[x + n] != INT_MAX);
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(2 * n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v + n);
        adj[u + n].push_back(v);
        adj[v + n].push_back(u);
        adj[v].push_back(u + n);
    }

    int a, b, c;
    cin >> a >> b >> c;

    int x, y, z;
    cin >> x >> y >> z;

    vector<int> dist1 = BFS(adj, 2 * n, a);
    vector<int> dist2 = BFS(adj, 2 * n, b);
    vector<int> dist3 = BFS(adj, 2 * n, c);

    bool possible = checkPossibility(dist1, dist2, dist3, x, y, z, n);

    if (possible) {
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    }

    return 0;
}
