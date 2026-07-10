// priority_queue<
//     pair<int,int>,
//     vector<pair<int,int>>,
//     greater<pair<int,int>>
// > pq;

// Think of it as:

// priority_queue<Datatype, Container, Comparison> Name;

// Here,

// Datatype = What will be stored?
// Container = Where will it be stored?
// Comparison = How will it be ordered?

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
    // Add edge from u to v with given weight
    adj[u].push_back({v, weight});

    // Since graph is undirected,
    // also add edge from v to u
    adj[v].push_back({u, weight});
}

//--------------------------------------------------------------
// Function to find shortest distance from source
// to every other vertex using Dijkstra Algorithm
//--------------------------------------------------------------
void dijkstra(vector<pair<int,int>> adj[], int V, int source)
{
    //----------------------------------------------------------
    // distance[i] stores shortest distance from source to i
    //----------------------------------------------------------
    vector<int> distance(V, INT_MAX);

    //----------------------------------------------------------
    // Min Heap (Priority Queue)
    //
    // pair.first  -> Distance
    // pair.second -> Node
    //
    // Node having minimum distance remains at the top.
    //----------------------------------------------------------
    priority_queue<
    pair<int,int>,        // Store (distance, node)
    vector<pair<int,int>>, // Use a vector internally
    greater<pair<int,int>> // Smallest distance has highest priority(min heap transformation)
> pq;

    //----------------------------------------------------------
    // Distance from source to itself is always 0
    //----------------------------------------------------------
    distance[source] = 0;

    //----------------------------------------------------------
    // Push source node into priority queue
    //----------------------------------------------------------
    pq.push({0, source});//distance,node

    //----------------------------------------------------------
    // Continue until priority queue becomes empty
    //----------------------------------------------------------
    while(!pq.empty())
    {
        //------------------------------------------------------
        // Get node having minimum distance
        //------------------------------------------------------
        int currDistance = pq.top().first;

        //------------------------------------------------------
        // Current node
        //------------------------------------------------------
        int currNode = pq.top().second;

        //------------------------------------------------------
        // Remove top element
        //------------------------------------------------------
        pq.pop();

        //------------------------------------------------------
        // Ignore outdated entry
        //
        // Example:
        // Queue contains (10,3)
        // Later shortest distance becomes (7,3)
        //
        // When (10,3) comes out,
        // skip it.
        //------------------------------------------------------
        if(currDistance > distance[currNode])
        {
            continue;
        }

        //------------------------------------------------------
        // Visit every neighbour of current node
        //------------------------------------------------------
        for(auto neighbour : adj[currNode])
        {
            //--------------------------------------------------
            // Neighbour node
            //--------------------------------------------------
            int nextNode = neighbour.first;

            //--------------------------------------------------
            // Weight of edge
            //--------------------------------------------------
            int edgeWeight = neighbour.second;

            //--------------------------------------------------
            // Check whether going through current node
            // gives a shorter path.
            //--------------------------------------------------
            if(distance[currNode] + edgeWeight < distance[nextNode])
            {
                //------------------------------------------------
                // Update shortest distance
                //------------------------------------------------
                distance[nextNode] = distance[currNode] + edgeWeight;

                //------------------------------------------------
                // Push updated distance into priority queue
                //------------------------------------------------
                pq.push({distance[nextNode], nextNode});
            }
        }
    }

    //----------------------------------------------------------
    // Print shortest distances
    //----------------------------------------------------------
    cout << "\nShortest Distance from Source " << source << "\n\n";

    for(int i = 0; i < V; i++)
    {
        cout << "Node " << i << " --> ";

        if(distance[i] == INT_MAX)
        {
            cout << "INF";
        }
        else
        {
            cout << distance[i];
        }

        cout << endl;
    }
}

//--------------------------------------------------------------
// Main Function
//--------------------------------------------------------------
int main()
{
    //----------------------------------------------------------
    // Number of vertices
    //----------------------------------------------------------
    int V = 6;

    //----------------------------------------------------------
    // Adjacency List
    //
    // Each element stores:
    // {Neighbour, Weight}
    //----------------------------------------------------------
    vector<pair<int,int>> adj[V];

    //----------------------------------------------------------
    // Create Graph
    //----------------------------------------------------------
    addEdge(adj, 0, 1, 4);//nnode,neighbour,weight     
    addEdge(adj, 0, 2, 1);
    addEdge(adj, 2, 1, 2);
    addEdge(adj, 1, 3, 1);
    addEdge(adj, 2, 3, 5);
    addEdge(adj, 3, 4, 3);
    addEdge(adj, 4, 5, 2);

    //----------------------------------------------------------
    // Source Vertex
    //----------------------------------------------------------
    int source = 0;

    //----------------------------------------------------------
    // Call Dijkstra Algorithm
    //----------------------------------------------------------
    dijkstra(adj, V, source);

    return 0;
}

          4
     0 ------- 1
     |         |
   1 |         |1
     |         |
     2 ------- 3
      \5       |
               |3
               |
               4
               |
               |2
               |
               5

            Initial State
vector<int> distance(V, INT_MAX);

Every node is unreachable initially.

Node :      0   1   2   3   4   5
Distance :  ∞   ∞   ∞   ∞   ∞   ∞
distance[source] = 0;

Distance from source to itself is always 0.

Node :      0   1   2   3   4   5
Distance :  0   ∞   ∞   ∞   ∞   ∞
pq.push({0,0});

Push

(distance,node)

(0,0)

Priority Queue

Top
 ↓
(0,0)
Iteration 1
Pop
currDistance = 0;
currNode = 0;
pq.pop();

Current Node

0
Visit neighbour 1

Edge

0 ------4------ 1
0 + 4 < INF
True

Update

distance[1]=4;

Push

pq.push({4,1});
Visit neighbour 2

Edge

0 -----1------2
0+1<INF

Update

distance[2]=1;

Push

pq.push({1,2});

Distance Array

0   4   1   ∞   ∞   ∞

Priority Queue

Top
 ↓
(1,2)

(4,1)

Notice

1 comes before 4

because it is a Min Heap.
Iteration 2
Pop
(1,2)

Current Node

2

Neighbours of 2

Node 0
1+1=2

2<0 ?

False

No update.

Node 1

Current distance of Node1

4

New distance

1+2=3
3<4

True

Update

distance[1]=3;

Push

(3,1)
Node3

Current

INF

New

1+5=6

Update

distance[3]=6

Push

(6,3)

Distance Array

0   3   1   6   ∞   ∞

Priority Queue

Top
 ↓
(3,1)

(4,1)

(6,3)

Notice something interesting.

There are two entries for Node 1.

(4,1)

(3,1)

This is perfectly normal.

Iteration 3
Pop
(3,1)

Current Node

1

Neighbours

Node0
3+4=7

7<0 ?

False
Node2
3+2=5

5<1 ?

False
Node3

Current

6

New

3+1=4
4<6

True

Update

distance[3]=4

Push

(4,3)

Distance

0   3   1   4   ∞   ∞

Priority Queue

Top
↓

(4,1)

(4,3)

(6,3)
Iteration 4

Pop

(4,1)

Current shortest distance of Node1

3

But queue says

4

Therefore

if(currDistance > distance[currNode])
    continue;

becomes

if(4>3)
True

So

Skip it.

No neighbour is visited.

This is called an outdated entry.

Iteration 5

Pop

(4,3)

Neighbours

Node4

Current

INF

New

4+3=7

Update

distance[4]=7

Push

(7,4)

Distance

0   3   1   4   7   ∞

Queue

(6,3)

(7,4)
Iteration 6

Pop

(6,3)

Current shortest distance of Node3

4

Queue gives

6

Old entry.

Skip.

Queue

(7,4)
Iteration 7

Pop

(7,4)

Visit Node5

7+2=9

Update

distance[5]=9

Push

(9,5)

Distance

0   3   1   4   7   9

Queue

(9,5)
Iteration 8

Pop

(9,5)

Only neighbour

4
9+2=11

11<7 ?

False

Nothing changes.

Queue becomes empty.

Algorithm stops.

Final Answer
Node	0	1	2	3	4	5
Shortest Distance	0	3	1	4	7	9
