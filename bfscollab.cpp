#include <iostream>
using namespace std;

const int MAX = 50;

int graph[MAX][MAX];
int visited[MAX];
int distanceFarm[MAX];
int queueArr[100];
int front = 0, rear = 0;

// Queue operations
void enqueue(int node) {
    queueArr[rear++] = node;
}

int dequeue() {
    return queueArr[front++];
}

bool isQueueEmpty() {
    return front == rear;
}

// Reset visited and distance arrays
void resetArrays(int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        distanceFarm[i] = -1;
    }
}

// BFS traversal
void bfs(int n, int start) {
    resetArrays(n);

    visited[start] = 1;
    distanceFarm[start] = 0;
    enqueue(start);

    while (!isQueueEmpty()) {
        int u = dequeue();

        for (int v = 0; v < n; v++) {
            if (graph[u][v] == 1 && !visited[v]) {
                visited[v] = 1;
                distanceFarm[v] = distanceFarm[u] + 1;
                enqueue(v);
            }
        }
    }
}



// Display the distances
void displayDistances(int n, int start) {
    cout << "Minimum hops from Farm " << start << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "To Farm " << i << " = " << distanceFarm[i] << " steps\n";
    }
}

// Initialize the graph
void initializeGraph(int n) {
    int temp[5][5] = {
        {0,1,0,0,0},
        {1,0,1,0,0},
        {0,1,0,1,1},
        {0,0,1,0,1},
        {0,0,1,1,0}
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = temp[i][j];
}


// Controller function
void runBFSExample() {
    int n = 5;
    int startFarm = 0;

    initializeGraph(n);

    bfs(n, startFarm);

    displayDistances(n, startFarm);
}

int main() {
    runBFSExample();
    return 0;
}
