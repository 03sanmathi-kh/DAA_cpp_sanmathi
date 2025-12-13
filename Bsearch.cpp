#include <iostream>
using namespace std;

int main() {
    int n, ecoStrain[100], safeLimit;

    // Number of sorted eco-corridors
    cin >> n;

    // Sorted eco-strain values
    for (int i = 0; i < n; i++)
        cin >> ecoStrain[i];

    // Safe eco-strain threshold
    cin >> safeLimit;

    int low = 0, high = n - 1;

    // Binary Search to quickly locate safe corridor
    while (low <= high) {
        int mid = (low + high) / 2;

        // Exact safe corridor found
        if (ecoStrain[mid] == safeLimit) {
            cout << "Safe corridor found at position " << mid;
            return 0;
        }
        // Move to higher strain corridors
        else if (ecoStrain[mid] < safeLimit)
            low = mid + 1;
        // Move to lower strain corridors
        else
            high = mid - 1;
    }

    // No corridor matches safe limit
    cout << "No safe corridor found";
}
