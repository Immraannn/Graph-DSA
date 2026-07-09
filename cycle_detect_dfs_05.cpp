#include <iostream>
#include <vector>
using namespace std;

// Add edge in an undirected graph
void addEdge(vector<int> adj[], int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// DFS function to detect cycle
bool dfs(int node, int parent, vector<int> adj[], vector<bool> &visited) {

    // Mark current node as visited
    visited[node] = true;

    // Traverse all neighbours
    for (int neighbour : adj[node]) {

        // If neighbour is not visited
        if (!visited[neighbour]) {

            // Visit neighbour recursively
            if (dfs(neighbour, node, adj, visited))
                return true;
        }

        // If neighbour is visited and is NOT the parent
        else if (neighbour != parent) {

            // Cycle exists
            return true;
        }
    }

    // No cycle found from this node
    return false;
}

int main() {

    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    vector<int> adj[vertices];

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;

        addEdge(adj, u, v);
    }

    // Initially all vertices are unvisited
    vector<bool> visited(vertices, false);

    bool cycle = false;

    // Handle disconnected graph
    for (int i = 0; i < vertices; i++) {

        if (!visited[i]) {

            if (dfs(i, -1, adj, visited)) {
                cycle = true;
                break;
            }
        }
    }

    if (cycle)
        cout << "Cycle Present";
    else
        cout << "Cycle Not Present";

    return 0;
}

// dfs(0,-1)

// │
// ├── visit 0
// │
// └── dfs(1,0)

//       │
//       ├── neighbour 0
//       │
//       ├── visited
//       │
//       ├── parent = 0
//       │
//       └── Ignore

//       │
//       └── dfs(2,1)

//              │
//              ├── neighbour 1
//              │
//              ├── parent
//              │
//              └── Ignore

//              │
//              ├── neighbour 0
//              │
//              ├── visited
//              │
//              ├── parent = 1
//              │
//              ├── 0 != 1
//              │
//              └── Cycle Found
