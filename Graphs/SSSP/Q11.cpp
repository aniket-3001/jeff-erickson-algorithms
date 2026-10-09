#include <bits/stdc++.h>
using namespace std;

void DFS1(vector <vector <pair <int, int>>> &adj, vector <int> &visited, vector <int> &pathVisited, vector <int> &cycleNodes, int node) {
    visited[node] = 1;
    pathVisited[node] = 1;

    for (auto it: adj[node]) {
        int adjNode = it.first;

        if (pathVisited[adjNode]) {
            cycleNodes[adjNode] = 1;
        }

        if (!visited[adjNode]) {
            DFS1(adj, visited, pathVisited, cycleNodes, adjNode);
        }
    }

    pathVisited[node] = 0;
}

void DFS2(vector <vector <pair <int, int>>> &adj, vector <int> &visited, vector <int> &cycleNodes, int node) {
    visited[node] = 1;

    for (auto it: adj[node]) {
        int adjNode = it.first;

        if (!visited[adjNode]) {
            cycleNodes[adjNode] = 1;
            DFS2(adj, visited, cycleNodes, adjNode);
        }
    }
}

void postorderDFS(vector <vector <pair <int, int>>> &adj, vector <int> &visited, vector <int> &postorder, int node) {
    visited[node] = 1;

    for (auto it: adj[node]) {
        int adjNode = it.first;

        if (!visited[adjNode]) {
            postorderDFS(adj, visited, postorder, adjNode);
        }
    }

    postorder.push_back(node);
}

vector <int> LLP(vector <vector <pair <int, int>>> &adj, int V, vector <int> &postorder, int src) {
    vector <int> dist(V + 1, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= V; i++) {
        int node = postorder[i];

        if (dist[node] != INT_MAX) {
            for (auto it: adj[node]) {
                int adjNode = it.first;
                int edgeWt = it.second;

                if (dist[adjNode] > dist[node] + edgeWt) {
                    dist[adjNode] = dist[node] + edgeWt;
                }
            }
        }
    }

    return dist;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector <vector <int>> edges(E + 1);
    vector <vector <pair <int, int>>> adj1(V + 1);

    for (int i = 1; i <= E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    for (int i = 1; i <= E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        adj1[u].push_back({v, -w});
    }

    int src;
    cin >> src;

    vector <int> visited(V + 1, 0);
    vector <int> pathVisited(V + 1, 0);
    vector <int> cycleNodes(V + 1, 0);
    vector <int> unreachableNodes(V + 1, 0);

    DFS1(adj1, visited, pathVisited, cycleNodes, src);

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            unreachableNodes[i] = 1;
        }
    }

    visited.assign(V + 1, 0);

    for (int i = 0; i < cycleNodes.size(); i++) {
        if (!visited[cycleNodes[i]] && cycleNodes[i]) {
            DFS2(adj1, visited, cycleNodes, cycleNodes[i]);
        }
    }

    vector <vector <pair <int, int>>> adj2(V + 1);

    for (int i = 1; i <= E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if (!cycleNodes[u] && !cycleNodes[v]) {
            adj2[v].push_back({u, -w}); // adj2 will become a DAG
        }
    }

    vector <int> postorder;
    visited.assign(V + 1, 0);

    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            postorderDFS(adj2, visited, postorder, i);
        }
    }

    vector <int> ans = LLP(adj2, V, postorder, src);

    for (int i = 1; i <= V; i++) {
        if (unreachableNodes[i]) {
            ans[i] = INT_MAX;
        } else if (cycleNodes[i]) {
            ans[i] = INT_MIN;
        }
    }

    for (int i = 1; i <= V; i++) {
        if (ans[i] == INT_MAX) {
            cout << "INF" << " ";
        } else if (ans[i] == INT_MIN) {
            cout << "-INF" << " ";
        } else {
            cout << ans[i] << " ";
        }
    }

    return 0;
}