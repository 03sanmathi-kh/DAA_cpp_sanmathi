#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
   Min-Heap for Real-Time Recommendations
   
   Each attraction stores:
     - id
     - current crowd count
     */

struct Spot {
    int id;
    int crowd;
};

struct Compare {
    bool operator()(Spot a, Spot b) {
        return a.crowd > b.crowd;   // Min-heap: smallest crowd first
    }
};

int main() {
    priority_queue<Spot, vector<Spot>, Compare> pq;

    // Push crowd values of 4 tourist spots
    pq.push({1, 120});
    pq.push({2, 90});
    pq.push({3, 150});
    pq.push({4, 60});   // least crowded

    cout << "Best spot to visit now: Spot "
         << pq.top().id
         << " with crowd = " << pq.top().crowd << endl;

    return 0;
}
