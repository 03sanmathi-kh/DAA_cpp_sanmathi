#include <iostream>
using namespace std;

/*
PROBLEM STATEMENT:
Eco-corridors are represented by sorted eco-strain values.
The task is to check whether a corridor exists whose eco-strain
exactly matches a given safe environmental limit.

WHY BINARY SEARCH:
Since the eco-strain values are already sorted, Binary Search
is used to efficiently locate the safe corridor by repeatedly
dividing the search space.
*/

// Get number of corridors
int readNumberOfCorridors() {
    int n;
    cin >> n;
    return n;
}

// Read eco-strain values into array
void readEcoStrainValues(int ecoStrain[], int n) {
    for (int i = 0; i < n; i++) {
        cin >> ecoStrain[i];
    }
}

// Read safe eco-strain limit
int readSafeLimit() {
    int limit;
    cin >> limit;
    return limit;
}

// Check if array is sorted (assumption verification)
bool isSorted(int ecoStrain[], int n) {
    for (int i = 1; i < n; i++) {
        if (ecoStrain[i] < ecoStrain[i - 1]) {
            return false;
        }
    }
    return true;
}

// Perform iterative binary search
int binarySearchEcoStrain(int ecoStrain[], int n, int safeLimit) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (ecoStrain[mid] == safeLimit) {
            return mid;
        }
        else if (ecoStrain[mid] < safeLimit) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

// Display successful search result
void displaySuccess(int position) {
    cout << "Safe corridor found at position " << position << endl;
}

// Display unsuccessful search result
void displayFailure() {
    cout << "No safe corridor found" << endl;
}

// Controller function for complete process
void processEcoCorridorSearch() {
    int ecoStrain[100];

    int n = readNumberOfCorridors();
    readEcoStrainValues(ecoStrain, n);

    int safeLimit = readSafeLimit();

    if (!isSorted(ecoStrain, n)) {
        cout << "Error: Eco-strain values are not sorted" << endl;
        return;
    }

    int result = binarySearchEcoStrain(ecoStrain, n, safeLimit);

    if (result != -1) {
        displaySuccess(result);
    } else {
        displayFailure();
    }
}

int main() {
    processEcoCorridorSearch();
    return 0;
}
