#include <bits/stdc++.h>
using namespace std;

/*
French Flag Walk: red -> white -> blue

Each vertex v is represented by 3 vertices: (v, 0), (v, 1), (v, 2) where 0, 1, 2 represent red, white, blue respectively.

In the code, (u, 0), (u, 1) and (u, 2) are represented by u, u + V and u + 2*V respectively.

We need to determine which vertices are reachable via a French Flag walk from a given source vertex src.

For each edge (u, v), we add 3 edges in the modified graph: (u, 0) -> (v, 1), (u, 1) -> (v, 2), (u, 2) -> (v, 0).

For some vertex (v, r), if there is an edge incident on this vertex from a vertex of type (u, 2), then our walk has been completed, and v is a reachable vertex. We can do this using a simple DFS traversal.
*/

void DFS(vector <vector <int>> &adj, vector <int> &isReachable, vector <int> &visited, int node, int V) {
    visited[node] = 1;

    // check if the current node is of type (u, 2)
    if (node > 2*V) {
        for (int adjNode: adj[node]) {
            isReachable[adjNode] = 1;

            if (!visited[adjNode]) {
                DFS(adj, isReachable, visited, adjNode, V);
            }
        }
    }
    else {
        for (int adjNode: adj[node]) {
            if (!visited[adjNode]) {
                DFS(adj, isReachable, visited, adjNode, V);
            }
        }
    }
}

int main() {
    int V, E;
    cin >> V >> E;

    vector <vector <int>> adj(3*V + 1);

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        
        adj[u].push_back(v + V);
        adj[u + V].push_back(v + 2*V);
        adj[u + 2*V].push_back(v);
    }

    int src;
    cin >> src;

    vector <int> isReachable(V + 1, 0);
    vector <int> visited(3*V + 1, 0);

    DFS(adj, isReachable, visited, src, V);

    for (int i = 1; i <= V; i++) {
        if (isReachable[i]) {
            cout << i << " ";
        }
    }

    cout << "\n";
}