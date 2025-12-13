#include <iostream>
using namespace std;

int main() {
    int n, ecoStrain[100];

    // Number of eco-corridors
    cin >> n;

    // Eco-strain values of corridors
    for (int i = 0; i < n; i++)
        cin >> ecoStrain[i];

    // Selection Sort to arrange corridors by eco-strain
    for (int i = 0; i < n - 1; i++) {

        // Assume current corridor has minimum strain
        int min = i;

        // Find corridor with lower eco-strain
        for (int j = i + 1; j < n; j++) {
            if (ecoStrain[j] < ecoStrain[min])
                min = j;
        }

        // Place lowest eco-strain corridor at correct position
        int temp = ecoStrain[i];
        ecoStrain[i] = ecoStrain[min];
        ecoStrain[min] = temp;
    }

    // Display ranked eco-corridors
    for (int i = 0; i < n; i++)
        cout << ecoStrain[i] << " ";
}
