#include <iostream>
using namespace std;

/*
PROBLEM STATEMENT:
Given eco-strain values of corridors, detect if any corridor
exceeds a dangerous eco-strain threshold.

WHY LINEAR SEARCH:
Linear Search checks each corridor one by one. This is suitable
when the array is unsorted or small in size.
*/

// Function to read the number of corridors
int readNumberOfCorridors() {
    int n;
    cin >> n;
    return n;
}

// Function to read eco-strain values
void readEcoStrainValues(int ecoStrain[], int n) {
    for (int i = 0; i < n; i++) {
        cin >> ecoStrain[i];
    }
}

// Function to read the dangerous threshold
int readDangerLevel() {
    int level;
    cin >> level;
    return level;
}

// Function to perform linear search for overloaded corridor
int findOverloadedCorridor(int ecoStrain[], int n, int dangerLevel) {
    for (int i = 0; i < n; i++) {
        if (ecoStrain[i] == dangerLevel) {
            return i; // Return position of first overloaded corridor
        }
    }
    return -1; // Not found
}

// Function to display result
void displayResult(int position) {
    if (position != -1) {
        cout << "Overloaded corridor detected at position " << position << endl;
    } else {
        cout << "No overloaded corridor" << endl;
    }
}

// Optional validation: check for negative eco-strain values
bool validateEcoStrain(int ecoStrain[], int n) {
    for (int i = 0; i < n; i++) {
        if (ecoStrain[i] < 0) {
            cout << "Warning: Negative eco-strain value at position " << i << endl;
            return false;
        }
    }
    return true;
}

// Controller function to handle the complete process
void detectOverloadedCorridor() {
    int ecoStrain[100];

    int n = readNumberOfCorridors();
    readEcoStrainValues(ecoStrain, n);

    int dangerLevel = readDangerLevel();

    validateEcoStrain(ecoStrain, n);

    int position = findOverloadedCorridor(ecoStrain, n, dangerLevel);

    displayResult(position);
}

int main() {
    detectOverloadedCorridor();
    return 0;
}
