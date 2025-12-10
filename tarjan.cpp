#include <iostream>
#include <vector>
using namespace std;

// This program finds "critical structural elements" (like columns or beams)
// in a multistory building. If any of these fail, parts of the building 
// might become disconnected. We use a simple graph approach.

class Building {
    int numElements; // Number of structural elements (nodes)
    vector<vector<int>> connections; // Adjacency list for connections between elements

    // Helper function for DFS traversal to find critical elements
    void dfs(int u, vector<bool>& visited, vector<int>& discoveryTime,
             vector<int>& lowTime, vector<int>& parent, vector<bool>& isCritical, int& time) {
        
        visited[u] = true;          // Mark current element as visited
        discoveryTime[u] = lowTime[u] = ++time; // Set discovery and low times
        int childCount = 0;         // To count child nodes in DFS

        for (int v : connections[u]) {
            if (!visited[v]) {
                // If neighbor not visited, visit it
                childCount++;
                parent[v] = u;
                dfs(v, visited, discoveryTime, lowTime, parent, isCritical, time);

                // Update the low value of current node
                lowTime[u] = min(lowTime[u], lowTime[v]);

                // Condition 1: Root element with more than one child is critical
                if (parent[u] == -1 && childCount > 1)
                    isCritical[u] = true;

                // Condition 2: Non-root element whose low time of a child
                // is >= discovery time of current element is critical
                if (parent[u] != -1 && lowTime[v] >= discoveryTime[u])
                    isCritical[u] = true;
            } else if (v != parent[u]) {
                // If neighbor already visited and not parent, update low time
                lowTime[u] = min(lowTime[u], discoveryTime[v]);
            }
        }
    }

public:
    Building(int n) : numElements(n), connections(n) {}

    void addConnection(int a, int b) {
        connections[a].push_back(b);
        connections[b].push_back(a);
    }

    void findCriticalElements() {
        vector<bool> visited(numElements, false);
        vector<int> discoveryTime(numElements, -1);
        vector<int> lowTime(numElements, -1);
        vector<int> parent(numElements, -1);
        vector<bool> isCritical(numElements, false);
        int time = 0;

        // Run DFS for every unvisited element
        for (int i = 0; i < numElements; i++) {
            if (!visited[i])
                dfs(i, visited, discoveryTime, lowTime, parent, isCritical, time);
        }

        // Print all critical elements
        cout << "Critical Structural Elements:\n";
        for (int i = 0; i < numElements; i++) {
            if (isCritical[i])
                cout << "Element " << i << " is critical\n";
        }
    }
};

int main() {
    // Example building with 6 elements
    Building building(6);

    // Connect elements (like beams or columns connected in structure)
    building.addConnection(0, 1);
    building.addConnection(0, 2);
    building.addConnection(1, 3);
    building.addConnection(2, 3);
    building.addConnection(3, 4);
    building.addConnection(4, 5);

    // Find critical elements in the structure
    building.findCriticalElements();

    return 0;
}
