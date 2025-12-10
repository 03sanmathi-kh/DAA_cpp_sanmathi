#include <iostream>
using namespace std;

// Simple Union-Find class to group connected streetlight zones
class UnionFind {
private:
    int cluster[100]; // cluster[i] stores the representative cluster of zone i
public:
    // Initialize each zone as its own cluster
    void init(int n) {
        for (int i = 0; i < n; i++)
            cluster[i] = i;
    }

    // Find the representative cluster of a zone
    int find(int x) {
        if (cluster[x] == x) return x; // If zone is its own cluster, return
        return find(cluster[x]);       // Otherwise, recursively find the representative
    }

    // Unite two zones into one cluster
    void unite(int x, int y) {
        int cx = find(x); // Find representative of x
        int cy = find(y); // Find representative of y
        if (cx != cy) {   // If they belong to different clusters, merge
            cluster[cy] = cx; // Make cx the representative of cy
        }
    }
};

int main() {
    int zones = 6; // Total streetlight zones

    UnionFind uf;
    uf.init(zones); // Initialize each zone as separate cluster

    // Define connections between zones (like adjacent streets)
    uf.unite(0, 1); // Zone 0 connected to Zone 1
    uf.unite(1, 2); // Zone 1 connected to Zone 2
    uf.unite(3, 4); // Zone 3 connected to Zone 4

    // Activity status: 1 = activity detected, 0 = no activity
    int activity[] = {1, 0, 1, 0, 1, 0};

    // Array to store cluster status: 1 = lights ON, 0 = lights OFF
    int clusterActive[100] = {0};

    // Loop through each zone
    for (int i = 0; i < zones; i++) {
        if (activity[i] == 1) {           // If any activity in the zone
            int c = uf.find(i);           // Find its cluster representative
            clusterActive[c] = 1;         // Turn ON lights for the entire cluster
        }
    }

    // Display streetlight status for each zone
    cout << "Streetlight cluster status:\n";
    for (int i = 0; i < zones; i++) {
        int c = uf.find(i); // Get cluster representative
        cout << "Zone " << i << ": " 
             << (clusterActive[c] ? "ON" : "OFF") << endl;
    }

    return 0;
}
