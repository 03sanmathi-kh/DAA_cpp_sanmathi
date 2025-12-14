
#include <iostream>
#include <vector>
using namespace std;

/*

 Idea:
 - Visitor patterns repeat daily (peak hours, low hours).
 - We use recursion to predict footfall for a future hour.
 - Memoization is used to avoid recomputing results.
*/

// Memoization array (stores already computed predictions)
int memo[100];

// Recursive function to predict footfall
int predictFootfall(int hour, vector<int>& history) {

    // Base case:
    // If the hour exists in historical data, return it directly
    if (hour < history.size()) {
        return history[hour];
    }

    // If already computed, return stored value
    if (memo[hour] != -1) {
        return memo[hour];
    }

    /*
      Pattern recognition:
      Footfall often depends on previous hours.
      We assume the current hour footfall is the
      average of the previous two hours.
    */
    int prev1 = predictFootfall(hour - 1, history);
    int prev2 = predictFootfall(hour - 2, history);

    memo[hour] = (prev1 + prev2) / 2;

    return memo[hour];
}

int main() {

    // Historical museum footfall data (hour-wise)
    vector<int> footfall = {40, 60, 120, 200, 250, 220, 180};

    // Initialize memoization array
    for (int i = 0; i < 100; i++) {
        memo[i] = -1;
    }

    int futureHour = 9;  // Predict footfall for hour 9

    cout << "Predicting museum footfall...\n\n";

    int predictedVisitors = predictFootfall(futureHour, footfall);

    cout << "Predicted number of visitors at hour "
         << futureHour << " = "
         << predictedVisitors << endl;

    /*
      Use case:
      - If predicted visitors are high, increase staff.
      - If low, reduce operational resources.
    */

    return 0;
}
