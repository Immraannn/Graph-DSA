#include <iostream>     // For input and output
#include <vector>       // For adjacency list
#include <queue>        // For BFS queue
using namespace std;

// Function to add a directed edge (u -> v)
void addEdge(vector<int> adj[], int u, int v) {

    // Add vertex v to the adjacency list of u
    adj[u].push_back(v);
}

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

    // Create indegree array and initialize all values to 0
    // indegree[i] = Number of incoming edges to vertex i
    vector<int> indegree(vertices, 0);

    cout << "Enter directed edges (u v):\n";

    // Read all edges
    for (int i = 0; i < edges; i++) {

        int u, v;
        cin >> u >> v;

        // Add edge u -> v
        addEdge(adj, u, v);

        // Increase indegree of destination vertex
        indegree[v]++;
    }

    // Queue to store vertices having indegree = 0
    queue<int> q;

    // Push all vertices with indegree 0 into the queue
    for (int i = 0; i < vertices; i++) {

        if (indegree[i] == 0) {

            q.push(i);
        }
    }

    cout << "\nTopological Order:\n";

    // Continue until queue becomes empty
    while (!q.empty()) {

        // Get the front vertex
        int frontNode = q.front();

        // Remove it from the queue
        q.pop();

        // Process (print) the current vertex
        cout << frontNode << " ";

        // Traverse all neighbours
        for (int neighbour : adj[frontNode]) {

            // Remove the edge from current node to neighbour
            // by decreasing neighbour's indegree
            indegree[neighbour]--;

            // If neighbour has no incoming edges left
            // it is ready to be processed
            if (indegree[neighbour] == 0) {

                q.push(neighbour);
            }
        }
    }

    return 0;
}


Dry Run
Graph
5 → 2 → 3 → 1
↓
0 → 4

Edges

5 2
5 0
2 3
3 1
0 4
Step 1: Calculate Indegree
Vertex	Indegree
0	1
1	1
2	1
3	1
4	1
5	0

Queue

[5]
Step 2

Remove 5

Output : 5

Neighbours:

2
0

Decrease indegree

2 : 1 → 0

0 : 1 → 0

Queue

[2, 0]
Step 3

Remove 2

Output : 5 2

Neighbour

3

Decrease indegree

3 : 1 → 0

Queue

[0, 3]
Step 4

Remove 0

Output : 5 2 0

Neighbour

4

Decrease indegree

4 : 1 → 0

Queue

[3, 4]
Step 5

Remove 3

Output : 5 2 0 3

Neighbour

1

Decrease indegree

1 : 1 → 0

Queue

[4, 1]
Step 6

Remove 4

Output : 5 2 0 3 4

No neighbours.

Queue

[1]
Step 7

Remove 1

Output : 5 2 0 3 4 1

Queue becomes empty.

Final Topological Order
5 2 0 3 4 1
