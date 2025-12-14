#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Patient {
    int patientId;
    int priority;      // Higher value = higher priority
    int treatmentTime; // 
    // Comparator for priority queue (Greedy choice)
    bool operator<(const Patient& other) const {
        return priority < other.priority; 
    }
};

int main() {

    cout << "=== Ayushman Bharat Appointment Optimization ===\n\n";

    /* ----------------------------------
       Available doctors (each with time slots)
    ---------------------------------- */
    int doctors = 2;
    vector<int> doctorTime = {30, 30}; // each doctor has 30 mins

    /* ----------------------------------
       Priority Queue to store patients
       Greedy strategy: treat high priority first
    ---------------------------------- */
    priority_queue<Patient> pq;

    // Adding patients (ID, Priority, Time required)
    pq.push({1, 3, 10}); // Emergency patient
    pq.push({2, 1, 15}); // Normal patient
    pq.push({3, 2, 20}); // Medium priority
    pq.push({4, 3, 10}); // Emergency patient

    /* ----------------------------------
       Greedy Appointment Allocation
    ---------------------------------- */
    while (!pq.empty()) {
        Patient current = pq.top();
        pq.pop();

        bool assigned = false;

        // Try assigning patient to any available doctor
        for (int i = 0; i < doctors; i++) {
            if (doctorTime[i] >= current.treatmentTime) {
                doctorTime[i] -= current.treatmentTime;

                cout << "Patient " << current.patientId
                     << " assigned to Doctor " << i + 1
                     << " | Priority: " << current.priority
                     << " | Time used: " << current.treatmentTime << " mins\n";

                assigned = true;
                break;
            }
        }

        // If no doctor is available
        if (!assigned) {
            cout << "Patient " << current.patientId
                 << " could not be scheduled (No time slots available)\n";
        }
    }

    cout << "\nAppointment optimization completed.\n";
    return 0;
}

