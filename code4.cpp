#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
PROBLEM:
Schedule patients for limited doctor time slots efficiently in an
Ayushman Bharat health camp. Patients have priorities (emergency > medium > normal)
and require varying treatment times.

WHY GREEDY:
Greedy approach ensures patients with higher priority are treated first,
maximizing the number of urgent patients handled within available doctor time.
*/


struct Patient {
    int patientId;
    int priority;      // Higher value = higher priority
    int treatmentTime; // Time required in minutes

    // Comparator for priority queue (Greedy choice)
    bool operator<(const Patient& other) const {
        return priority < other.priority; // higher priority patients first
    }
};

/* ----------------------------
   Input Patients
   ---------------------------- */
vector<Patient> inputPatients(int n) {
    vector<Patient> patients(n);
    for(int i=0;i<n;i++){
        cout << "Enter Patient ID: ";
        cin >> patients[i].patientId;
        cout << "Enter Priority (1=Normal, 2=Medium, 3=Emergency): ";
        cin >> patients[i].priority;
        cout << "Enter Treatment Time (mins): ";
        cin >> patients[i].treatmentTime;
        cout << endl;
    }
    return patients;
}

/* ----------------------------
   Display Doctor Availability
   ---------------------------- */
void displayDoctorTime(const vector<int>& doctorTime) {
    cout << "Current Doctor Availability (minutes left): ";
    for(size_t i=0;i<doctorTime.size();i++)
        cout << "Doctor " << i+1 << ": " << doctorTime[i] << " ";
    cout << "\n";
}

/* ----------------------------
   Schedule Appointments
   ---------------------------- */
void scheduleAppointments(vector<Patient>& patients, vector<int>& doctorTime) {
    priority_queue<Patient> pq;

    // Push all patients into priority queue
    for(auto p : patients)
        pq.push(p);

    cout << "\n--- Scheduling Patients ---\n\n";

    while(!pq.empty()){
        Patient current = pq.top(); pq.pop();
        bool assigned = false;

        cout << "Trying to assign Patient " << current.patientId
             << " | Priority: " << current.priority
             << " | Treatment: " << current.treatmentTime << " mins\n";

        // Assign to first available doctor
        for(size_t i=0;i<doctorTime.size();i++){
            if(doctorTime[i] >= current.treatmentTime){
                doctorTime[i] -= current.treatmentTime;
                cout << "Assigned to Doctor " << i+1
                     << " | Remaining Doctor Time: " << doctorTime[i] << " mins\n\n";
                assigned = true;
                break;
            }
        }

        if(!assigned){
            cout << "Could NOT assign Patient " << current.patientId
                 << " (No available time slots)\n\n";
        }

        displayDoctorTime(doctorTime);
    }

    cout << "\nAll patients processed.\n";
}

/* ----------------------------
   Controller Function
   ---------------------------- */
void runAppointmentScheduler() {
    int doctors, numPatients;
    cout << "Enter number of doctors available: ";
    cin >> doctors;

    vector<int> doctorTime(doctors);
    for(int i=0;i<doctors;i++){
        cout << "Enter available time (minutes) for Doctor " << i+1 << ": ";
        cin >> doctorTime[i];
    }

    cout << "\nEnter number of patients: ";
    cin >> numPatients;

    vector<Patient> patients = inputPatients(numPatients);

    scheduleAppointments(patients, doctorTime);
}

int main() {
    cout << "=== Ayushman Bharat Appointment Optimization ===\n\n";
    runAppointmentScheduler();
    return 0;
}
