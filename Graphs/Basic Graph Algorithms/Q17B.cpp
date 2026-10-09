#include <bits/stdc++.h>
using namespace std;

int BFS(vector <vector <int>> &adj, int src, int target, int n, int k) {
    vector <int> dist(2*k*n + 1, INT_MAX);
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

    return min(dist[target], dist[target + k*n]);
}

int main() {
    int n, m;
    cin >> n >> m;

    int src, target;
    cin >> src >> target;

    int k;
    cin >> k;

    vector <vector <int>> adj(2*k*n + 1); // modified input graph

    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;

        for (int r = 0; r < k; r++) {
            // in order to get the vertex (u, r, 1), simply add k*n to (u, r, 0)

            // edges from (u, r, 0) -> (v, (r + wt) % k, 0)
            adj[u + r*n].push_back(v + ((r + wt) % k)*n);
            adj[v + r*n].push_back(u + ((r + wt) % k)*n);

            // edges from (u, r, 0) -> (v, r, 1) (indicate free teleport way)
            adj[u + r*n].push_back((v + r*n) + k*n);
            adj[v + r*n].push_back((u + r*n) + k*n);

            // edges from (u, r, 1) -> (v, (r + wt) % k, 1)
            adj[(u + r*n) + k*n].push_back((v + ((r + wt) % k)*n) + k*n);
            adj[(v + r*n) + k*n].push_back((u + ((r + wt) % k)*n) + k*n);
        }
    }

    int ans = BFS(adj, src, target, n, k);
    cout << (ans == INT_MAX ? -1 : ans) << endl;

    return 0;
}
