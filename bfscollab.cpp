#include <iostream>
using namespace std;

int graphBFS[50][50];
int visitedBFS[50];
int distBFS[50];
int q[100], front = 0, rear = 0;

void bfs(int n, int start) {
    for (int i = 0; i < n; i++) {
        visitedBFS[i] = 0;
        distBFS[i] = -1;
    }

    visitedBFS[start] = 1;
    distBFS[start] = 0;
    q[rear++] = start;

    while (front < rear) {
        int u = q[front++];

        for (int v = 0; v < n; v++) {
            if (graphBFS[u][v] == 1 && !visitedBFS[v]) {
                visitedBFS[v] = 1;
                distBFS[v] = distBFS[u] + 1;
                q[rear++] = v;
            }
        }
    }
}

int main() {
    int n = 5;
    int temp[5][5] = {
        {0,1,0,0,0},
        {1,0,1,0,0},
        {0,1,0,1,1},
        {0,0,1,0,1},
        {0,0,1,1,0}
    };

    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            graphBFS[i][j] = temp[i][j];

    bfs(n, 0);

    cout << "Fastest (minimum hops) from Farm 0:\n";
    for (int i = 0; i < n; i++)
        cout << "To " << i << " = " << distBFS[i] << " steps\n";

    return 0;
}
