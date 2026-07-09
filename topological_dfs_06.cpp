// A Topological Order is an ordering of the vertices of a Directed Acyclic Graph (DAG) such that:

// For every directed edge u → v, vertex u appears before v in the ordering.

// In simple words:

// A node must appear before all the nodes that depend on it.

#include <iostream>     // For input and output
#include <vector>       // To store adjacency list
#include <stack>        // To store topological order
using namespace std;

// Function to add a directed edge (u -> v)
void addEdge(vector<int> adj[], int u, int v) {

    // Add vertex v to the adjacency list of u
    adj[u].push_back(v);
}

// DFS function for Topological Sorting
void dfs(int node,
         vector<int> adj[],
         vector<bool> &visited,
         stack<int> &st)
{
    // Mark the current node as visited
    visited[node] = true;

    // Traverse all neighbours of the current node
    for (int neighbour : adj[node]) {

        // Visit the neighbour only if it has not been visited
        if (!visited[neighbour]) {

            // Recursive DFS call
            dfs(neighbour, adj, visited, st);
        }
    }

    // All neighbours have been processed
    // Push the current node into the stack
    // Nodes are pushed in reverse finishing order
    st.push(node);
}

int main() {

    int vertices, edges;

    // Read the total number of vertices
    cout << "Enter number of vertices: ";
    cin >> vertices;

    // Read the total number of edges
    cout << "Enter number of edges: ";
    cin >> edges;

    // Create the adjacency list
    vector<int> adj[vertices];

    cout << "Enter directed edges (u v):\n";

    // Read all directed edges
    for (int i = 0; i < edges; i++) {

        int u, v;
        cin >> u >> v;

        // Add edge u -> v
        addEdge(adj, u, v);
    }

    // Initially, all vertices are unvisited
    vector<bool> visited(vertices, false);

    // Stack to store the topological ordering
    stack<int> st;

    // Start DFS from every unvisited vertex
    // This also handles disconnected graphs
    for (int i = 0; i < vertices; i++) {

        if (!visited[i]) {

            dfs(i, adj, visited, st);
        }
    }

    // Print the topological order
    cout << "\nTopological Order:\n";

    // Nodes are printed by popping from the stack
    while (!st.empty()) {

        cout << st.top() << " ";

        st.pop();
    }

    return 0;
}


Example

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
DFS Calls
dfs(5)

↓

dfs(2)

↓

dfs(3)

↓

dfs(1)

Now pushing starts

push(1)

push(3)

push(2)

Back to

5

↓

dfs(0)

↓

dfs(4)

push(4)

push(0)

push(5)

Stack

Top

5

0

4

2

3

1

Bottom

Output

5 0 4 2 3 1
Time Complexity
O(V + E)

Space

O(V)
