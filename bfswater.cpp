#include <iostream>
using namespace std;

/*
PROBLEM STATEMENT:
Traverse all connected zones in a water distribution network starting
from a main source, using BFS to ensure zones are visited in order of
their distance (number of connections) from the source.

WHY BFS:
BFS guarantees visiting zones level by level, which helps model
the spread or inspection of resources efficiently.
*/

const int MAX = 50;

// Function to initialize adjacency matrix
void initializeAdjacency(int n, int adj[MAX][MAX]) {
    int temp[5][5] = { 
        {0,1,0,1,0},
        {1,0,1,1,1},
        {0,1,0,0,1},
        {1,1,0,0,1},
        {0,1,1,1,0}
    };
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            adj[i][j] = temp[i][j];
}

// Queue helper functions
void enqueue(int queue[], int &rear, int value) {
    queue[rear++] = value;
}

int dequeue(int queue[], int &front) {
    return queue[front++];
}

bool isEmpty(int front, int rear) {
    return front == rear;
}

// BFS traversal
void bfsTraversal(int n, int adj[MAX][MAX], int source) {
    bool visited[MAX] = {false};
    int queue[100];
    int front = 0, rear = 0;

    enqueue(queue, rear, source);
    visited[source] = true;

    int step = 0;
    cout << "BFS Traversal starting from Zone " << source << ":\n";

    while(!isEmpty(front, rear)) {
        int size = rear - front; // all nodes at current step
        step++;
        cout << "\nStep " << step << ": ";

        for(int i=0; i<size; i++) {
            int u = dequeue(queue, front);
            cout << u << " "; // print current zone

            for(int v=0; v<n; v++) {
                if(adj[u][v] && !visited[v]) {
                    visited[v] = true;
                    enqueue(queue, rear, v);
                }
            }
        }
    }

    cout << "\nTraversal complete.\n";
}

// Display adjacency matrix
void displayAdjacency(int n, int adj[MAX][MAX]) {
    cout << "\nAdjacency Matrix:\n";
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++)
            cout << adj[i][j] << " ";
        cout << "\n";
    }
}

// Controller function
void runBFSExample() {
    int n = 5;
    int adj[MAX][MAX];
    int source = 0;

    initializeAdjacency(n, adj);
    displayAdjacency(n, adj);

    cout << "\nStarting BFS from source zone: " << source << endl;
    bfsTraversal(n, adj, source);
}

int main() {
    runBFSExample();
    return 0;
}
