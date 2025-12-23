#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    This structure stores details of one patient's appointment.
    We keep everything together so it is easy to manage.
*/
struct Appointment
{
    int patientId;   // Patient number
    int start;       // Starting time
    int end;         // Ending time
};

int main()
{
    int n;
    cout << "Enter number of patients: ";
    cin >> n;

    // Vector to store all appointments
    vector<Appointment> appointments;

    /*
        Taking input from user
        One appointment at a time
    */
    for (int i = 0; i < n; i++)
    {
        Appointment temp;

        temp.patientId = i + 1;

        cout << "\nEnter start time for patient " << temp.patientId << ": ";
        cin >> temp.start;

        cout << "Enter end time for patient " << temp.patientId << ": ";
        cin >> temp.end;

        appointments.push_back(temp);
    }

    /*
        STEP 1:
        Sort all appointments based on END TIME.
        Appointment that finishes first should come first.
        This helps us choose maximum non-overlapping appointments.
    */
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (appointments[i].end > appointments[j].end)
            {
                // Swap appointments
                Appointment swapTemp = appointments[i];
                appointments[i] = appointments[j];
                appointments[j] = swapTemp;
            }
        }
    }

    cout << "\nAppointments after sorting by end time:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Patient " << appointments[i].patientId
             << " -> [" << appointments[i].start
             << ", " << appointments[i].end << "]\n";
    }

    /*
        STEP 2:
        Greedy selection of appointments
    */

    vector<Appointment> selected;

    // First appointment is always selected
    selected.push_back(appointments[0]);
    int lastEndTime = appointments[0].end;

    /*
        Check remaining appointments
        Select only if start time >= last selected end time
    */
    for (int i = 1; i < n; i++)
    {
        if (appointments[i].start >= lastEndTime)
        {
            selected.push_back(appointments[i]);
            lastEndTime = appointments[i].end;
        }
    }

    /*
        STEP 3:
        Display final result
    */
    cout << "\nSelected appointments (No time clash):\n";
    for (int i = 0; i < selected.size(); i++)
    {
        cout << "Patient " << selected[i].patientId
             << " -> [" << selected[i].start
             << ", " << selected[i].end << "]\n";
    }

    cout << "\nTotal patients treated: " << selected.size() << endl;

    return 0;
}
