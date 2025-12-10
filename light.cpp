#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Event structure: represents an event at a specific zone
struct Event {
    int time;       // Time of event (simplified as integer)
    int zone;       // Streetlight zone affected
    int type;       // Type: 1 = activity starts, 0 = activity ends
};

int main() {
    // Total zones in the city
    const int zones = 5;

    // Queue to store events
    queue<Event> eventQueue;

    // Example events: {time, zone, type}
    eventQueue.push({1, 0, 1}); // Activity starts at zone 0
    eventQueue.push({2, 1, 1}); // Activity starts at zone 1
    eventQueue.push({3, 0, 0}); // Activity ends at zone 0
    eventQueue.push({4, 2, 1}); // Activity starts at zone 2

    // Streetlight status: 1 = ON, 0 = OFF
    vector<int> streetlights(zones, 0);

    cout << "Simulating streetlight system...\n\n";

    // Process events in chronological order
    while (!eventQueue.empty()) {
        Event e = eventQueue.front();
        eventQueue.pop();

        // Turn ON/OFF streetlights based on event type
        if (e.type == 1) {
            streetlights[e.zone] = 1; // Activity starts -> light ON
            cout << "Time " << e.time << ": Zone " << e.zone << " lights turned ON.\n";
        } else {
            streetlights[e.zone] = 0; // Activity ends -> light OFF
            cout << "Time " << e.time << ": Zone " << e.zone << " lights turned OFF.\n";
        }
    }

    cout << "\nFinal streetlight states:\n";
    for (int i = 0; i < zones; i++) {
        cout << "Zone " << i << ": " << (streetlights[i] ? "ON" : "OFF") << endl;
    }

    return 0;
}
