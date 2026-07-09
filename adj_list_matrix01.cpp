#include <iostream>
#include <vector>
using namespace std;

// Create Graph using Adjacency List
void createAdjList(vector<int> adj[], int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);   // Remove this line for Directed Graph
}

// Print Adjacency List
void printAdjList(vector<int> adj[], int vertices) {
    cout << "\nAdjacency List:\n";

    for (int i = 0; i < vertices; i++) {
        cout << i << " -> ";

        for (int neighbour : adj[i]) {
            cout << neighbour << " ";
        }

        cout << endl;
    }
}

// Create Graph using Adjacency Matrix
void createAdjMatrix(vector<vector<int>> &matrix, int u, int v) {
    matrix[u][v] = 1;
    matrix[v][u] = 1;      // Remove this line for Directed Graph
}

// Print Adjacency Matrix
void printAdjMatrix(vector<vector<int>> &matrix) {
    cout << "\nAdjacency Matrix:\n";

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {

    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    // Adjacency List
    vector<int> adj[vertices];

    // Adjacency Matrix
    vector<vector<int>> matrix(vertices, vector<int>(vertices, 0));

    cout << "\nEnter edges (u v):\n";

    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;

        createAdjList(adj, u, v);
        createAdjMatrix(matrix, u, v);
    }

    printAdjList(adj, vertices);
    printAdjMatrix(matrix);

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

//output
// Adjacency List:
// 0 -> 1 2
// 1 -> 0 2 3
// 2 -> 0 1 4
// 3 -> 1 4
// 4 -> 2 3

// Adjacency Matrix:
// 0 1 1 0 0
// 1 0 1 1 0
// 1 1 0 0 1
// 0 1 0 0 1
// 0 0 1 1 0
