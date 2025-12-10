#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
  This program uses BFS to check the building's structural elements
  floor-by-floor and detect weak nodes.
  Each element is a node, and connections (load paths)
  are edges in an adjacency list.
*/

void bfsCheck(int start, vector<vector<int>>& graph, vector<int>& weak) {
    queue<int> q;
    vector<int> visited(graph.size(), 0);

    q.push(start);
    visited[start] = 1;

    cout << "BFS Structural Scan (Floor-by-Floor):\n";

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << "Checking element " << node;

        if (weak[node] == 1)
            cout << "  --> WEAK POINT FOUND!";

        cout << endl;

        for (int next : graph[node]) {
            if (!visited[next]) {
                visited[next] = 1;
                q.push(next);
            }
        }
    }
}

int main() {
    // Example building graph with 6 structural nodes
    vector<vector<int>> graph = {
        {1, 2},   // Node 0 connected to 1,2
        {0, 3},   // Node 1 connected to 0,3
        {0, 3},   // Node 2 connected to 0,3
        {1, 2, 4},// Node 3 connected to 1,2,4
        {3, 5},   // Node 4 connected to 3,5
        {4}       // Node 5 connected to 4
    };

    // 1 = weak element, 0 = strong
    vector<int> weak = {0, 1, 0, 0, 1, 0};

    bfsCheck(0, graph, weak);

    return 0;
}
