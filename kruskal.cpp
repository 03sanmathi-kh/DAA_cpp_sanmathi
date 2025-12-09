#include <iostream>
#include <climits> // for INT_MAX
using namespace std;

// Edge structure for pipelines
struct Edge {
    int from, to, cost;
};

// DSU arrays
int parent[100];

// Find root with path compression
int findRoot(int x) {
    if (parent[x] == x) return x;
    return parent[x] = findRoot(parent[x]);
}

// Unite two sets
void connect(int a, int b) {
    parent[findRoot(a)] = findRoot(b);
}

int main() {
    int n = 5; // number of zones/plants
    int m = 7; // number of possible pipelines

    // List of pipelines: from, to, cost
    Edge pipelines[7] = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}, {3,4,9}
    };

    // Initialize DSU
    for(int i = 0; i < n; i++) parent[i] = i;

    // Selection sort by cost (for Kruskal)
    for(int i = 0; i < m-1; i++) {
        int minIdx = i;
        for(int j = i+1; j < m; j++)
            if(pipelines[j].cost < pipelines[minIdx].cost) minIdx = j;
        Edge temp = pipelines[i];
        pipelines[i] = pipelines[minIdx];
        pipelines[minIdx] = temp;
    }

    // Build MST and adjacency matrix for Dijkstra
    int adj[100][100]; // adjacency matrix, 0 = no edge
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            adj[i][j] = 0;

    cout << "Kruskal MST (Cost-efficient water network):\n";
    for(int i = 0; i < m; i++) {
        int u = pipelines[i].from;
        int v = pipelines[i].to;
        int w = pipelines[i].cost;

        if(findRoot(u) != findRoot(v)) { // add edge if no cycle
            connect(u, v);
            cout << "Connect Zone " << u << " to Zone " << v << " | Cost = " << w << endl;
            adj[u][v] = w;
            adj[v][u] = w; // undirected graph
        }
    }

    // ---------------- Dijkstra for shortest water paths ----------------
    int dist[100]; // shortest distances from source
    bool visited[100]; // visited nodes
    int source = 0; // river node

    for(int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[source] = 0;

    for(int i = 0; i < n; i++) {
        int u = -1;
        // pick unvisited node with smallest distance
        for(int j = 0; j < n; j++)
            if(!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;

        if(dist[u] == INT_MAX) break; // remaining nodes unreachable
        visited[u] = true;

        // update neighbors
        for(int v = 0; v < n; v++) {
            if(adj[u][v] != 0 && !visited[v]) {
                if(dist[u] + adj[u][v] < dist[v])
                    dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    cout << "\nShortest water delivery paths from River (Node 0):\n";
    for(int i = 0; i < n; i++) {
        if(dist[i] == INT_MAX) cout << "Zone " << i << " : Unreachable\n";
        else cout << "Zone " << i << " : Distance = " << dist[i] << endl;
    }

    return 0;
}
