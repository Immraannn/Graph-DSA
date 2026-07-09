#include <iostream>      // For input and output
#include <vector>        // For adjacency list
#include <stack>         // For Topological Sort
#include <climits>       // For INT_MAX
using namespace std;

//---------------------------------------------------------
// Function to add a directed weighted edge
//---------------------------------------------------------
void addEdge(vector<pair<int,int>> adj[], int u, int v, int weight) {

    // Add an edge from u to v with given weight
    adj[u].push_back({v, weight});
}

//---------------------------------------------------------
// DFS function for Topological Sorting
//---------------------------------------------------------
void topoSort(int node,
              vector<pair<int,int>> adj[],
              vector<bool> &visited,
              stack<int> &st)
{
    // Mark current node as visited
    visited[node] = true;

    // Traverse all neighbours of current node
    for (auto neighbour : adj[node]) {

        // Extract neighbour vertex
        int nextNode = neighbour.first;

        // Visit neighbour only if it has not been visited
        if (!visited[nextNode]) {

            topoSort(nextNode, adj, visited, st);
        }
    }

    // Push current node into stack
    // AFTER visiting all its neighbours
    st.push(node);
}

//---------------------------------------------------------
// Function to find shortest path from source
//---------------------------------------------------------
void shortestPath(vector<pair<int,int>> adj[],
                  int vertices,
                  int source)
{
    //-----------------------------------------------------
    // Create visited array for Topological Sort
    //-----------------------------------------------------
    vector<bool> visited(vertices, false);

    //-----------------------------------------------------
    // Stack to store Topological Order
    //-----------------------------------------------------
    stack<int> st;

    //-----------------------------------------------------
    // Perform Topological Sort
    //-----------------------------------------------------
    for (int i = 0; i < vertices; i++) {

        if (!visited[i]) {

            topoSort(i, adj, visited, st);
        }
    }

    //-----------------------------------------------------
    // Distance array
    //-----------------------------------------------------
    vector<int> distance(vertices, INT_MAX);

    // Distance from source to itself is always zero
    distance[source] = 0;

    //-----------------------------------------------------
    // Process vertices according to Topological Order
    //-----------------------------------------------------
    while (!st.empty()) {

        // Get the top vertex
        int topNode = st.top();

        // Remove it from stack
        st.pop();

        // If this vertex is reachable from source
        if (distance[topNode] != INT_MAX) {

            // Traverse all outgoing edges
            for (auto neighbour : adj[topNode]) {

                // Extract neighbour vertex
                int nextNode = neighbour.first;

                // Extract edge weight
                int weight = neighbour.second;

                // Relaxation Step
                //
                // If going through topNode gives
                // a shorter distance, then update it
                if (distance[topNode] + weight < distance[nextNode]) {

                    distance[nextNode] = distance[topNode] + weight;
                }
            }
        }
    }

    //-----------------------------------------------------
    // Print shortest distance of every vertex
    //-----------------------------------------------------
    cout << "\nShortest Distance from Source:\n";

    for (int i = 0; i < vertices; i++) {

        // Vertex cannot be reached
        if (distance[i] == INT_MAX)

            cout << i << " -> INF" << endl;

        // Shortest distance exists
        else

            cout << i << " -> " << distance[i] << endl;
    }
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
    vector<pair<int,int>> adj[vertices];

    cout << "Enter edges (u v weight):\n";

    // Read all edges
    for (int i = 0; i < edges; i++) {

        int u, v, weight;

        cin >> u >> v >> weight;

        // Add edge into graph
        addEdge(adj, u, v, weight);
    }

    int source;

    // Read source vertex
    cout << "Enter source vertex: ";
    cin >> source;

    // Find shortest path
    shortestPath(adj, vertices, source);

    return 0;
}
