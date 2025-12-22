#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
   Real-Time Tourist Spot Recommendation System
   --------------------------------------------
   - Min-Heap based on current crowd levels
   - Dynamic updates for real-time monitoring
   - Multiple time steps simulate changing crowds
*/

struct Spot {
    int id;
    int crowd; // current number of people
};

struct Compare {
    bool operator()(Spot a, Spot b) {
        return a.crowd > b.crowd; // min-heap: smaller crowd has higher priority
    }
};

int main() {
    const int timeSteps = 5; // simulate 5 different times of day
    priority_queue<Spot, vector<Spot>, Compare> pq;

    // Initialize tourist spots
    const int spots = 6;
    int initialCrowd[spots] = {120, 90, 150, 60, 110, 80};

    cout << "Initializing tourist spots...\n";
    for (int i = 0; i < spots; i++) {
        pq.push({i + 1, initialCrowd[i]});
        cout << "Spot " << i + 1 << " crowd = " << initialCrowd[i] << endl;
    }
    cout << "-------------------------------\n\n";

    // Simulate crowd updates over multiple time steps
    for (int t = 1; t <= timeSteps; t++) {
        cout << "=== Time Step " << t << " ===\n";

        // Temporary vector to store updated crowds
        vector<Spot> updatedSpots;

        // Update crowds dynamically
        while (!pq.empty()) {
            Spot s = pq.top();
            pq.pop();

            // Simulate random change in crowd (for simplicity, deterministic pattern)
            int change = ((s.id + t) % 5) * 5; // just a pattern for demo
            if (t % 2 == 0) s.crowd += change; // increase for even time steps
            else s.crowd -= change;            // decrease for odd time steps

            if (s.crowd < 0) s.crowd = 0;      // cannot have negative crowd
            updatedSpots.push_back(s);
        }

        // Push updated spots back into priority queue
        for (Spot s : updatedSpots) pq.push(s);

        // Recommend top 3 spots
        cout << "Recommended spots to visit:\n";
        int count = 0;
        vector<Spot> topSpots;
        while (!pq.empty() && count < 3) {
            Spot s = pq.top();
            pq.pop();
            cout << "Spot " << s.id << " | crowd = " << s.crowd << endl;
            topSpots.push_back(s);
            count++;
        }

        // Push top spots back into pq to maintain min-heap
        for (Spot s : topSpots) pq.push(s);

        cout << "-------------------------------\n\n";
    }

    // Final snapshot of all spots
    cout << "Final tourist crowd snapshot:\n";
    vector<Spot> finalSpots;
    while (!pq.empty()) {
        Spot s = pq.top();
        pq.pop();
        cout << "Spot " << s.id << " | crowd = " << s.crowd << endl;
        finalSpots.push_back(s);
    }

    // Restore priority queue for further use
    for (Spot s : finalSpots) pq.push(s);

    cout << "\nSimulation complete.\n";
    return 0;
}
