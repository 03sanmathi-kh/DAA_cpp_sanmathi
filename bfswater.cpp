#include <iostream>
using namespace std;

int main() {
    int n = 5; // number of zones (nodes)
    
    // Adjacency matrix representing connections (1 = connected, 0 = no connection)
    int adj[5][5] = { 
        {0,1,0,1,0},
        {1,0,1,1,1},
        {0,1,0,0,1},
        {1,1,0,0,1},
        {0,1,1,1,0}
    };

    bool visited[5] = {false}; // keep track of visited zones
    int queue[100]; // simple array-based queue
    int front = 0, rear = 0;

    int source = 0; // starting node (e.g., main water source)
    queue[rear++] = source; // enqueue source
    visited[source] = true;  // mark source as visited

    cout << "BFS Traversal starting from Zone " << source << ":\n";

    while(front < rear) {
        int u = queue[front++]; // dequeue next zone
        cout << u << " ";       // print current zone

        // Visit all neighbors of u
        for(int v = 0; v < n; v++) {
            if(adj[u][v] && !visited[v]) { // if connected and not visited
                visited[v] = true;         // mark as visited
                queue[rear++] = v;         // enqueue for future exploration
            }
        }
    }

    cout << endl;
    return 0;
}
