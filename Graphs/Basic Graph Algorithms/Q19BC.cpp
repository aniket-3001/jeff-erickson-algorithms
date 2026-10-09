#include <bits/stdc++.h>
using namespace std;

void BFS(int src, int idx, vector <vector <int>> &adj, vector <vector <int>> &distances) {
    distances[idx][src] = 0;
    queue <int> q;
    q.push(src);

    while (!q.empty()) {
        int node = q.front();
        int d = distances[idx][node];
        q.pop();

        for (int adjNode: adj[node]) {
            if (distances[idx][adjNode] > d + 1) {
                distances[idx][adjNode] = d + 1;
                q.push(adjNode);
            }
        }
    }
}

int deven(int s, int v, vector <vector <int>> &distances, int n) {
    return distances[s][v];
}

int dodd(int s, int v, vector <vector <int>> &distances, int n) {
    return distances[s][v + n];
}

int main() {
    int n, m;
    cin >> n >> m;

    int k;
    cin >> k;

    vector <int> coins(k);

    for (int i = 0; i < k; i++) {
        cin >> coins[i];
    }

    vector <vector <int>> adj(2*n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v + n);
        adj[v + n].push_back(u);
        adj[u + n].push_back(v);
        adj[v].push_back(u + n);
    }

    vector<vector<int>> distances(k, vector <int>(2*n + 1, INT_MAX));

    for (int i = 0; i < k; i++) {
        BFS(coins[i], i, adj, distances);
    }

    int ans = INT_MAX;

    for (int i = 1; i <= n; i++) {
        int node = i;
        int maxdeven = INT_MIN;
        int maxdodd = INT_MIN;

        for (int j = 0; j < k; j++) {
            maxdodd = max(maxdodd, dodd(j, node, distances, n));
            maxdeven = max(maxdeven, deven(j, node, distances, n));
        }

        ans = min(ans, min(maxdeven, maxdodd));
    }

    cout << (ans == INT_MAX ? -1 : ans) << endl;

    return 0;
}