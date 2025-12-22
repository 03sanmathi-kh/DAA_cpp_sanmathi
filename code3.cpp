#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
PROBLEM:
Allocate limited blood units to hospitals based on demand and urgency.
Hospitals with higher priority and urgent needs should get blood first.

WHY GREEDY ALGORITHM:
Greedy approach works because at each step, allocating to the highest
priority hospital maximizes overall effectiveness, ensuring urgent
needs are met before distributing to less critical cases.
*/

/* ----------------------------
   Hospital Structure
   ---------------------------- */
struct Hospital {
    int id;
    int demand;
    int priority; // higher value = more urgent
};

/* ----------------------------
   Comparator for sorting by priority
   ---------------------------- */
bool comparePriority(Hospital a, Hospital b) {
    return a.priority > b.priority;
}

/* ----------------------------
   Function to input hospital data
   ---------------------------- */
vector<Hospital> inputHospitals(int n) {
    vector<Hospital> hospitals(n);
    for(int i=0;i<n;i++){
        cout << "Enter Hospital ID: ";
        cin >> hospitals[i].id;
        cout << "Enter blood demand for Hospital " << hospitals[i].id << ": ";
        cin >> hospitals[i].demand;
        cout << "Enter priority (higher = urgent) for Hospital " << hospitals[i].id << ": ";
        cin >> hospitals[i].priority;
        cout << endl;
    }
    return hospitals;
}

/* ----------------------------
   Function to display hospitals
   ---------------------------- */
void displayHospitals(const vector<Hospital> &hospitals) {
    cout << "\nHospital Details (Before Allocation):\n";
    cout << "ID\tDemand\tPriority\n";
    for(auto h : hospitals)
        cout << h.id << "\t" << h.demand << "\t" << h.priority << endl;
}

/* ----------------------------
   Function to sort hospitals by priority
   ---------------------------- */
void sortHospitalsByPriority(vector<Hospital> &hospitals) {
    sort(hospitals.begin(), hospitals.end(), comparePriority);
    cout << "\nHospitals sorted by priority (highest first):\n";
    cout << "ID\tDemand\tPriority\n";
    for(auto h : hospitals)
        cout << h.id << "\t" << h.demand << "\t" << h.priority << endl;
}

/* ----------------------------
   Function to allocate blood (Greedy)
   ---------------------------- */
void allocateBlood(vector<Hospital> &hospitals, int &totalBloodUnits) {
    cout << "\nAllocating blood units step-by-step:\n";

    for(auto &h : hospitals){
        if(totalBloodUnits == 0){
            cout << "No more blood units left.\n";
            break;
        }

        int allocated = min(h.demand, totalBloodUnits);
        totalBloodUnits -= allocated;

        cout << "Hospital " << h.id << " | Demand: " << h.demand
             << " | Priority: " << h.priority
             << " | Allocated: " << allocated
             << " | Remaining Stock: " << totalBloodUnits << endl;
    }
}

/* ----------------------------
   Function to display final allocation status
   ---------------------------- */
void displayFinalStatus(const vector<Hospital> &hospitals, int totalBloodUnits) {
    cout << "\nFinal Blood Allocation Summary:\n";
    cout << "Hospital ID\tAllocated Units\n";
    for(auto h : hospitals){
        int allocated = min(h.demand, h.demand); // same as allocated during allocation
        cout << h.id << "\t\t" << min(h.demand, h.demand) << endl;
    }
    cout << "\nRemaining Blood Units in Stock: " << totalBloodUnits << endl;
}

/* ----------------------------
   Controller Function
   ---------------------------- */
void runBloodAllocation() {
    int totalBloodUnits, n;
    cout << "Enter total blood units available: ";
    cin >> totalBloodUnits;
    cout << "Enter number of hospitals: ";
    cin >> n;

    vector<Hospital> hospitals = inputHospitals(n);

    displayHospitals(hospitals);

    sortHospitalsByPriority(hospitals);

    allocateBlood(hospitals, totalBloodUnits);

    displayFinalStatus(hospitals, totalBloodUnits);
}

int main() {
    runBloodAllocation();
    return 0;
}
