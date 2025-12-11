#include <iostream>
using namespace std;

const int INF = 1e9;
const int MAX = 50;

int graph[MAX][MAX];    // adjacency matrix (costs)
int distArr[MAX];       // distance array
bool visited[MAX];      // visited nodes

// Simple Dijkstra (O(n^2))
void dijkstra(int n, int start) {
    for (int i = 0; i < n; i++) {
        distArr[i] = INF;
        visited[i] = false;
    }

    distArr[start] = 0;

    for (int count = 0; count < n - 1; count++) {

        // Pick unvisited node with smallest distance
        int minDist = INF, u = -1;
        for (int i = 0; i < n; i++)
            if (!visited[i] && distArr[i] < minDist) {
                minDist = distArr[i];
                u = i;
            }

        visited[u] = true;

        // Relax neighbors
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != 0 &&
                distArr[u] + graph[u][v] < distArr[v]) {

                distArr[v] = distArr[u] + graph[u][v];
            }
        }
    }
}

int main() {
    int n = 6;  // 6 locations (farms + mills + factories)

    // Simple example graph (fuel cost)
    int temp[6][6] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 3, 0, 0, 0},
        {0, 3, 0, 2, 7, 0},
        {0, 0, 2, 0, 3, 4},
        {0, 0, 7, 3, 0, 1},
        {0, 0, 0, 4, 1, 0}
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = temp[i][j];

    dijkstra(n, 0);  // starting from Farm 0

    cout << "Minimum fuel cost from Farm 0 to all locations:\n";
    for (int i = 0; i < n; i++)
        cout << "To " << i << " = " << distArr[i] << "\n";

    return 0;
}
