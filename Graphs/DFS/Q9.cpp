#include <bits/stdc++.h>
using namespace std;

void SinkVertexDFS(int node, vector <vector <int>> &adj, vector <int> &visited, vector <int> &isSinkVertex) {
    visited[node] = 1;
    int cnt = 0;

    for (int adjNode: adj[node]) {
        if (!visited[adjNode]) {
            SinkVertexDFS(adjNode, adj, visited, isSinkVertex);
        }

        cnt++;
    }

    if (cnt == 0) {
        isSinkVertex[node] = 1;
    }
}

vector <int> FindSinkVertices(vector <vector <int>> &adj, int V) {
    vector <int> isSinkVertex(V + 1, 0);
    vector <int> visited(V + 1, 0);

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            SinkVertexDFS(i, adj, visited, isSinkVertex);
        }
    }

    return isSinkVertex;
}

void DFS(int node, vector <vector <int>> &adj, vector <int> &visited) {
    visited[node] = 1;

    for (int adjNode: adj[node]) {
        if (!visited[adjNode]) {
            DFS(adjNode, adj, visited);
        }
    }
}

bool SolvePartA(vector <vector <int>> &adj, int src, vector <int> &isSinkVertex, int V) {
    vector <int> visited(V + 1, 0);
    DFS(src, adj, visited);

    for (int i = 1; i <= V; i++) {
        if (!visited[i] && !isSinkVertex[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    // n is the number of lockboxes
    // m is the number of keys

    vector <vector <int>> KeysInsideLockbox(n + 1);
    vector <int> keyToLockbox(m + 1);

    for (int i = 1; i <= m; i++) {
        // the lockbox ith key belongs to
    }

    for (int i = 1; i <= n; i++) {
        // keys inside ith lockbox
    }

    // constructing the graph
    vector <vector <int>> adj(n + 1);

    for (int i = 1; i <= n; i++) {
        for (int key: KeysInsideLockbox[i]) {
            adj[i].push_back(keyToLockbox[key]);
        }
    }

    // a) asks us to find whether given a lockbox, is it possible to open all the lockboxes from it?

    int src;
    cin >> src;

    // We solve this by first finding all the sink vertices of the graph
    vector <int> isSinkVertex = FindSinkVertices(adj, n);
    
    if (SolvePartA(adj, src, isSinkVertex, n)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    // b) asks us to find the minimum number of locks we can break, to open all the lockboxes

    // We can solve this by first computing SCC(G) and then counting all vertices in SS(G) with in-degree 0, i.e all the source vertices

    return 0;
}