#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Factory structure
struct Factory {
    int id;
    int demand;
    int urgency;
    double efficiency;
};

// Function to forecast average of last k arrivals
double forecast(const vector<int>& arrivals, int k) {
    int n = arrivals.size();
    if (n == 0) return 0;
    if (k > n) k = n;
    int sum = 0;
    for (int i = n - k; i < n; ++i) sum += arrivals[i];
    return static_cast<double>(sum) / k;
}

// Allocate materials to factories based on urgency and efficiency
int allocate(vector<Factory>& factories, int materials) {
    cout << "\n=== Allocation Round ===\n";
    
    while (materials > 0) {
        int bestIndex = -1;
        // Find factory with highest urgency (tie-breaker: efficiency)
        for (size_t i = 0; i < factories.size(); i++) {
            if (factories[i].demand > 0) {
                if (bestIndex == -1 || factories[i].urgency > factories[bestIndex].urgency ||
                    (factories[i].urgency == factories[bestIndex].urgency && factories[i].efficiency > factories[bestIndex].efficiency)) {
                    bestIndex = i;
                }
            }
        }

        // If no factory needs materials, stop
        if (bestIndex == -1) break;

        // Allocate materials
        int allocated = min(materials, factories[bestIndex].demand);
        factories[bestIndex].demand -= allocated;
        materials -= allocated;

        cout << "Allocated " << allocated 
             << " units to Factory " << factories[bestIndex].id
             << " (Remaining demand: " << factories[bestIndex].demand << ")\n";
    }

    if (materials > 0) {
        cout << "Remaining materials unallocated: " << materials << " units\n";
    } else {
        cout << "All materials allocated successfully.\n";
    }

    return materials;
}

// Calculate total throughput
double throughput(const vector<Factory>& factories, const vector<int>& originalDemand) {
    double total = 0;
    for (size_t i = 0; i < factories.size(); i++) {
        int used = originalDemand[i] - factories[i].demand;
        total += used * factories[i].efficiency;
    }
    return total;
}

int main() {
    // Setup factories
    vector<Factory> factories = {{1, 50, 5, 1.2}, {2, 30, 8, 1.5}, {3, 40, 3, 1.1}};
    vector<int> originalDemand;
    for (auto f : factories) originalDemand.push_back(f.demand);

    // Incoming material arrivals
    vector<int> arrivals = {40, 20, 50, 30};

    cout << fixed << setprecision(2);
    for (size_t i = 0; i < arrivals.size(); i++) {
        cout << "\n=== Arrival " << i+1 << ": " << arrivals[i] << " units ===\n";
        double nextForecast = forecast(vector<int>(arrivals.begin(), arrivals.begin() + i + 1), 2);
        cout << "Forecast for next arrival: " << nextForecast << " units\n";

        int remaining = allocate(factories, arrivals[i]);
        cout << "Remaining materials after allocation: " << remaining << " units\n";
    }

    // Final throughput
    double totalThroughput = throughput(factories, originalDemand);
    cout << "\n=== Final Report ===\n";
    for (size_t i = 0; i < factories.size(); i++) {
        cout << "Factory " << factories[i].id
             << " | Remaining Demand: " << factories[i].demand << endl;
    }
    cout << "Total Production Throughput: " << totalThroughput << endl;

    return 0;
}
