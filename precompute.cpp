#include <iostream>
using namespace std;

/*
   Prefix Sum Precomputation:
  
   This creates a cumulative array of hourly tourist arrivals.
   After precomputing, any query like:
      "How many tourists visited between hour L and R?"
   can be answered in O(1) time.
   
*/

int main() {
    int hours = 6;
    int visitors[] = {30, 20, 25, 40, 10, 15};
    int pref[10];

    // Build prefix sum
    pref[0] = visitors[0];
    for (int i = 1; i < hours; i++)
        pref[i] = pref[i - 1] + visitors[i];

    // Query: tourists from hour 2 to 5
    int l = 2, r = 5;

    // Prefix-sum formula
    int result = pref[r] - (l > 0 ? pref[l - 1] : 0);

    cout << "Visitors from hour " << l << " to " << r
         << " = " << result << endl;

    return 0;
}
