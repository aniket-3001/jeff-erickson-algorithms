#include <bits/stdc++.h>
using namespace std;

int BFS(vector <vector <int>> &adj, int n, int s, int t) {
    vector <int> dist(n + 1, INT_MAX);
    dist[s] = 0;
    queue <int> q;
    q.push(s);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int adjNode : adj[node]) {
            if (dist[adjNode] > dist[node] + 1) {
                dist[adjNode] = dist[node] + 1;
                q.push(adjNode);
            }
        }
    }

    return dist[t];
}

int main() {
    int n, m;
    cin >> n >> m;

    int s, t;
    cin >> s >> t;

    int k;
    cin >> k;

    vector <vector <int>> adj(k*n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;

        for (int r = 0; r < k; r++) {
            adj[u + r*n].push_back(v + ((r + wt) % k)*n);
            adj[v + r*n].push_back(u + ((r + wt) % k)*n);
        }
    }

    int ans = BFS(adj, k*n, s, t);
    cout << ans << endl;

    return 0;
}