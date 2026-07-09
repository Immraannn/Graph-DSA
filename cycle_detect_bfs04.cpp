//logic
// 1. Cycle Detection in Undirected Graph using BFS
// Logic

// For every node, keep track of:

// Visited array
// Parent of every node

// While traversing:

// If a neighbour is not visited, mark it visited and store its parent.
// If a neighbour is already visited and is not the parent, then a cycle exists.
#include <iostream>      // For input/output
#include <vector>        // For adjacency list
#include <queue>         // For BFS queue
using namespace std;

// Add an undirected edge
void addEdge(vector<int> adj[], int u, int v) {

    adj[u].push_back(v);     // u -> v

    adj[v].push_back(u);     // v -> u
}

// BFS function to detect cycle
bool bfsCycle(vector<int> adj[], vector<bool> &visited, int start) {

    // Queue stores {current node, parent node}
    queue<pair<int,int>> q;

    // Mark starting node visited
    visited[start] = true;

    // Push starting node with parent = -1
    q.push({start,-1});

    // BFS traversal
    while(!q.empty()) {

        // Take front node
        int node = q.front().first;

        // Take its parent
        int parent = q.front().second;

        // Remove from queue
        q.pop();

        // Traverse all neighbours
        for(int neighbour : adj[node]) {

            // If neighbour is not visited
            if(!visited[neighbour]) {

                // Mark visited
                visited[neighbour] = true;

                // Push neighbour with current node as parent
                q.push({neighbour,node});
            }

            // Visited neighbour but not parent
            else if(neighbour != parent) {

                // Cycle found
                return true;
            }
        }
    }

    // No cycle
    return false;
}

int main() {

    int vertices, edges;

    cout<<"Enter vertices: ";
    cin>>vertices;

    cout<<"Enter edges: ";
    cin>>edges;

    vector<int> adj[vertices];

    cout<<"Enter edges:\n";

    for(int i=0;i<edges;i++) {

        int u,v;
        cin>>u>>v;

        addEdge(adj,u,v);
    }

    vector<bool> visited(vertices,false);

    bool cycle = false;

    // Handle disconnected graph
    for(int i=0;i<vertices;i++) {

        if(!visited[i]) {

            if(bfsCycle(adj,visited,i)) {
                cycle = true;
                break;
            }
        }
    }

    if(cycle)
        cout<<"Cycle Present";
    else
        cout<<"Cycle Not Present";
}

dry run

Example

Graph

0 -----1
|      |
|      |
3------2

Start BFS from 0

Queue = [(0,-1)]

Visit 0

Push (1,0)
Push (3,0)

Visit 1

Neighbour 0 = Parent ✔

Push (2,1)

Visit 3

Neighbour 0 = Parent ✔

Neighbour 2 already visited
Parent = 0

2 != 0

Cycle Found
Time Complexity
O(V + E)

Space

O(V)
