#include <iostream>
#include <vector>
using namespace std;

/*
PROBLEM:
Find all possible routes from a starting location (e.g., Farm)
to a destination (e.g., Factory) in a network of roads. The network
is represented using an adjacency matrix.

WHY DFS:
Depth-First Search is ideal here because it explores one route completely
before backtracking, allowing us to find all possible paths between nodes.
*/

/* ----------------------------
   Global Variables
   ---------------------------- */
int n; // number of nodes
vector<vector<int>> graphDFS;
vector<bool> visitedDFS;
vector<int> path; // stores current path

/* ----------------------------
   Function to Print Current Path
   ---------------------------- */
void printPath(int depth){
    cout << "Route: ";
    for(int i=0;i<=depth;i++)
        cout << path[i] << " ";
    cout << "\n";
}

/* ----------------------------
   Recursive DFS Function
   ---------------------------- */
void dfs(int u, int target, int depth) {
    visitedDFS[u] = true;
    path[depth] = u;

    cout << "Exploring node " << u << " at depth " << depth << "\n";

    // If destination reached, print the route
    if(u == target){
        cout << "Destination reached! ";
        printPath(depth);
        visitedDFS[u] = false; // backtrack
        cout << "Backtracking from node " << u << "\n\n";
        return;
    }

    // Explore neighbors
    for(int v=0;v<n;v++){
        if(graphDFS[u][v] == 1 && !visitedDFS[v]){
            cout << "Moving from node " << u << " to node " << v << "\n";
            dfs(v, target, depth+1);
        }
    }

    // Backtracking
    visitedDFS[u] = false;
    cout << "Backtracking from node " << u << " to previous node\n\n";
}

/* ----------------------------
   Initialize Graph
   ---------------------------- */
void initializeGraph(){
    n = 6; // total nodes
    int temp[6][6] = {
        {0,1,1,0,0,0},
        {1,0,1,1,0,0},
        {1,1,0,1,1,0},
        {0,1,1,0,1,1},
        {0,0,1,1,0,1},
        {0,0,0,1,1,0}
    };

    graphDFS.resize(n, vector<int>(n));
    visitedDFS.resize(n,false);
    path.resize(n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            graphDFS[i][j] = temp[i][j];

    cout << "Graph initialized with adjacency matrix:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout << graphDFS[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

/* ----------------------------
   Controller Function
   ---------------------------- */
void runDFSExample(int start, int target){
    cout << "Finding all routes from node " << start << " to node " << target << ":\n\n";
    dfs(start, target, 0);
    cout << "DFS traversal completed.\n";
}

/* ----------------------------
   Main Function
   ---------------------------- */
int main(){
    initializeGraph();
    int start = 0, target = 5;
    runDFSExample(start, target);
    return 0;
}
