#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Prim + Dijkstra demonstration

const int INF = INT_MAX;
int n = 5; // number of nodes (treatment plants + zones)

// Graph represented as adjacency matrix (weights = pipeline cost)
int cost[5][5] = {
    {0, 2, 0, 6, 0},
    {2, 0, 3, 8, 5},
    {0, 3, 0, 0, 7},
    {6, 8, 0, 0, 9},
    {0, 5, 7, 9, 0}
};

// Prim's Algorithm to find Minimum Spanning Tree
void primMST() {
    int parent[n]; // stores MST
    int key[n];    // cost to connect node
    bool mstSet[n]; // included in MST

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[0] = 0;   // start from node 0
    parent[0] = -1;

    for (int count = 0; count < n-1; count++) {
        int minKey = INF, u;
        for (int v = 0; v < n; v++)
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }

        mstSet[u] = true;

        for (int v = 0; v < n; v++)
            if (cost[u][v] && !mstSet[v] && cost[u][v] < key[v]) {
                parent[v] = u;
                key[v] = cost[u][v];
            }
    }

    cout << "Prim MST (Pipeline Connections):\n";
    for (int i = 1; i < n; i++)
        cout << "Node " << parent[i] << " - " << i << " : Cost = " << cost[i][parent[i]] << endl;
}

// Dijkstra's Algorithm to find shortest path from source
void dijkstra(int src) {
    int dist[n];
    bool visited[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < n-1; count++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        visited[u] = true;

        for (int v = 0; v < n; v++)
            if (cost[u][v] && dist[u] + cost[u][v] < dist[v])
                dist[v] = dist[u] + cost[u][v];
    }

    cout << "\nShortest paths from source " << src << ":\n";
    for (int i = 0; i < n; i++)
        cout << "To node " << i << " = " << dist[i] << endl;
}

int main() {
    primMST();
    dijkstra(0); // shortest path from node 0 (river)
    return 0;
}
