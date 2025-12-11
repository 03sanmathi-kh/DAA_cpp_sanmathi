#include <iostream>
using namespace std;

// Each edge stores:
// cost     → cost of sending 1 unit of cotton
// capacity → maximum amount that can be sent on this route
struct Edge {
    int cost;
    int capacity;
};

Edge supplyGraph[5][5]; // Farm → Mill graph with cost + capacity

int main() {
    int farms = 2, mills = 3;

    // Cost matrix: cost[i][j] = cost from Farm i → Mill j
    // These costs represent fuel usage, tolls, distance, etc.
    int cost[2][3] = {
        {4, 2, 5},   // Farm 0 → Mill 0,1,2
        {3, 1, 4}    // Farm 1 → Mill 0,1,2
    };

    // Capacities: max amount each farm can send to each mill
    int cap[2][3] = {
        {30, 20, 10},
        {25, 15, 20}
    };

    // Demand required at each mill (how much cotton each mill needs)
    int demand[3] = {25, 20, 20};

    // Supply available at each farm
    int supply[2] = {40, 25};

    // Fill the supplyGraph to store everything in one structure
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++) {
            supplyGraph[i][j].cost = cost[i][j];
            supplyGraph[i][j].capacity = cap[i][j];
        }

    int total = 0;

    cout << "Greedy Minimum Cost Allocation:\n";

    // Process every mill one-by-one
    // Goal: satisfy mill demand using cheapest possible farms first
    for (int j = 0; j < mills; j++) {

        // Continue until mill's demand becomes 0
        while (demand[j] > 0) {

            int bestFarm = -1, bestCost = 1e9;

            // Step 1: Find the farm that can supply at the LOWEST cost
            for (int i = 0; i < farms; i++) {

                // Farm must have supply available
                if (supply[i] > 0 &&
                    supplyGraph[i][j].cost < bestCost) {

                    bestCost = supplyGraph[i][j].cost;
                    bestFarm = i;
                }
            }

            // Step 2: Send as much as possible from the cheapest farm
            int send = min(supply[bestFarm], demand[j]);

            // Update supply at that farm
            supply[bestFarm] -= send;

            // Update remaining demand at mill
            demand[j] -= send;

            // Add cost to total cost
            total += send * bestCost;

            cout << "Send " << send << " from Farm "
                 << bestFarm << " → Mill " << j
                 << " at cost " << bestCost << "\n";
        }
    }

    cout << "\nTotal Minimum Cost = " << total << "\n";
    return 0;
}
