#include <iostream>
#include <vector>
#include <limits>
using namespace std;

/*
PROBLEM:
Compute the minimum fuel cost from a starting farm to all other
locations (farms, mills, factories) using a road network represented
as a weighted graph (adjacency matrix).

WHY DIJKSTRA:
Dijkstra’s algorithm finds shortest paths efficiently in a graph
with non-negative edge weights. It selects the closest unvisited
node at each step and relaxes all neighboring edges.
*/

/* ----------------------------
   Global Variables
   ---------------------------- */
const int INF = 1e9;
int n; // number of nodes
vector<vector<int>> graph;
vector<int> distArr;
vector<bool> visited;
vector<int> parent; // to reconstruct shortest paths

/* ----------------------------
   Initialize Graph
   ---------------------------- */
void initializeGraph(){
    n = 6; // default number of locations
    graph.resize(n, vector<int>(n,0));
    distArr.resize(n, INF);
    visited.resize(n,false);
    parent.resize(n,-1);

    int temp[6][6] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 3, 0, 0, 0},
        {0, 3, 0, 2, 7, 0},
        {0, 0, 2, 0, 3, 4},
        {0, 0, 7, 3, 0, 1},
        {0, 0, 0, 4, 1, 0}
    };

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            graph[i][j] = temp[i][j];

    cout << "Graph (Adjacency Matrix - fuel costs) initialized:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout << graph[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

/* ----------------------------
   Print Shortest Paths from Parent Array
   ---------------------------- */
void printPath(int target){
    vector<int> path;
    for(int v=target; v!=-1; v=parent[v])
        path.push_back(v);

    cout << "Path: ";
    for(int i=path.size()-1; i>=0; i--)
        cout << path[i] << " ";
    cout << "\n";
}

/* ----------------------------
   Dijkstra’s Algorithm (Simple O(n^2))
   ---------------------------- */
void dijkstra(int start){
    for(int i=0;i<n;i++){
        distArr[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    distArr[start] = 0;

    for(int count=0;count<n;count++){
        // Pick closest unvisited node
        int minDist = INF, u = -1;
        for(int i=0;i<n;i++){
            if(!visited[i] && distArr[i] < minDist){
                minDist = distArr[i];
                u = i;
            }
        }

        if(u==-1) break; // no reachable unvisited node

        visited[u] = true;
        cout << "Visiting node " << u << " with current distance " << distArr[u] << "\n";

        // Relax all neighbors
        for(int v=0;v<n;v++){
            if(graph[u][v] != 0 && !visited[v]){
                if(distArr[u] + graph[u][v] < distArr[v]){
                    cout << "Updating distance of node " << v << " from " << distArr[v]
                         << " to " << distArr[u] + graph[u][v] << "\n";
                    distArr[v] = distArr[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
        cout << "\n";
    }
}

/* ----------------------------
   Display All Distances and Paths
   ---------------------------- */
void displayDistances(int start){
    cout << "Minimum fuel cost from node " << start << " to all locations:\n";
    for(int i=0;i<n;i++){
        cout << "To " << i << " = " << distArr[i] << " | ";
        printPath(i);
    }
}


void runDijkstraExample(){
    initializeGraph();
    int start = 0;
    dijkstra(start);
    displayDistances(start);
}

int main(){
    cout << "=== Minimum Fuel Cost Computation (Dijkstra) ===\n\n";
    runDijkstraExample();
    return 0;
}
