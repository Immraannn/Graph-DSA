#include <iostream>     // For input and output
#include <vector>       // For vector
#include <queue>        // For queue used in BFS
using namespace std;

// Function to add an edge in an undirected graph
void addEdge(vector<int> adj[], int u, int v) {

    adj[u].push_back(v);     // Add vertex v to u's adjacency list

    adj[v].push_back(u);     // Add vertex u to v's adjacency list
                             // Remove this line for a directed graph
}

// Function to perform BFS traversal
void BFS(vector<int> adj[], int vertices, int start) {

    // Create a visited array and initialize all vertices as unvisited
    vector<bool> visited(vertices, false);

    // Create an empty queue
    queue<int> q;

    // Mark the starting vertex as visited
    visited[start] = true;

    // Push the starting vertex into the queue
    q.push(start);

    // Continue until the queue becomes empty
    while (!q.empty()) {

        // Store the front vertex of the queue
        int frontNode = q.front();

        // Remove the front vertex from the queue
        q.pop();

        // Process the current vertex
        cout << frontNode << " ";

        // Traverse all neighbours of the current vertex
        for (int neighbour : adj[frontNode]) {

            // If the neighbour has not been visited
            if (!visited[neighbour]) {

                // Mark it as visited
                visited[neighbour] = true;

                // Add it to the queue for future processing
                q.push(neighbour);
            }
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

    // Create an adjacency list
    vector<int> adj[vertices];

    cout << "Enter edges (u v):\n";

    // Read all edges
    for (int i = 0; i < edges; i++) {

        int u, v;

        cin >> u >> v;

        // Add the edge to the graph
        addEdge(adj, u, v);
    }

    int start;

    // Read the starting vertex
    cout << "Enter starting vertex: ";
    cin >> start;

    // Print BFS traversal
    cout << "\nBFS Traversal: ";

    BFS(adj, vertices, start);

    return 0;
}
// sample input
// Enter number of vertices: 5
// Enter number of edges: 6

// 0 1
// 0 2
// 1 2
// 1 3
// 2 4
// 3 4

// Enter starting vertex: 0
  //output
//   BFS Traversal:
// 0 1 2 3 4
//time=O(v+e)
//space=O(v)
    //   0
    //  / \
    // 1---2
    // |    \
    // 3-----4
