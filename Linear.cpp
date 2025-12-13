#include <iostream>
using namespace std;

int main() {
    int n, ecoStrain[100], dangerLevel;

    // Number of eco-corridors
    cin >> n;

    // Eco-strain values
    for (int i = 0; i < n; i++)
        cin >> ecoStrain[i];

    // Dangerous eco-strain value to detect overload
    cin >> dangerLevel;

    // Linear Search checks every corridor
    for (int i = 0; i < n; i++) {

        // If any corridor crosses danger level
        if (ecoStrain[i] == dangerLevel) {
            cout << "Overloaded corridor detected at position " << i;
            return 0;
        }
    }

    // No overloaded corridor detected
    cout << "No overloaded corridor";
}
