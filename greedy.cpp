#include <iostream>
#include <iomanip>
using namespace std;

/*
PROBLEM:
Allocate incoming raw materials to factories efficiently.
Each factory has:
- demand: how much it needs
- urgency: higher means needs allocation first
- efficiency: production multiplier for throughput

GOAL:
Maximize throughput while allocating materials based on urgency.

WHY GREEDY:
Allocate the most urgent factory first. If tie, pick the one with higher efficiency.
Repeat until materials exhausted.
*/

const int MAX_FACTORIES = 10;

int selectFactory(int n, int demand[], int urgency[], float efficiency[], int allocated[]) {
    int idx = -1;
    for(int i = 0; i < n; i++) {
        if(demand[i] > 0) {
            if(idx == -1 || urgency[i] > urgency[idx] ||
               (urgency[i] == urgency[idx] && efficiency[i] > efficiency[idx])) {
                idx = i;
            }
        }
    }
    return idx;
}

void allocateMaterials(int n, int demand[], int urgency[], float efficiency[], int allocated[], int &materials) {
    int idx = selectFactory(n, demand, urgency, efficiency, allocated);
    if(idx != -1 && materials > 0) {
        int alloc = (materials >= demand[idx]) ? demand[idx] : materials;
        demand[idx] -= alloc;
        allocated[idx] += alloc;
        materials -= alloc;
        cout << "Allocated " << alloc << " units to Factory " << (idx + 1)
             << " | Remaining demand: " << demand[idx] << " | Materials left: " << materials << "\n";
    } else {
        cout << "No suitable factory or materials exhausted.\n";
    }
}

float calculateThroughput(int n, int allocated[], float efficiency[]) {
    float throughput = 0;
    for(int i = 0; i < n; i++)
        throughput += allocated[i] * efficiency[i];
    return throughput;
}

void printStatus(int n, int demand[], int allocated[], float efficiency[], int materials) {
    cout << "\n--- Current Allocation Status ---\n";
    cout << setw(10) << "Factory" << setw(12) << "Allocated" 
         << setw(10) << "Demand" << setw(12) << "Efficiency" << "\n";
    for(int i = 0; i < n; i++) {
        cout << setw(10) << (i+1) 
             << setw(12) << allocated[i] 
             << setw(10) << demand[i] 
             << setw(12) << efficiency[i] << "\n";
    }
    cout << "Remaining materials: " << materials << "\n\n";
}

void simulateRounds(int n, int demand[], int urgency[], float efficiency[], int allocated[], int materialArrivals[], int rounds) {
    for(int r = 0; r < rounds; r++) {
        cout << "=== Round " << (r+1) << ": Incoming materials = " << materialArrivals[r] << " ===\n";
        int materials = materialArrivals[r];
        while(materials > 0) {
            int prev = materials;
            allocateMaterials(n, demand, urgency, efficiency, allocated, materials);
            if(prev == materials) break; // nothing allocated
        }
        printStatus(n, demand, allocated, efficiency, materials);
    }
}

int main() {
    int n = 3; // number of factories

    int demand[MAX_FACTORIES] = {50, 30, 40};
    int urgency[MAX_FACTORIES] = {5, 8, 3};
    float efficiency[MAX_FACTORIES] = {1.2, 1.5, 1.1};
    int allocated[MAX_FACTORIES] = {0};

    int original_demand[MAX_FACTORIES];
    for(int i = 0; i < n; i++) original_demand[i] = demand[i];

    int materialArrivals[3] = {70, 30, 20}; // materials arriving in rounds
    int rounds = 3;

    cout << "=== Greedy Material Allocation Simulation ===\n\n";
    simulateRounds(n, demand, urgency, efficiency, allocated, materialArrivals, rounds);

    float throughput = calculateThroughput(n, allocated, efficiency);
    cout << "=== Final Results ===\n";
    cout << "Total throughput achieved: " << throughput << "\n";

    return 0;
}
