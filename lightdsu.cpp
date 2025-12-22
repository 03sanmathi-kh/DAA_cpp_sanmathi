#include <iostream>
using namespace std;

/*
  Streetlight Cluster Simulation
  ------------------------------
  - Each streetlight zone can belong to a cluster
  - Clusters are formed via connected zones
  - Activity in any zone turns ON the entire cluster
  - Uses Union-Find to efficiently manage clusters
*/

class UnionFind {
private:
    int cluster[100]; // cluster[i] = representative of zone i
public:
    // Initialize each zone as its own cluster
    void init(int n) {
        for (int i = 0; i < n; i++) {
            cluster[i] = i;
        }
    }

    // Find representative with path compression
    int find(int x) {
        if (cluster[x] == x) return x;
        return cluster[x] = find(cluster[x]);
    }

    // Unite two clusters
    void unite(int x, int y) {
        int cx = find(x);
        int cy = find(y);
        if (cx != cy) {
            cluster[cy] = cx;
            cout << "Merging clusters: Zone " << x << " (rep " << cx << ") "
                 << "and Zone " << y << " (rep " << cy << ")\n";
        }
    }

    // Print clusters for debugging
    void printClusters(int n) {
        cout << "\nCluster representatives per zone:\n";
        for (int i = 0; i < n; i++) {
            cout << "Zone " << i << " -> Cluster " << find(i) << endl;
        }
        cout << endl;
    }
};

int main() {
    int zones = 10; // total streetlight zones
    UnionFind uf;
    uf.init(zones);

    // Define connections (adjacent streets)
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);
    uf.unite(4, 5);
    uf.unite(6, 7);
    uf.unite(7, 8);
    uf.unite(8, 9);
    uf.unite(2, 3); // merge two clusters
    uf.unite(5, 6); // merge another clusters

    uf.printClusters(zones);

    // Activity changes over time (simulating multiple time steps)
    int timeSteps = 5;
    int activity[10][5] = {
        {1,0,0,0,1}, // Zone 0
        {0,0,1,0,0}, // Zone 1
        {0,1,0,0,0}, // Zone 2
        {0,0,0,1,0}, // Zone 3
        {0,1,0,0,0}, // Zone 4
        {1,0,0,1,0}, // Zone 5
        {0,0,1,0,1}, // Zone 6
        {0,1,0,0,0}, // Zone 7
        {1,0,0,1,0}, // Zone 8
        {0,0,1,0,1}  // Zone 9
    };

    // Cluster active status
    int clusterActive[100] = {0};

    // Process each time step
    for (int t = 0; t < timeSteps; t++) {
        cout << "==== Time Step " << t+1 << " ====\n";
        // Reset cluster status
        for (int i = 0; i < zones; i++) clusterActive[i] = 0;

        // Update cluster status based on activity
        for (int i = 0; i < zones; i++) {
            if (activity[i][t] == 1) {
                int c = uf.find(i);
                clusterActive[c] = 1;
                cout << "Activity detected in Zone " << i
                     << " -> Cluster " << c << " activated.\n";
            }
        }

        // Display streetlight status
        cout << "Streetlight status at time " << t+1 << ":\n";
        for (int i = 0; i < zones; i++) {
            int c = uf.find(i);
            cout << "Zone " << i << ": " 
                 << (clusterActive[c] ? "ON" : "OFF") << endl;
        }
        cout << "-------------------------------\n\n";
    }

    // Summary of clusters
    cout << "Final Cluster Summary:\n";
    for (int i = 0; i < zones; i++) {
        int c = uf.find(i);
        cout << "Zone " << i << " belongs to Cluster " << c << endl;
    }

    return 0;
}
