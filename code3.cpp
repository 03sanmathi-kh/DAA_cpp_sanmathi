#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* ----------------------------
   Hospital Structure
   ---------------------------- */
struct Hospital {
    int id;
    int demand;
    int priority; // higher value = more urgent
};

/* ----------------------------
   Comparator for Partitioning
   ---------------------------- */
bool compare(Hospital a, Hospital b) {
    return a.priority > b.priority; // urgent hospitals first
}

int main() {
    int totalBloodUnits = 120;

    // Hospital data: {id, demand, priority}
    vector<Hospital> hospitals = {
        {1, 40, 3},
        {2, 30, 2},
        {3, 50, 5},
        {4, 20, 1}
    };

    // STEP 1: Partition hospitals based on priority
    sort(hospitals.begin(), hospitals.end(), compare);

    cout << "Blood Allocation Result:\n\n";

    // STEP 2: Edge relaxation (greedy distribution)
    for (auto &h : hospitals) {
        if (totalBloodUnits == 0)
            break;

        int allocated = min(h.demand, totalBloodUnits);
        totalBloodUnits -= allocated;

        cout << "Hospital " << h.id
             << " received " << allocated
             << " units\n";
    }

    // STEP 3: Search completion status
    cout << "\nRemaining Blood Units: " << totalBloodUnits << endl;

    return 0;
}

