#include <iostream>
using namespace std;

/* ============================================================
   PART 1: DIJKSTRA (Simple version without priority_queue)
   ============================================================ */

// MAX nodes
const int N = 6;
int graph1[N][N];     // weighted graph
int dist1[N];         // distance array
bool visited1[N];     // visited tracker

// Simple Dijkstra – finds shortest path from src
void dijkstra(int src) {

    // Initialize all distances as large
    for (int i = 0; i < N; i++) {
        dist1[i] = 9999;
        visited1[i] = false;
    }

    dist1[src] = 0;

    // Repeat N times
    for (int count = 0; count < N - 1; count++) {

        int u = -1;

        // Pick unvisited node with smallest distance
        for (int i = 0; i < N; i++) {
            if (!visited1[i] &&
                (u == -1 || dist1[i] < dist1[u]))
                u = i;
        }

        visited1[u] = true;

        // Relax edges
        for (int v = 0; v < N; v++) {
            if (graph1[u][v] > 0 && !visited1[v]) {

                int newDist = dist1[u] + graph1[u][v];

                if (newDist < dist1[v])
                    dist1[v] = newDist;
            }
        }
    }

    cout << "\nDijkstra (Shortest Time From Farm 0):\n";
    for (int i = 0; i < N; i++)
        cout << "To node " << i << " = " << dist1[i] << "\n";
}

/* ============================================================
   PART 2: BELLMAN–FORD (Handles hazard penalties)
   ============================================================ */

struct EdgeBF {
    int u, v, w;   // edge: u → v with weight w
};

EdgeBF edges[20];
int dist2[N];

void bellmanFord(int src, int edgeCount) {

    // Initially everything is large
    for (int i = 0; i < N; i++)
        dist2[i] = 9999;

    dist2[src] = 0;

    // Relax edges N-1 times
    for (int i = 0; i < N - 1; i++) {
        for (int e = 0; e < edgeCount; e++) {

            int u = edges[e].u;
            int v = edges[e].v;
            int w = edges[e].w;

            if (dist2[u] + w < dist2[v])
                dist2[v] = dist2[u] + w;
        }
    }

    cout << "\nBellman-Ford (Hazard-Adjusted Costs From 0):\n";
    for (int i = 0; i < N; i++)
        cout << "To node " << i << " = " << dist2[i] << "\n";
}

/* ============================================================
   PART 3: FLOYD–WARSHALL (All-Pairs Shortest Paths)
   ============================================================ */

int fw[N][N];

void floydWarshall() {

    // Floyd-Warshall core logic
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (fw[i][k] + fw[k][j] < fw[i][j])
                    fw[i][j] = fw[i][k] + fw[k][j];

    cout << "\nFloyd-Warshall (All-Pairs Best Routes):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << fw[i][j] << " ";
        cout << "\n";
    }
}


/* ============================================================
   PART 4: SIMPLE MIN-COST COTTON FLOW (Greedy)
   ============================================================ */

struct EdgeCost {
    int cost;
    int cap;
};

EdgeCost supplyGraph[5][5];

void minCostCotton() {

    int farms = 2, mills = 3;

    int cost[2][3] = {
        {4, 2, 5},
        {3, 1, 4}
    };

    int cap[2][3] = {
        {30, 20, 10},
        {25, 15, 20}
    };

    int demand[3] = {25, 20, 20};
    int supply[2] = {40, 25};

    for (int i = 0; i < farms; i++)
        for (int j = 0; j < mills; j++) {
            supplyGraph[i][j].cost = cost[i][j];
            supplyGraph[i][j].cap = cap[i][j];
        }

    int total = 0;

    cout << "\nGreedy Min-Cost Cotton Distribution:\n";

    // For each mill, take the cheapest possible supply
    for (int j = 0; j < mills; j++) {
        while (demand[j] > 0) {

            int bestFarm = -1, bestCost = 9999;

            // Pick cheapest farm with supply left
            for (int i = 0; i < farms; i++) {
                if (supply[i] > 0 &&
                    supplyGraph[i][j].cost < bestCost) {
                    bestCost = supplyGraph[i][j].cost;
                    bestFarm = i;
                }
            }

            int send = (supply[bestFarm] < demand[j])
                       ? supply[bestFarm] : demand[j];

            supply[bestFarm] -= send;
            demand[j] -= send;
            total += send * bestCost;

            cout << "Send " << send
                 << " from Farm " << bestFarm
                 << " → Mill " << j
                 << " at cost " << bestCost << "\n";
        }
    }

    cout << "Total Minimum Cotton Transport Cost = " << total << "\n";
}


/* ============================================================
   MAIN – RUN ALL FOUR SOLUTIONS
   ============================================================ */

int main() {

    // ------------------ Setup for Dijkstra and Floyd-Warshall ------------------
    int simpleGraph[6][6] = {
        {0, 4, 2, 0, 0, 0},
        {4, 0, 1, 7, 0, 0},
        {2, 1, 0, 3, 4, 0},
        {0, 7, 3, 0, 2, 5},
        {0, 0, 4, 2, 0, 1},
        {0, 0, 0, 5, 1, 0}
    };

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            graph1[i][j] = simpleGraph[i][j];
            fw[i][j] = (simpleGraph[i][j] == 0 && i != j)
                       ? 9999 : simpleGraph[i][j];
        }

    // ------------------ Setup for Bellman-Ford ------------------
    int edgeCount = 0;

    // Convert adjacency matrix to edge list
    for (int u = 0; u < N; u++)
        for (int v = 0; v < N; v++)
            if (simpleGraph[u][v] > 0) {
                edges[edgeCount].u = u;
                edges[edgeCount].v = v;
                edges[edgeCount].w = simpleGraph[u][v];
                edgeCount++;
            }

    // ------------------ Run All Algorithms ------------------
    dijkstra(0);                 // shortest path
    bellmanFord(0, edgeCount);  // hazard-adjusted
    floydWarshall();             // all-pairs shortest routes
    minCostCotton();             // min-cost cotton allocation

    return 0;
}
