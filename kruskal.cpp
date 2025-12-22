#include <iostream>
#include <climits> // For INT_MAX
using namespace std;

/*
PROBLEM:
Design a cost-efficient water pipeline network connecting zones/plants.
- Build MST (Minimum Spanning Tree) using Kruskal to minimize pipeline cost.
- Compute shortest delivery paths from main river using Dijkstra.

APPROACH:
1. Kruskal MST:
   - Sort pipelines by cost
   - Use DSU to avoid cycles
   - Select edges until all zones are connected

2. Dijkstra:
   - Compute minimum distances from source river to all zones
   
*/

// Edge structure for pipelines
struct Edge {
    int from, to, cost;
};

// DSU arrays
int parent[100];

// Find root with path compression
int findRoot(int x) {
    if(parent[x] == x) return x;
    return parent[x] = findRoot(parent[x]);
}

// Unite two sets
void connect(int a, int b) {
    parent[findRoot(a)] = findRoot(b);
}

// Sort edges by cost (Selection sort)
void sortEdgesByCost(Edge edges[], int m) {
    for(int i = 0; i < m - 1; i++) {
        int minIdx = i;
        for(int j = i + 1; j < m; j++)
            if(edges[j].cost < edges[minIdx].cost)
                minIdx = j;
        Edge temp = edges[i];
        edges[i] = edges[minIdx];
        edges[minIdx] = temp;
    }
}

// Print adjacency matrix
void printAdjMatrix(int adj[][100], int n) {
    cout << "\nAdjacency Matrix (MST):\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << adj[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

// Build MST using Kruskal and fill adjacency matrix
void buildMST(int n, int m, Edge pipelines[], int adj[][100]) {
    cout << "Building Kruskal MST...\n";
    for(int i = 0; i < n; i++) parent[i] = i;

    for(int i = 0; i < m; i++) {
        int u = pipelines[i].from;
        int v = pipelines[i].to;
        int w = pipelines[i].cost;

        if(findRoot(u) != findRoot(v)) {
            connect(u, v);
            adj[u][v] = w;
            adj[v][u] = w;
            cout << "Selected Edge: Zone " << u << " - Zone " << v << " | Cost = " << w << endl;
        } else {
            cout << "Skipping Edge (would form cycle): Zone " << u << " - Zone " << v << endl;
        }
    }
    printAdjMatrix(adj, n);
}

// Dijkstra to compute shortest paths
void dijkstra(int n, int adj[][100], int source) {
    int dist[100];
    bool visited[100];
    for(int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[source] = 0;

    cout << "Running Dijkstra from River (Node " << source << ")...\n";

    for(int i = 0; i < n; i++) {
        int u = -1;
        for(int j = 0; j < n; j++)
            if(!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;

        if(dist[u] == INT_MAX) {
            cout << "Remaining nodes unreachable. Ending Dijkstra.\n";
            break;
        }

        visited[u] = true;
        cout << "Visiting Node " << u << " | Current Distance = " << dist[u] << endl;

        for(int v = 0; v < n; v++) {
            if(adj[u][v] != 0 && !visited[v]) {
                if(dist[u] + adj[u][v] < dist[v]) {
                    cout << "Updating Distance: Node " << v << " | Old = " << dist[v] 
                         << " | New = " << dist[u] + adj[u][v] << " via Node " << u << endl;
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }

    cout << "\nFinal Shortest Water Paths from River:\n";
    for(int i = 0; i < n; i++) {
        if(dist[i] == INT_MAX) cout << "Zone " << i << " : Unreachable\n";
        else cout << "Zone " << i << " : Distance = " << dist[i] << endl;
    }
}

int main() {
    int n = 5; // Zones
    int m = 7; // Pipelines

    Edge pipelines[7] = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}, {3,4,9}
    };

    int adj[100][100];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            adj[i][j] = 0;

    cout << "Sorting edges by cost...\n";
    sortEdgesByCost(pipelines, m);

    buildMST(n, m, pipelines, adj);
    dijkstra(n, adj, 0);

    return 0;
}

