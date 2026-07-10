Prim's Algorithm

Prim's Algorithm is a Greedy Algorithm used to find the Minimum Spanning Tree (MST) of a connected, weighted, undirected graph.

What is a Minimum Spanning Tree (MST)?

A Minimum Spanning Tree is a tree that:

Connects all vertices.
Has no cycles.
Uses exactly V - 1 edges.
Has the minimum possible total edge weight.
Idea of Prim's Algorithm

Instead of finding the shortest path like Dijkstra, Prim's algorithm grows a tree.

At every step:

Start from any vertex.
Mark it as visited.
Choose the minimum weight edge that connects:
a visited vertex to an unvisited vertex.
Add that edge to the MST.
Repeat until all vertices are included.

Greedy Choice: Always pick the smallest valid edge connecting the current MST to a new vertex.

Standard Example
        4
   0 ------- 1
   | \       |
  2|  \1     |5
   |   \     |
   2----3----4
     8    3

Edges:

0-1 = 4
0-2 = 2
0-3 = 1
1-4 = 5
3-4 = 3
2-3 = 8

Start from 0

Step 1

Visited

{0}

Available edges

0-1 (4)
0-2 (2)
0-3 (1)

Choose

0-3 (1)

MST Cost

1
Step 2

Visited

{0,3}

Available edges

0-1 (4)
0-2 (2)
3-4 (3)
3-2 (8)

Choose

0-2 (2)

MST Cost

1+2=3
Step 3

Visited

{0,2,3}

Available edges

0-1 (4)
3-4 (3)
2-3 (8)

Choose

3-4 (3)

MST Cost

3+3=6
Step 4

Visited

{0,2,3,4}

Available edges

0-1 (4)
4-1 (5)

Choose

0-1 (4)

MST Cost

6+4=10

All vertices are visited.

Minimum Spanning Tree
0----3 (1)
|
2 (2)

3----4 (3)

0----1 (4)

Total Cost

10


//code
#include <iostream>
#include <vector>
#include <queue>
#include <climits>      // For INT_MAX

using namespace std;

//--------------------------------------------------------------
// Function to add an undirected weighted edge
//--------------------------------------------------------------
void addEdge(vector<pair<int,int>> adj[], int u, int v, int weight)
{
    // Add edge from u to v
    adj[u].push_back({v, weight});

    // Since graph is undirected,
    // also add edge from v to u
    adj[v].push_back({u, weight});
}

//--------------------------------------------------------------
// Prim's Algorithm
//
// Finds the Minimum Spanning Tree (MST)
//
// key[i]     -> Minimum edge weight required
//               to include vertex i in MST.
//
// parent[i]  -> Parent of vertex i in MST.
//
// inMST[i]   -> True if vertex i is already
//               included in MST.
//--------------------------------------------------------------
void prims(vector<pair<int,int>> adj[], int V)
{
    //----------------------------------------------------------
    // key[i] stores the minimum edge weight required
    // to reach vertex i.
    //----------------------------------------------------------
    vector<int> key(V, INT_MAX);

    //----------------------------------------------------------
    // parent[i] stores the parent of vertex i
    // in the Minimum Spanning Tree.
    //----------------------------------------------------------
    vector<int> parent(V, -1);

    //----------------------------------------------------------
    // inMST[i] becomes true once
    // vertex i is included in MST.
    //----------------------------------------------------------
    vector<bool> inMST(V, false);

    //----------------------------------------------------------
    // Min Heap
    //
    // pair.first  -> Edge Weight
    // pair.second -> Vertex
    //
    // Vertex having minimum edge weight
    // always remains at the top.
    //----------------------------------------------------------
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    //----------------------------------------------------------
    // Start Prim's Algorithm from vertex 0.
    //----------------------------------------------------------
    key[0] = 0;

    //----------------------------------------------------------
    // Push {weight,node}
    //----------------------------------------------------------
    pq.push({0,0});

    //----------------------------------------------------------
    // Continue until all reachable vertices
    // are processed.
    //----------------------------------------------------------
    while(!pq.empty())
    {
        //------------------------------------------------------
        // Extract the vertex having
        // minimum edge weight.
        //------------------------------------------------------
        int currentNode = pq.top().second;

        //------------------------------------------------------
        // Remove it from priority queue.
        //------------------------------------------------------
        pq.pop();

        //------------------------------------------------------
        // If this node is already included
        // in MST, ignore it.
        //------------------------------------------------------
        if(inMST[currentNode])
            continue;

        //------------------------------------------------------
        // Include current node in MST.
        //------------------------------------------------------
        inMST[currentNode] = true;

        //------------------------------------------------------
        // Visit all neighbours
        //------------------------------------------------------
        for(auto neighbour : adj[currentNode])
        {
            //--------------------------------------------------
            // Adjacent vertex
            //--------------------------------------------------
            int nextNode = neighbour.first;

            //--------------------------------------------------
            // Weight of edge
            //--------------------------------------------------
            int edgeWeight = neighbour.second;

            //--------------------------------------------------
            // Update only if:
            //
            // 1. Vertex is not already in MST.
            // 2. Current edge is smaller than
            //    previously known edge.
            //--------------------------------------------------
            if(!inMST[nextNode] && edgeWeight < key[nextNode])
            {
                //------------------------------------------------
                // Update minimum edge weight.
                //------------------------------------------------
                key[nextNode] = edgeWeight;

                //------------------------------------------------
                // Store parent of this vertex.
                //------------------------------------------------
                parent[nextNode] = currentNode;

                //------------------------------------------------
                // Push updated information
                // into priority queue.
                //------------------------------------------------
                pq.push({key[nextNode], nextNode});
            }
        }
    }

    //----------------------------------------------------------
    // Print Minimum Spanning Tree
    //----------------------------------------------------------
    cout << "\nEdges in Minimum Spanning Tree\n";
    cout << "-----------------------------\n";

    int totalCost = 0;

    for(int i = 1; i < V; i++)
    {
        cout << parent[i]
             << " ---- "
             << i
             << "   Weight = "
             << key[i]
             << endl;

        totalCost += key[i];
    }

    //----------------------------------------------------------
    // Print total weight of MST
    //----------------------------------------------------------
    cout << "\nTotal Cost = " << totalCost << endl;
}

//--------------------------------------------------------------
// Main Function
//--------------------------------------------------------------
int main()
{
    //----------------------------------------------------------
    // Number of vertices
    //----------------------------------------------------------
    int V = 5;

    //----------------------------------------------------------
    // Adjacency List
    //
    // pair.first  -> Neighbour
    // pair.second -> Edge Weight
    //----------------------------------------------------------
    vector<pair<int,int>> adj[V];

    //----------------------------------------------------------
    // Create Graph
    //----------------------------------------------------------
    addEdge(adj,0,1,4);
    addEdge(adj,0,2,2);
    addEdge(adj,0,3,1);
    addEdge(adj,3,4,3);
    addEdge(adj,1,4,5);
    addEdge(adj,2,3,8);

    //----------------------------------------------------------
    // Call Prim's Algorithm
    //----------------------------------------------------------
    prims(adj, V);

    return 0;
}
