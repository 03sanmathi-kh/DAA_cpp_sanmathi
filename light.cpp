#include <iostream>
#include <queue>
using namespace std;

/*
  Smart Streetlight Simulation
  ----------------------------
  - Each zone has a streetlight
  - Events represent activity starting or ending
  - Streetlights turn ON when activity starts, OFF when activity ends
  - Track total ON time per zone
*/

struct Event {
    int time;   // Time of event
    int zone;   // Streetlight zone
    int type;   // 1 = activity starts, 0 = activity ends
};

// Function to display current streetlight states
void displayStates(int streetlights[], int zones, int currentTime) {
    cout << "Time " << currentTime << " | Current states: ";
    for (int i = 0; i < zones; i++) {
        cout << "Zone " << i << "=" << (streetlights[i] ? "ON " : "OFF ");
    }
    cout << endl;
}

int main() {
    const int zones = 5;

    // Initialize streetlight states and ON timers
    int streetlights[zones] = {0};
    int onTime[zones] = {0}; // total time lights have been ON

    queue<Event> eventQueue;

    // Sample events (time, zone, type)
    eventQueue.push({1, 0, 1});
    eventQueue.push({2, 1, 1});
    eventQueue.push({3, 0, 0});
    eventQueue.push({4, 2, 1});
    eventQueue.push({5, 1, 0});
    eventQueue.push({6, 2, 0});
    eventQueue.push({7, 3, 1});
    eventQueue.push({8, 3, 0});
    eventQueue.push({9, 4, 1});
    eventQueue.push({10, 4, 0});

    cout << "Starting streetlight simulation...\n\n";

    int currentTime = 0;

    while (!eventQueue.empty()) {
        Event e = eventQueue.front();
        eventQueue.pop();

        // Update ON times for all zones
        int duration = e.time - currentTime;
        for (int i = 0; i < zones; i++) {
            if (streetlights[i] == 1) {
                onTime[i] += duration;
            }
        }
        currentTime = e.time;

        // Process event
        if (e.type == 1) {
            streetlights[e.zone] = 1;
            cout << "Time " << e.time << ": Activity started at Zone " << e.zone
                 << " -> Light turned ON." << endl;
        } else {
            streetlights[e.zone] = 0;
            cout << "Time " << e.time << ": Activity ended at Zone " << e.zone
                 << " -> Light turned OFF." << endl;
        }

        displayStates(streetlights, zones, e.time);
        cout << "--------------------------------------\n";
    }

    cout << "\nSimulation complete.\n\n";
    cout << "Total ON times per zone:\n";
    for (int i = 0; i < zones; i++) {
        cout << "Zone " << i << " : " << onTime[i] << " time units ON\n";
    }

    cout << "\nFinal streetlight states:\n";
    for (int i = 0; i < zones; i++) {
        cout << "Zone " << i << ": " << (streetlights[i] ? "ON" : "OFF") << endl;
    }

    // Additional summary: which zones were most active
    int maxTime = onTime[0], maxZone = 0;
    for (int i = 1; i < zones; i++) {
        if (onTime[i] > maxTime) {
            maxTime = onTime[i];
            maxZone = i;
        }
    }
    cout << "\nZone with most activity: Zone " << maxZone
         << " (" << maxTime << " time units ON)" << endl;

    return 0;
}
