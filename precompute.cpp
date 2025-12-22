#include <iostream>
using namespace std;

/*
   Prefix Sum Precomputation for Tourist Arrivals
   
   Objective:
   We want to efficiently calculate the number of tourists
   visiting a site between any two given hours.
   
   Approach:
   1. Maintain an array of hourly visitors.
   2. Precompute the prefix sum array.
      pref[i] = sum of visitors from hour 0 to hour i.
   3. Any query [L, R] can be answered in O(1):
      sum = pref[R] - pref[L-1] (if L > 0)
*/

int main() {
    // Step 1: Input number of hours
    const int hours = 6;
    int visitors[hours] = {30, 20, 25, 40, 10, 15}; // tourists per hour
    int pref[hours]; // prefix sum array

    cout << "Hourly visitor data:\n";
    for (int i = 0; i < hours; i++) {
        cout << "Hour " << i << ": " << visitors[i] << " visitors\n";
    }
    cout << "\n";

    // Step 2: Compute prefix sum array
    pref[0] = visitors[0];
    cout << "Building prefix sum array step by step:\n";
    cout << "pref[0] = " << pref[0] << endl;
    for (int i = 1; i < hours; i++) {
        pref[i] = pref[i - 1] + visitors[i];
        cout << "pref[" << i << "] = pref[" << i-1 << "] + visitors[" << i << "] = "
             << pref[i-1] << " + " << visitors[i] << " = " << pref[i] << endl;
    }
    cout << "\nComplete prefix sum array:\n";
    for (int i = 0; i < hours; i++)
        cout << "Hour 0 to " << i << ": " << pref[i] << " visitors\n";
    cout << "\n";

    // Step 3: Process multiple queries
    int queries[][2] = {{1, 3}, {2, 5}, {0, 4}}; // {L, R} pairs
    int numQueries = sizeof(queries) / sizeof(queries[0]);

    cout << "Processing queries:\n";
    for (int q = 0; q < numQueries; q++) {
        int l = queries[q][0];
        int r = queries[q][1];

        int totalVisitors = pref[r];
        if (l > 0) totalVisitors -= pref[l - 1];

        cout << "Visitors from hour " << l << " to " << r
             << " = " << totalVisitors << endl;
    }

    // Step 4: Optional: total visitors for the day
    cout << "\nTotal visitors for the entire day: " << pref[hours-1] << endl;

    return 0;
}
