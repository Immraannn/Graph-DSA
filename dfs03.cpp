#include <iostream>     // For input and output
#include <vector>       // For vector
using namespace std;

// Function to add an edge in an undirected graph
void addEdge(vector<int> adj[], int u, int v) {

    adj[u].push_back(v);     // Add vertex v to u's adjacency list

    adj[v].push_back(u);     // Add vertex u to v's adjacency list
                             // Remove this line for a directed graph
}

// Recursive DFS function
void DFS(vector<int> adj[], vector<bool> &visited, int node) {

    // Mark the current node as visited
    visited[node] = true;

    // Process the current node
    cout << node << " ";

    // Visit all neighbours of the current node
    for (int neighbour : adj[node]) {

        // If the neighbour has not been visited
        if (!visited[neighbour]) {

            // Recursively visit the neighbour
            DFS(adj, visited, neighbour);
        }
    }
}

int main() {

    int vertices, edges;

    // Read the number of vertices
    cout << "Enter number of vertices: ";
    cin >> vertices;

    // Read the number of edges
    cout << "Enter number of edges: ";
    cin >> edges;

    // Create the adjacency list
    vector<int> adj[vertices];

    cout << "Enter edges (u v):\n";

    // Read all edges
    for (int i = 0; i < edges; i++) {

        int u, v;
        cin >> u >> v;

        // Add edge to the graph
        addEdge(adj, u, v);
    }

    int start;

    // Read the starting vertex
    cout << "Enter starting vertex: ";
    cin >> start;

    // Create a visited array and initialize all vertices as unvisited
    vector<bool> visited(vertices, false);

    cout << "\nDFS Traversal: ";

    // Start DFS from the given vertex
    DFS(adj, visited, start);

    return 0;
}
//sample input
// Enter number of vertices: 5
// Enter number of edges: 6

// 0 1
// 0 2
// 1 2
// 1 3
// 2 4
// 3 4

// // Enter starting vertex: 0
// DFS Traversal:
// 0 1 2 4 3

        0
     / \
    1---2
    |    \
    3-----4
Dry Run

Graph:

      0
     / \
    1---2
    |    \
    3-----4
Initial State
Visited = [F F F F F]
DFS(0)
Visit 0

Visited = [T F F F F]

Output: 0

Neighbours: 1, 2

Go to 1

DFS(1)
Visit 1

Visited = [T T F F F]

Output: 0 1

Neighbours: 0, 2, 3

0 already visited
Go to 2
DFS(2)
Visit 2

Visited = [T T T F F]

Output: 0 1 2

Neighbours: 0, 1, 4

0 visited
1 visited
Go to 4
DFS(4)
Visit 4

Visited = [T T T F T]

Output: 0 1 2 4

Neighbours: 2, 3

2 visited
Go to 3
DFS(3)
Visit 3

Visited = [T T T T T]

Output: 0 1 2 4 3

Neighbours: 1, 4

Both are already visited.

Return to 4 → 2 → 1 → 0

DFS ends.

 //  Time: O(V + E)
	// Space: O(V) (including recursion stack)
          
