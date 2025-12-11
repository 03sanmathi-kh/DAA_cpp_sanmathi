#include <iostream>
using namespace std;

int graphDFS[10][10];   // Adjacency matrix for routes between locations
bool visitedDFS[10];    // Keeps track of visited nodes to avoid loops
int path[10];           // Stores current route being explored
int n;

// Depth-First Search function
// u      → current node
// target → destination we want to reach
// depth  → position in the current path
void dfs(int u, int target, int depth) {

    visitedDFS[u] = true;     // mark current node as visited
    path[depth] = u;          // store the node in our route path

    // If we reached the destination, print the entire route
    if (u == target) {
        cout << "Route: ";
        for (int i = 0; i <= depth; i++)
            cout << path[i] << " ";
        cout << "\n";

        visitedDFS[u] = false; // unmark for other possible paths
        return;
    }

    // Explore all neighbours of the current node
    for (int v = 0; v < n; v++) {

        // If route exists (1) and not already visited
        if (graphDFS[u][v] == 1 && !visitedDFS[v])
            dfs(v, target, depth + 1);   // go deeper into DFS
    }

    // Backtracking step:
    // Unmark current node so other paths can use it
    visitedDFS[u] = false;
}

int main() {

    n = 6; // Total 6 nodes (Farms, junctions, mills, factories)

    // Graph adjacency matrix:
    // 1 = direct road exists
    // 0 = no road
    int temp[6][6] = {
        {0,1,1,0,0,0},
        {1,0,1,1,0,0},
        {1,1,0,1,1,0},
        {0,1,1,0,1,1},
        {0,0,1,1,0,1},
        {0,0,0,1,1,0}
    };

    // Load into graphDFS
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            graphDFS[i][j] = temp[i][j];

    cout << "All possible routes from Farm 0 → Factory 5:\n";

    // Start DFS from node 0 to node 5
    dfs(0, 5, 0);

    return 0;
}
