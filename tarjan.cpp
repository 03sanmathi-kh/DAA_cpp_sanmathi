#include <iostream>
#include <vector>
using namespace std;

/*
    Structural Integrity Checker for Buildings
    ------------------------------------------
    - Each structural element (column, beam, etc.) is represented as a node.
    - Connections between elements represent load paths.
    - A "critical element" is one whose failure can disconnect parts of the building.
    - Uses DFS-based Tarjan’s algorithm to find articulation points.
*/

class Building {
    int numElements; // Number of structural elements (nodes)
    vector<vector<int>> connections; // Adjacency list for connections between elements

    // DFS helper to find critical elements
    void dfs(int u, vector<bool>& visited, vector<int>& discoveryTime,
             vector<int>& lowTime, vector<int>& parent, vector<bool>& isCritical, int& time) {

        visited[u] = true;
        discoveryTime[u] = lowTime[u] = ++time;
        int childCount = 0;

        cout << "\nVisiting Element " << u 
             << " | Discovery Time = " << discoveryTime[u]
             << " | Low Time = " << lowTime[u] << endl;

        for (int v : connections[u]) {
            if (!visited[v]) {
                childCount++;
                parent[v] = u;
                cout << " -> Going deeper from " << u << " to " << v << endl;

                dfs(v, visited, discoveryTime, lowTime, parent, isCritical, time);

                lowTime[u] = min(lowTime[u], lowTime[v]);

                cout << "Backtracking to " << u << " from " << v
                     << " | Updated Low Time = " << lowTime[u] << endl;

                if (parent[u] == -1 && childCount > 1) {
                    isCritical[u] = true;
                    cout << " --> Root element " << u << " is critical (childCount = " << childCount << ")\n";
                }

                if (parent[u] != -1 && lowTime[v] >= discoveryTime[u]) {
                    isCritical[u] = true;
                    cout << " --> Element " << u << " is critical because lowTime[" << v << "] >= discoveryTime[" << u << "]\n";
                }

            } else if (v != parent[u]) {
                lowTime[u] = min(lowTime[u], discoveryTime[v]);
                cout << "   Found back-edge from " << u << " to " << v 
                     << " | Updated Low Time = " << lowTime[u] << endl;
            }
        }
    }

public:
    Building(int n) : numElements(n), connections(n) {}

    void addConnection(int a, int b) {
        connections[a].push_back(b);
        connections[b].push_back(a);
    }

    void printConnections() {
        cout << "\nBuilding Connections:\n";
        for (int i = 0; i < numElements; i++) {
            cout << "Element " << i << ": ";
            for (int v : connections[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    void findCriticalElements() {
        vector<bool> visited(numElements, false);
        vector<int> discoveryTime(numElements, -1);
        vector<int> lowTime(numElements, -1);
        vector<int> parent(numElements, -1);
        vector<bool> isCritical(numElements, false);
        int time = 0;

        for (int i = 0; i < numElements; i++) {
            if (!visited[i]) {
                cout << "\nStarting DFS from Element " << i << endl;
                dfs(i, visited, discoveryTime, lowTime, parent, isCritical, time);
            }
        }

        cout << "\n============================\n";
        cout << "Critical Structural Elements:\n";
        for (int i = 0; i < numElements; i++) {
            if (isCritical[i])
                cout << "Element " << i << " is critical\n";
        }
        cout << "============================\n";
    }
};

int main() {
    int n, m;
    cout << "Enter number of structural elements in the building: ";
    cin >> n;
    cout << "Enter number of connections between elements: ";
    cin >> m;

    Building building(n);

    cout << "\nEnter the connections (two elements per connection, 0-based indexing):\n";
    for (int i = 0; i < m; i++) {
        int a, b;
        cout << "Connection " << i+1 << ": ";
        cin >> a >> b;
        building.addConnection(a, b);
    }

    building.printConnections();

    building.findCriticalElements();

    return 0;
}
