#include <iostream>      // For input and output
#include <vector>        // For adjacency list and path
#include <queue>         // For BFS
#include <algorithm>     // For reverse()
using namespace std;

//---------------------------------------------------------
// Function to add an undirected edge
//---------------------------------------------------------
void addEdge(vector<int> adj[], int u, int v) {

    // Edge from u to v
    adj[u].push_back(v);

    // Since graph is undirected,
    // also add edge from v to u
    adj[v].push_back(u);
}

//---------------------------------------------------------
// BFS Traversal
//---------------------------------------------------------
void bfs(vector<int> adj[],
         int source,
         vector<bool> &visited,
         vector<int> &parent)
{
    // Queue stores the vertices to be processed
    queue<int> q;

    // Mark source as visited because BFS starts from here
    visited[source] = true;

    // Insert source into queue
    q.push(source);

    // Continue until queue becomes empty
    while (!q.empty()) {

        // Take the front vertex
        int frontNode = q.front();

        // Remove it from queue
        q.pop();

        // Visit every neighbour of the current vertex
        for (int neighbour : adj[frontNode]) {

            // Process only unvisited neighbours
            if (!visited[neighbour]) {

                // Mark neighbour visited
                visited[neighbour] = true;

                // Store from which vertex we reached this neighbour
                // This helps us reconstruct the shortest path later
                parent[neighbour] = frontNode;

                // Push neighbour into queue
                q.push(neighbour);
            }
        }
    }
}

//---------------------------------------------------------
// Function to find and print shortest path
//---------------------------------------------------------
void shortestPath(vector<int> adj[],
                  int vertices,
                  int source,
                  int destination)
{
    // Initially no vertex is visited
    vector<bool> visited(vertices, false);

    // Parent array
    // parent[i] stores the previous vertex used to reach i
    vector<int> parent(vertices, -1);

    // Perform BFS from source
    bfs(adj, source, visited, parent);

    // If destination was never visited,
    // then no path exists
    if (!visited[destination]) {

        cout << "No Path Exists";
        return;
    }

    // This vector will store the shortest path
    vector<int> path;

    // Start from destination
    int current = destination;

    // Move backwards using parent array
    //
    // Example:
    // parent[4] = 2
    // parent[2] = 0
    // parent[0] = -1
    //
    // Path stored becomes:
    // 4 2 0
    while (current != -1) {

        path.push_back(current);

        current = parent[current];
    }

    // Reverse the path to get
    // Source ----> Destination
    reverse(path.begin(), path.end());

    cout << "\nShortest Path:\n";

    // Print the path
    for (int node : path) {

        cout << node << " ";
    }

    cout << endl;

    // Number of edges in shortest path
    cout << "Shortest Distance = "
         << path.size() - 1 << endl;
}

//---------------------------------------------------------
// Driver Code
//---------------------------------------------------------
int main() {

    int vertices, edges;

    // Read number of vertices
    cout << "Enter number of vertices: ";
    cin >> vertices;

    // Read number of edges
    cout << "Enter number of edges: ";
    cin >> edges;

    // Create adjacency list
    vector<int> adj[vertices];

    cout << "Enter edges (u v):\n";

    // Read all edges
    for (int i = 0; i < edges; i++) {

        int u, v;

        cin >> u >> v;

        addEdge(adj, u, v);
    }

    int source, destination;

    // Read source vertex
    cout << "Enter source: ";
    cin >> source;

    // Read destination vertex
    cout << "Enter destination: ";
    cin >> destination;

    // Find shortest path
    shortestPath(adj, vertices, source, destination);

    return 0;
}

 Dry Run

Example

Graph

0 -----1
|      |
|      |
2------3
 \
  \
   4

Edges

0 1
0 2
1 3
2 3
2 4

Source

0

Destination

4
BFS Dry Run

Initially

Queue = [0]

Visited = [T F F F F]

Parent = [-1 -1 -1 -1 -1]
Remove 0

Neighbours

1

2
Queue = [1 2]

Parent

1 ← 0

2 ← 0
Remove 1

Neighbour

3
Queue = [2 3]

Parent

3 ← 1
Remove 2

Neighbour

4
Queue = [3 4]

Parent

4 ← 2

Final Parent Array

Vertex	Parent
0	-1
1	0
2	0
3	1
4	2
Reconstruct Path

Start from destination

4

Go to parent

4 → 2

Go to parent

4 → 2 → 0

Go to parent

4 → 2 → 0 → -1

Reverse it

0 → 2 → 4

This is the shortest path.

// time O(v+e)
// space O(v)
