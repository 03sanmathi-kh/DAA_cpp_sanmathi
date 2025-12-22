#include <iostream>
using namespace std;

/*
PROBLEM STATEMENT:
Given eco-strain values of corridors, rank them from least to most sensitive.

WHY SELECTION SORT:
Selection Sort repeatedly selects the smallest element and places it at
the correct position. It is simple and works well for small datasets.
*/

// Function to read number of corridors
int readNumberOfCorridors() {
    int n;
    cin >> n;
    return n;
}

// Function to read eco-strain values
void readEcoStrain(int ecoStrain[], int n) {
    for (int i = 0; i < n; i++)
        cin >> ecoStrain[i];
}

// Function to validate eco-strain values (optional)
bool validateEcoStrain(int ecoStrain[], int n) {
    bool valid = true;
    for (int i = 0; i < n; i++) {
        if (ecoStrain[i] < 0) {
            cout << "Warning: Negative eco-strain at position " << i << endl;
            valid = false;
        }
    }
    return valid;
}

// Selection Sort with swap and comparison counters
void selectionSort(int ecoStrain[], int n) {
    int comparisons = 0;
    int swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (ecoStrain[j] < ecoStrain[minIndex])
                minIndex = j;
        }

        if (minIndex != i) {
            int temp = ecoStrain[i];
            ecoStrain[i] = ecoStrain[minIndex];
            ecoStrain[minIndex] = temp;
            swaps++;
        }
    }

    cout << "Total comparisons: " << comparisons << endl;
    cout << "Total swaps: " << swaps << endl;
}

// Function to display eco-strain array
void displayEcoStrain(int ecoStrain[], int n) {
    cout << "Ranked eco-corridors: ";
    for (int i = 0; i < n; i++)
        cout << ecoStrain[i] << " ";
    cout << endl;
}

// Controller function for the whole process
void rankEcoCorridors() {
    int ecoStrain[100];
    int n = readNumberOfCorridors();

    readEcoStrain(ecoStrain, n);

    validateEcoStrain(ecoStrain, n);

    selectionSort(ecoStrain, n);

    displayEcoStrain(ecoStrain, n);
}

int main() {
    rankEcoCorridors();
    return 0;
}
